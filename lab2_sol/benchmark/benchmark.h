#pragma once

#include "benchmark/benchmark.h"

#include "encryption/Key.h"
#include "image/bitmap_image.h"

#include <cstdint>
#include <span>
#include <vector>

class Holder {
	constexpr static std::uint32_t row_height = 3;
	constexpr static std::uint32_t row_width = 16656;

	constexpr static std::uint32_t column_height = 1024;
	constexpr static std::uint32_t column_width = 48;

	constexpr static std::uint32_t square = 1024;

public:
	static void init(const std::size_t number_keys) {
		keys.reserve(number_keys);
		keys.emplace_back(Key::get_standard_key());

		for (auto i = std::size_t(1); i < number_keys; i++) {
			keys.emplace_back(Key::produce_new_key(keys[i - 1]));
		}

		for (auto y = 0; y < square; y++) {
			for (auto x = 0; x < square; x++) {
				const auto& pixel = BitmapImage::BitmapPixel{ static_cast<std::uint8_t>((y % 256) + (x % 256)), static_cast<std::uint8_t>((x * y) % 256), static_cast<std::uint8_t>((x + y + 17) % 256) };
				square_image.set_pixel(y, x, pixel);
			}
		}

		for (auto y = 0; y < row_height; y++) {
			for (auto x = 0; x < row_width; x++) {
				const auto& pixel = BitmapImage::BitmapPixel{ static_cast<std::uint8_t>(y % 256), static_cast<std::uint8_t>(x % 256), static_cast<std::uint8_t>((x + y * x) % 256) };
				row_image.set_pixel(y, x, pixel);
			}
		}

		for (auto y = 0; y < column_height; y++) {
			for (auto x = 0; x < column_width; x++) {
				const auto& pixel = BitmapImage::BitmapPixel{ static_cast<std::uint8_t>(y % 256), static_cast<std::uint8_t>(x % 256), static_cast<std::uint8_t>((x + y * x) % 256) };
				column_image.set_pixel(y, x, pixel);
			}
		}
	}

	static const std::vector<Key::key_type>& get_keys() {
		return keys;
	}

	static const BitmapImage& get_row_image() {
		return row_image;
	}

	static const BitmapImage& get_column_image() {
		return column_image;
	}

	static const BitmapImage& get_square_image() {
		return square_image;
	}

private:
	static inline std::vector<Key::key_type> keys{};

	static inline BitmapImage row_image{ row_height, row_width };
	static inline BitmapImage column_image{ column_height, column_width };
	static inline BitmapImage square_image{ square, square };
};
