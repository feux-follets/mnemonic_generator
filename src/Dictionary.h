#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace ff {

class Dictionary {
  public:
	explicit Dictionary(const std::filesystem::path& filepath);
	std::optional<std::string> get_word(const int key) const;

  private:
	static constexpr int word_count{2048};
	static constexpr std::string_view english_md5sum{"f23506956964fa69c98fa3fb5c8823b5"};
	std::unordered_map<int, std::string> dictionary;
};

} // namespace ff
