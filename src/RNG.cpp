#include "RNG.h"

#include <cpuid.h>
#include <immintrin.h>

#include <stdexcept>

namespace ff {

RNG::RNG() {
	unsigned int eax {}, ebx {}, ecx {}, edx {};
	__get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx);

	if (!(ebx & bit_RDSEED))
		throw std::runtime_error("CPU does not have RDSEED!\n");
}

unsigned long long RNG::rand64() const {
	unsigned long long num {};
	while (!_rdseed64_step(&num))
		;
	return num;
}

} // namespace ff
