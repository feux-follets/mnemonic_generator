#pragma once

#include "Base.h"

#include <filesystem>
#include <string>
#include <unordered_map>

class Dictionary : NonCopyable {
  public:
	explicit Dictionary(const std::filesystem::path& filepath);
	std::string get_word(const int& key) const;

  private:
	inline static const int word_length{2048};
	inline static const std::string english_md5sum{"f23506956964fa69c98fa3fb5c8823b5"};
	std::unordered_map<int, std::string> dictionary;
};
