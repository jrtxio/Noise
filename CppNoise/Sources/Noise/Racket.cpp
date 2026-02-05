// Racket.cpp - Racket Runtime Implementation

#include "Noise/Racket.hpp"
#include "NoiseBoot/NoiseBoot.hpp"

#include <cstring>

namespace Noise {

Racket::Racket(const std::string& execPath) {
    racket_boot_arguments_t args = {};

    std::string petitePath = NoiseBoot::getPetitePath();
    std::string schemePath = NoiseBoot::getSchemePath();
    std::string racketPath = NoiseBoot::getRacketPath();

    args.exec_file = const_cast<char*>(execPath.c_str());
    args.boot1_path = const_cast<char*>(petitePath.c_str());
    args.boot2_path = const_cast<char*>(schemePath.c_str());
    args.boot3_path = const_cast<char*>(racketPath.c_str());

    racket_boot(&args);
    racket_deactivate_thread();
}

Racket::~Racket() {
    // Runtime cleans up on process exit
}

void Racket::load(const std::filesystem::path& zo) {
    std::string pathStr = zo.string();
    racket_embedded_load_file(pathStr.c_str(), 1);
}

Val Racket::require(Val what, Val mod) {
    return {racket_dynamic_require(mod.p, what.p)};
}

} // namespace Noise
