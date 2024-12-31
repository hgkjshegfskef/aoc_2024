#include "util.hh"

#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

namespace util {

std::ifstream try_open(std::filesystem::path const& file) {
    std::ifstream f;
    if (f.open(file); !f) {
        throw std::system_error{errno, std::generic_category(), "failed to open '" + file.string() + "'"};
    }
    return f;
}

} // namespace util
