// Racket.hpp - Racket Runtime Bindings for C++
// Mirrors SwiftNoise/Sources/Noise/Racket.swift

#pragma once

#include <string>
#include <filesystem>
#include <functional>
#include <stdexcept>

// Include Chez Scheme headers (provided by copy-libs.sh)
#ifdef _WIN32
#include "chezscheme-x86_64-windows.h"
#else
#error "Unsupported platform"
#endif

#include "racketcs.h"

namespace Noise {

/// An unsafe wrapper for Chez Scheme values.
///
/// @note Values may be moved by the GC at any time, so these
/// helpers should mainly be used to create data to be passed into
/// Racket, and to copy data from Racket within activated threads.
struct Val {
    ptr p;

    /// The empty list.
    static Val null() { return {Snil}; }

    /// The false value.
    static Val f() { return {Sfalse}; }

    /// The true value.
    static Val t() { return {Strue}; }

    /// Creates a Chez Scheme fixnum.
    static Val fixnum(iptr i) { return {Sfixnum(i)}; }

    /// Creates a Chez Scheme symbol by copying a string.
    static Val symbol(const char* s) { return {Sstring_to_symbol(s)}; }

    /// Creates a Chez Scheme symbol by copying a string.
    static Val symbol(const std::string& s) { return symbol(s.c_str()); }

    /// Creates a Chez Scheme string by copying a regular string.
    static Val string(const char* s) { return {Sstring(s)}; }

    /// Creates a Chez Scheme string by copying a regular string.
    static Val string(const std::string& s) { return string(s.c_str()); }

    /// Creates a pair of two Values.
    static Val cons(Val a, Val b) { return {Scons(a.p, b.p)}; }

    /// Locks the value to prevent the GC from moving it.
    void lock() const { Slock_object(p); }

    /// Unlocks the value to let the GC move it.
    void unlock() const { Sunlock_object(p); }

    /// Like lock(), but returns the value.
    Val locked() const { lock(); return *this; }

    /// Like unlock(), but returns the value.
    Val unlocked() const { unlock(); return *this; }

    /// Applies the value using args.
    Val apply(Val args) const {
        if (Sprocedurep(p)) {
            return unsafeApply(args);
        }
        return null();
    }

    /// Applies the value using args, panicking if the value is not a procedure.
    Val unsafeApply(Val args) const {
        return {racket_apply(p, args.p)};
    }

    /// Returns true if this is a procedure.
    bool isProcedure() const { return Sprocedurep(p) != 0; }

    /// Returns true if this is a pair.
    bool isPair() const { return Spairp(p) != 0; }

    /// Returns true if this is a fixnum.
    bool isFixnum() const { return Sfixnump(p) != 0; }

    /// Returns true if this is a bytevector.
    bool isBytevector() const { return Sbytevectorp(p) != 0; }

    /// Returns the car of a pair.
    Val car() const {
        if (isPair()) return unsafeCar();
        return null();
    }

    /// Returns the cdr of a pair.
    Val cdr() const {
        if (isPair()) return unsafeCdr();
        return null();
    }

    /// Returns the car of a pair, panicking if not a pair.
    Val unsafeCar() const { return {Scar(p)}; }

    /// Returns the cdr of a pair, panicking if not a pair.
    Val unsafeCdr() const { return {Scdr(p)}; }

    /// Extracts the integer value of a fixnum.
    iptr fixnumValue() const {
        if (isFixnum()) return unsafeFixnumValue();
        return 0;
    }

    /// Extracts the integer value of a fixnum, panicking if not a fixnum.
    iptr unsafeFixnumValue() const { return Sfixnum_value(p); }

    /// Copies a Chez Scheme bytevector value into a string.
    std::string bytestring() const {
        if (isBytevector()) return unsafeBytestring();
        return "";
    }

    /// Copies a Chez Scheme bytevector value into a string.
    std::string unsafeBytestring() const {
        iptr len = Sbytevector_length(p);
        const char* data = reinterpret_cast<const char*>(Sbytevector_data(p));
        return std::string(data, static_cast<size_t>(len));
    }

    /// Copies a Chez Scheme bytevector into a vector of bytes.
    std::vector<uint8_t> bytevector() const {
        if (isBytevector()) return unsafeBytevector();
        return {};
    }

    /// Copies a Chez Scheme bytevector into a vector of bytes.
    std::vector<uint8_t> unsafeBytevector() const {
        iptr len = Sbytevector_length(p);
        const uint8_t* data = reinterpret_cast<const uint8_t*>(Sbytevector_data(p));
        return std::vector<uint8_t>(data, data + len);
    }

    bool operator==(const Val& other) const { return p == other.p; }
    bool operator!=(const Val& other) const { return p != other.p; }
};

/// The Racket runtime.
///
/// # Threading
///
/// The thread on which the runtime is instantiated is considered the
/// main Racket place. All Racket operations must be run on that thread.
/// You may work with Chez Scheme values and call Chez Scheme primitives
/// from other threads (see bracket() and activate()).
///
/// @warning Only one instance may be created per process.
class Racket {
public:
    /// Initializes Racket with the given executable path.
    explicit Racket(const std::string& execPath = "racket");

    /// Destructor - tears down the Chez Scheme runtime.
    ~Racket();

    // Non-copyable
    Racket(const Racket&) = delete;
    Racket& operator=(const Racket&) = delete;

    /// Loads compiled Racket code.
    ///
    /// @warning This function must be called from the same thread the
    /// Racket runtime was initialized on.
    void load(const std::filesystem::path& zo);

    /// Requires `what` from the module at path `mod`.
    ///
    /// @warning This function must be called from the same thread the
    /// Racket runtime was initialized on.
    Val require(Val what, Val mod);

    /// Calls proc after activating the current thread.
    /// Deactivates the thread before returning proc's result.
    template<typename F>
    auto bracket(F&& proc) -> decltype(proc()) {
        racket_activate_thread();
        auto result = proc();
        racket_deactivate_thread();
        return result;
    }

    /// Makes the current thread known to Chez Scheme.
    ///
    /// @warning Accessing Chez Scheme data from inactive threads
    /// races against the garbage collector.
    void activate() { racket_activate_thread(); }

    /// Deactivates the current thread.
    void deactivate() { racket_deactivate_thread(); }

    /// Tears down the Chez Scheme runtime.
    void destroy() { racket_destroy(); }
};

} // namespace Noise
