#pragma once

#include <filesystem>
#include <string>

namespace util {

std::ifstream try_open(std::filesystem::path const& file);

} // namespace util
