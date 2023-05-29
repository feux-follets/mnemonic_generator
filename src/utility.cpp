#include "utility.h"

#include <openssl/evp.h>

#include <format>
#include <fstream>
#include <stdexcept>

namespace ff {

std::string slurp(const std::filesystem::path& filepath) {
	std::ifstream input(filepath, std::ios::binary);
	if (!input.is_open())
		throw std::runtime_error(std::format("Failed to open {}\n", filepath.c_str()));
	std::ostringstream contents;
	contents << input.rdbuf();
	return contents.str();
}

std::string hash(const EVP_MD* type, const char* bytes, const std::size_t& size) {
	unsigned char md_buffer[EVP_MAX_MD_SIZE] {};
	unsigned int md_len {0};
	EVP_Digest(bytes, size, md_buffer, &md_len, type, nullptr);

	std::string output;
	for (unsigned int i = 0; i < md_len; ++i)
		output += std::format("{:0>2x}", md_buffer[i]);
	return output;
}

} // namespace ff
