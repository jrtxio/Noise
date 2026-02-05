// Racket.hpp - Racket Runtime Bindings for C++

#pragma once

#include <string>
#include <vector>
#include <cstdint>

#ifdef _WIN32
#include "chezscheme-x86_64-windows.h"
#else
#error "Unsupported platform"
#endif

#include "racketcs.h"
#include "NoiseBoot/NoiseBoot.hpp"

namespace Noise {

// Unsafe wrapper for Chez Scheme values.
// Values may be moved by GC, so use within activated threads.
struct Val {
    ptr p;

    static Val null() { return {Snil}; }
    static Val f() { return {Sfalse}; }
    static Val t() { return {Strue}; }
    static Val fixnum(iptr i) { return {Sfixnum(i)}; }
    static Val symbol(const char* s) { return {Sstring_to_symbol(s)}; }
    static Val symbol(const std::string& s) { return symbol(s.c_str()); }
    static Val string(const char* s) { return {Sstring(s)}; }
    static Val string(const std::string& s) { return string(s.c_str()); }
    static Val cons(Val a, Val b) { return {Scons(a.p, b.p)}; }

    void lock() const { Slock_object(p); }
    void unlock() const { Sunlock_object(p); }
    Val locked() const { lock(); return *this; }
    Val unlocked() const { unlock(); return *this; }

    Val apply(Val args) const { return Sprocedurep(p) ? unsafeApply(args) : null(); }
    Val unsafeApply(Val args) const { return {racket_apply(p, args.p)}; }

    bool isProcedure() const { return Sprocedurep(p) != 0; }
    bool isPair() const { return Spairp(p) != 0; }
    bool isFixnum() const { return Sfixnump(p) != 0; }
    bool isBytevector() const { return Sbytevectorp(p) != 0; }

    Val car() const { return isPair() ? unsafeCar() : null(); }
    Val cdr() const { return isPair() ? unsafeCdr() : null(); }
    Val unsafeCar() const { return {Scar(p)}; }
    Val unsafeCdr() const { return {Scdr(p)}; }

    iptr fixnumValue() const { return isFixnum() ? unsafeFixnumValue() : 0; }
    iptr unsafeFixnumValue() const { return Sfixnum_value(p); }

    std::string bytestring() const { return isBytevector() ? unsafeBytestring() : ""; }
    std::string unsafeBytestring() const {
        return std::string(reinterpret_cast<const char*>(Sbytevector_data(p)),
                           static_cast<size_t>(Sbytevector_length(p)));
    }

    std::vector<uint8_t> bytevector() const { return isBytevector() ? unsafeBytevector() : std::vector<uint8_t>{}; }
    std::vector<uint8_t> unsafeBytevector() const {
        auto data = reinterpret_cast<const uint8_t*>(Sbytevector_data(p));
        return std::vector<uint8_t>(data, data + Sbytevector_length(p));
    }

    bool operator==(const Val& o) const { return p == o.p; }
    bool operator!=(const Val& o) const { return p != o.p; }
};

// The Racket runtime.
// Only one instance may be created per process.
// All Racket operations must run on the thread that created the instance.
struct Racket {
    Racket(const std::string& execPath = "racket") {
        racket_boot_arguments_t args = {};
        std::string petite = NoiseBoot::getPetitePath();
        std::string scheme = NoiseBoot::getSchemePath();
        std::string racket = NoiseBoot::getRacketPath();
        args.exec_file = const_cast<char*>(execPath.c_str());
        args.boot1_path = const_cast<char*>(petite.c_str());
        args.boot2_path = const_cast<char*>(scheme.c_str());
        args.boot3_path = const_cast<char*>(racket.c_str());
        racket_boot(&args);
        racket_deactivate_thread();
    }

    ~Racket() {}

    Racket(const Racket&) = delete;
    Racket& operator=(const Racket&) = delete;

    void load(const std::string& zo) { racket_embedded_load_file(zo.c_str(), 1); }
    Val require(Val what, Val mod) { return {racket_dynamic_require(mod.p, what.p)}; }

    template<typename F>
    auto bracket(F&& proc) -> decltype(proc()) {
        racket_activate_thread();
        auto result = proc();
        racket_deactivate_thread();
        return result;
    }

    void activate() { racket_activate_thread(); }
    void deactivate() { racket_deactivate_thread(); }
    void destroy() { racket_destroy(); }
};

} // namespace Noise
