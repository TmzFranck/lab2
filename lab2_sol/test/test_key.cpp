#include "test.h"

#include "encryption/Key.h"

#include <climits>
#include <cstdint>

class KeyTest : public LabTest {};

TEST_F(KeyTest, test_three_a_one_fabian_ist_voll_knorke) {
	const auto& standard_key = Key::get_standard_key();

	const auto& new_key = Key::produce_new_key(standard_key);
	const auto& expected_new_key = Key::key_type{32, 142, 78, 8, 85, 162, 36, 45, 104, 220, 0, 126, 3, 244, 154, 1, 176, 42, 203, 172, 202, 86, 241, 117, 248, 96, 149, 26, 124, 135, 63, 232, 0, 181, 39, 81, 46, 245, 77, 156, 72, 23, 246, 135, 217, 59, 144, 176};
	
	ASSERT_EQ(new_key, expected_new_key);
}

TEST_F(KeyTest, test_three_b_one_fabian_ist_voll_knorke) {
	const auto& standard_key = Key::get_standard_key();

	const auto standard_hash = Key::hash(standard_key);
	const auto expected_standard_hash = std::uint64_t{ 11'361'817'798'440'499'784ULL };

	ASSERT_EQ(standard_hash, expected_standard_hash);
}

TEST_F(KeyTest, test_three_c_one_fabian_ist_voll_knorke) {
	const auto minimum_hash = Key::get_smallest_hash({});
	const auto expected_minimum_hash = std::numeric_limits<std::uint64_t>::max();

	ASSERT_EQ(minimum_hash, expected_minimum_hash);
}

TEST_F(KeyTest, test_three_c_two_fabian_ist_voll_knorke) {
	auto keys = std::vector<Key::key_type>{};
	keys.reserve(1024);

	keys.emplace_back(Key::get_standard_key());
	for (auto i = std::size_t(0); i < 1023; i++) {
		keys.emplace_back(Key::produce_new_key(keys[i]));
	}

	const auto minimum_hash = Key::get_smallest_hash(keys);
	const auto expected_minimum_hash = std::uint64_t{ 30'403'176'973'399'313ULL };

	ASSERT_EQ(minimum_hash, expected_minimum_hash);
}

TEST_F(KeyTest, test_three_e_one_fabian_ist_voll_knorke) {
	auto keys = std::vector<Key::key_type>{};
	keys.reserve(1024);

	keys.emplace_back(Key::get_standard_key());
	for (auto i = std::size_t(0); i < 1023; i++) {
		keys.emplace_back(Key::produce_new_key(keys[i]));
	}

	const auto hash_to_find = std::uint64_t{ 30'403'176'973'399'313ULL };

	const auto key = Key::find_key(keys, hash_to_find);

	ASSERT_EQ(Key::hash(key), hash_to_find);
}

TEST_F(KeyTest, test_three_f_two_fabian_ist_voll_knorke) {
	auto keys = std::vector<Key::key_type>{};
	keys.reserve(1024);

	keys.emplace_back(Key::get_standard_key());
	for (auto i = std::size_t(0); i < 1023; i++) {
		keys.emplace_back(Key::produce_new_key(keys[i]));
	}

	const auto hash_to_find = std::uint64_t{ 30'403'176'973'399'313ULL };

	const auto key = Key::find_key_parallel(keys, hash_to_find, 4);

	ASSERT_EQ(Key::hash(key), hash_to_find);
}
