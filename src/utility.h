#pragma once

#include <openssl/types.h>

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>

namespace ff {

inline constexpr std::string_view hex_to_dec {"0123456789abcdef"};
std::string slurp(const std::filesystem::path& filepath);
std::string hash(const EVP_MD* type, const char* bytes, const std::size_t& size);

} // namespace ff
