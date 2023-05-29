#include "Dictionary.h"
#include "RNG.h"
#include "utility.h"

#include <openssl/evp.h>

#include <climits>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

int main(int argc, char* argv[]) {
	int phrase_size {24};
	std::size_t bit_size {256};
	if (argc > 1) {
		phrase_size = std::stoi(argv[1], nullptr, 10);
		if (phrase_size != 12 && phrase_size != 24)
			throw std::runtime_error("Invalid seed size");
		if (phrase_size == 12)
			bit_size = 128;
	}

	std::filesystem::path filepath {std::filesystem::current_path() / "../data/english.txt"};
	ff::Dictionary dictionary(filepath);

	std::vector<char> bytes(bit_size / CHAR_BIT, 0);
	std::string hex_value;
	ff::RNG rng;
	for (std::size_t i = 0; i < bit_size / 64; ++i) {
		std::uint64_t random_number {static_cast<std::uint64_t>(rng.rand64())};
		std::memcpy(&bytes[i * 8], &random_number, 8); // Copy 8 bytes number to 8-chars
		for (std::size_t j = 0; j < 8; ++j)			   // Parse 8-chars to hex representation
			hex_value += std::format("{:0>2x}", static_cast<std::uint8_t>(bytes[i * 8 + j]));
	}

	std::string sha256 {ff::hash(EVP_sha256(), bytes.data(), bytes.size())};
	hex_value = hex_value + sha256[0];
	if (phrase_size == 24)
		hex_value = hex_value + sha256[1];

	std::string bin_value;
	for (const char& c : hex_value)
		bin_value += std::format("{:0>4b}", ff::hex_to_dec.find(c));

	std::vector<int> wordBitVec;
	std::string bin_word;
	int count = 0;
	for (const char c : bin_value) {
		bin_word += c;
		++count;
		if (count % 11 == 0) {
			wordBitVec.push_back(std::stoi(bin_word, nullptr, 2));
			bin_word.clear();
		}
	}
	for (const int& key : wordBitVec)
		std::print("{} ", dictionary.get_word(key).value());
	std::println("");

	return 0;
}
