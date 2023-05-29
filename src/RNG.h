#pragma once

namespace ff {

class RNG {
  public:
	RNG();

	[[nodiscard]] unsigned long long rand64() const;
};

} // namespace ff
