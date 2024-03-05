#include "util/Hash.h"

Hash::hash_type Hash::hash(const std::uint32_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return 0;
}

Hash::hash_type Hash::hash(const std::uint16_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return 0;
}

Hash::hash_type Hash::hash(const std::uint8_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return 0;
}

Hash::hash_type Hash::combine_hashes(const hash_type first_hash, const hash_type second_hash) noexcept {
	return first_hash ^ second_hash;
}

Hash::hash_type Hash::hash(std::uint64_t value) noexcept {
    const hash_type A = 5'647'095'006'226'412'969;
    const hash_type B = 41'413'938'183'913'153;
    const hash_type C = 6'225'658'194'131'981'369;

    hash_type result = (((value >> 14) + A) + ((value << 54) ^ B)) << 4;
    result = result ^ ((value % C) * 137);

    return result;
}
