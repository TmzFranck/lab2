#include "encryption/Key.h"
#include "util/Hash.h"

Key::key_type Key::get_standard_key() noexcept {
	auto key = key_type{};
	for (auto i = key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	return key;
}


Key::key_type Key::produce_new_key(const key_type& old_key) {
	key_type new_key;
	for (int i = 0; i < 6; i++) {
		std::uint64_t value;
		std::memcpy(&value, &old_key[i * 8], sizeof(value));
		std::uint64_t hashed_value = Hash::hash(value);
		std::memcpy(&new_key[i * 8], &hashed_value, sizeof(hashed_value));
	}
	return new_key;
}



std::uint64_t Key::hash(const key_type& key) {
	std::uint64_t combined_hash = 0;
	key_type hashed_key = produce_new_key(key);
	for (int i = 0; i < 6; i++) {
		std::uint64_t value;
		std::memcpy(&value, &hashed_key[i * 8], sizeof(value));
		combined_hash = Hash::combine_hashes(combined_hash, value);
	}
	return combined_hash;
}



std::uint64_t Key::get_smallest_hash(const std::span<const key_type>& keys) {
	if (keys.empty()) {
		return std::numeric_limits<std::uint64_t>::max();
	}

	std::uint64_t smallest_hash = hash(keys[0]);
	for (const auto& key : keys) {
		std::uint64_t current_hash = hash(key);
		if (current_hash < smallest_hash) {
			smallest_hash = current_hash;
		}
	}
	return smallest_hash;
}


std::uint64_t Key::get_smallest_hash_parallel(const std::span<const key_type>& keys, int num_threads = 1) {
	if (keys.empty()) {
		return std::numeric_limits<std::uint64_t>::max();
	}

	std::uint64_t smallest_hash = std::numeric_limits<std::uint64_t>::max();

	#pragma omp parallel for num_threads(num_threads) reduction(min:smallest_hash)
	for (int i = 0; i < keys.size(); i++) {
		std::uint64_t current_hash = hash(keys[i]);
		if (current_hash < smallest_hash) {
			smallest_hash = current_hash;
		}
	}
	return smallest_hash;
}


Key::key_type Key::find_key(const std::span<const key_type>& keys, std::uint64_t target_hash) {
	for (const auto& key : keys) {
		if (hash(key) == target_hash) {
			return key;
		}
	}

	// Return a dummy value if no matching key is found.
	// This should never happen according to the problem statement.
	return key_type{};
}


Key::key_type Key::find_key_parallel(const std::span<const key_type>& keys, std::uint64_t target_hash, int num_threads = 1) {
	key_type result;
	bool found = false;

	#pragma omp parallel for num_threads(num_threads)
	for (int i = 0; i < keys.size(); i++) {
		if (hash(keys[i]) == target_hash) {
			#pragma omp critical
			{
				if (!found) {
					result = keys[i];
					found = true;
				}
			}
		}
	}

	// Return a dummy value if no matching key is found.
	// This should never happen according to the problem statement.
	return found ? result : key_type{};
}