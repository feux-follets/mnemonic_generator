#include "Dictionary.h"
#include "Hash.h"
#include "RNG/RNG.h"

#include <fmt/format.h>

#include <vector>

const std::string HEX2DEC = "0123456789abcdef";
constexpr int phrase_size = 4; // 4 * 64 = 256 bits

int main(int argc, char* argv[]) {
	std::unique_ptr<ff::RNG> rng;
	std::unique_ptr<Dictionary> dictionary;

	try {
		rng = std::make_unique<ff::RNG>();
		std::filesystem::path filepath{std::filesystem::current_path() / "../data/english.txt"};
		if (argc > 1)
			filepath = argv[1];
		dictionary = std::make_unique<Dictionary>(filepath);
	} catch (std::exception& e) {
		fmt::print(stderr, "{}\n", e.what());
		return 1;
	}

	std::string hex_str;
	for (int i = 0; i < phrase_size; ++i)
		hex_str += fmt::format("{:0>16x}", rng->rand64());

	std::string hashed_hex_str{hex_sha256(hex_str)};
	hashed_hex_str = hex_str + hashed_hex_str[0] + hashed_hex_str[1];

	std::string bin_264;
	for (const char& c : hashed_hex_str)
		bin_264 += fmt::format("{:0>4b}", HEX2DEC.find(c));

	std::vector<int> wordBitVec;
	std::string wordBit;
	int count = 0;
	for (const char& c : bin_264) {
		wordBit += c;
		++count;
		if (count % 11 == 0) {
			wordBitVec.emplace_back(std::stoi(wordBit, nullptr, 2));
			wordBit.clear();
		}
	}
	for (const int& key : wordBitVec)
		fmt::print("{} ", dictionary->get_word(key));
	fmt::print("\n");

	return 0;
}
