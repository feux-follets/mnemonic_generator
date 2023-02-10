#include "Dictionary.h"

#include "Hash.h"

#include <fstream>

Dictionary::Dictionary(const std::filesystem::path& path) {
	std::ifstream input(path);
	if (input.fail())
		throw std::runtime_error("File read error!");
	if (md5sum(path) != english_md5sum)
		throw std::runtime_error("md5sum unmatched!");

	std::string line;
	dictionary.reserve(word_length);
	for (int i = 0; i < word_length; ++i) {
		std::getline(input, line);
		dictionary.emplace(i, line);
	}
}

std::string Dictionary::get_word(const int& key) const {
	if (!dictionary.contains(key))
		return "";
	return dictionary.at(key);
}
