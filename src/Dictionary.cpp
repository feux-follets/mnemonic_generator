#include "Dictionary.h"

#include "utility.h"

#include <openssl/evp.h>

#include <fstream>
#include <stdexcept>
#include <utility>

namespace ff {

Dictionary::Dictionary(const std::filesystem::path& path) {
	std::string input(ff::slurp(path));
	if (ff::hash(EVP_md5(), input.c_str(), input.size()) != english_md5sum)
		throw std::runtime_error("md5sum unmatched!");

	std::ifstream input_reader(path);
	std::string line;
	dictionary.reserve(word_count);
	for (int i = 0; i < word_count; ++i) {
		std::getline(input_reader, line);
		dictionary.emplace(i, line);
	}
}

std::optional<std::string> Dictionary::get_word(const int key) const {
	const auto iter{dictionary.find(key)};
	if (iter != dictionary.end())
		return iter->second;
	else
		return {};
}

} // namespace ff
