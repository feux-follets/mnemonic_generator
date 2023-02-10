#include "Hash.h"

#include <fmt/format.h>
#include <openssl/evp.h>

#include <algorithm>
#include <fstream>

std::string md5sum(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path))
		return "";

	std::uintmax_t size = std::filesystem::file_size(path);
	char buffer[size];
	std::ifstream input(path, std::ios::binary);
	if (input.bad())
		return "";
	input.read(buffer, size);
	input.close();

	EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;
	EVP_DigestInit_ex2(md_ctx, EVP_md5(), nullptr);
	EVP_DigestUpdate(md_ctx, buffer, size);
	EVP_DigestFinal(md_ctx, md_value, &md_len);
	EVP_MD_CTX_free(md_ctx);

	std::string output;
	for (unsigned int i = 0; i < md_len; ++i)
		output += fmt::format("{:0>2x}", md_value[i]);
	return output;
}

void format(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	s.erase(std::remove(s.begin(), s.end(), ':'), s.end());
}

/// Computer sha256 of a given hex string
/// \param input a hex string
/// \return sha256 of input
std::string hex_sha256(const std::string& input) {
	long buffer_length = 0;
	unsigned char* bin = OPENSSL_hexstr2buf(input.c_str(), &buffer_length);

	const EVP_MD* md_algo = EVP_sha256();
	unsigned int md_len = EVP_MD_size(md_algo);
	unsigned char md[md_len];
	EVP_Digest(bin, buffer_length, md, &md_len, md_algo, nullptr);
	OPENSSL_free(bin);

	char* buffer = OPENSSL_buf2hexstr(md, md_len);
	std::string output(buffer);
	OPENSSL_free(buffer);

	format(output);
	return output;
}
