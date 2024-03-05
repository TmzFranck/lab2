#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <limits>
#include <span>


class Key {
public:
	using key_type = std::array<std::uint8_t, 48>;

	[[nodiscard]] static key_type get_standard_key() noexcept;

	[[nodiscard]] static key_type produce_new_key(const key_type& old_key);
	
	[[nodiscard]] static std::uint64_t hash(const key_type& key);
	
	[[nodiscard]] static std::uint64_t get_smallest_hash(const std::span<const key_type>& keys);
	
	[[nodiscard]] static std::uint64_t get_smallest_hash_parallel(const std::span<const key_type>& keys, int num_threads);

	[[nodiscard]] static key_type find_key(const std::span<const key_type>& keys, std::uint64_t target_hash);

	[[nodiscard]] static key_type find_key_parallel(const std::span<const key_type>& keys, std::uint64_t target_hash, int num_threads);

private:

};
