#pragma once

#include <filesystem>
#include <string>

std::string md5sum(const std::filesystem::path& path);
std::string hex_sha256(const std::string& input);
