#include "benchmark.h"

#include "encryption/FES.h"
#include "encryption/Key.h"
#include "image/bitmap_image.h"

#include <iostream>

static bool check_image_equality_fabian_ist_voll_knorke(const BitmapImage& first, const BitmapImage& second) {
	if (first.get_height() != second.get_height()) {
		return false;
	}

	if (first.get_width() != second.get_width()) {
		return false;
	}

	// Who knows in what order they store their pixel
	try {
		for (auto y = std::uint32_t{ 0 }; y < first.get_height(); y++) {
			for (auto x = std::uint32_t{ 0 }; x < first.get_width(); x++) {
				const auto& first_pixel = first.get_pixel(y, x);
				const auto first_r = first_pixel.get_red_channel();
				const auto first_g = first_pixel.get_green_channel();
				const auto first_b = first_pixel.get_blue_channel();

				const auto& second_pixel = second.get_pixel(y, x);
				const auto second_r = second_pixel.get_red_channel();
				const auto second_g = second_pixel.get_green_channel();
				const auto second_b = second_pixel.get_blue_channel();

				if ((first_r != second_r) | (first_g != second_g) | (first_b != second_b)) {
					return false;
				}
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = std::uint32_t{ 0 }; y < first.get_height(); y++) {
			for (auto x = std::uint32_t{ 0 }; x < first.get_width(); x++) {
				const auto& first_pixel = first.get_pixel(x, y);
				const auto first_r = first_pixel.get_red_channel();
				const auto first_g = first_pixel.get_green_channel();
				const auto first_b = first_pixel.get_blue_channel();

				const auto& second_pixel = second.get_pixel(x, y);
				const auto second_r = second_pixel.get_red_channel();
				const auto second_g = second_pixel.get_green_channel();
				const auto second_b = second_pixel.get_blue_channel();

				if ((first_r != second_r) | (first_g != second_g) | (first_b != second_b)) {
					return false;
				}
			}
		}
	}
	return true;
}

static BitmapImage transpose_fabian_ist_voll_knorke(const BitmapImage& img) {
	const auto width = img.get_width();
	const auto height = img.get_height();

	auto transposed_image = BitmapImage(width, height);

	// Who knows in what order they store their pixel
	try {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				transposed_image.set_pixel(x, y, img.get_pixel(y, x));
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				transposed_image.set_pixel(y, x, img.get_pixel(x, y));
			}
		}
	}
	return transposed_image;
}

static BitmapImage grayscale_fabian_ist_voll_knorke(const BitmapImage& img) {
	const auto height = img.get_height();
	const auto width = img.get_width();

	auto gray_image = BitmapImage(height, width);

	// Who knows in what order they store their pixel
	try {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				const auto pixel = img.get_pixel(y, x);
				const auto r = pixel.get_red_channel();
				const auto g = pixel.get_green_channel();
				const auto b = pixel.get_blue_channel();

				const auto gray = r * 0.2989 + g * 0.5870 + b * 0.1140;
				const auto gray_converted = static_cast<std::uint8_t>(gray);

				const auto gray_pixel = BitmapImage::BitmapPixel{ gray_converted , gray_converted,  gray_converted };

				gray_image.set_pixel(y, x, gray_pixel);
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				const auto pixel = img.get_pixel(x, y);
				const auto r = pixel.get_red_channel();
				const auto g = pixel.get_green_channel();
				const auto b = pixel.get_blue_channel();

				const auto gray = r * 0.2989 + g * 0.5870 + b * 0.1140;
				const auto gray_converted = static_cast<std::uint8_t>(gray);

				const auto gray_pixel = BitmapImage::BitmapPixel{ gray_converted , gray_converted,  gray_converted };

				gray_image.set_pixel(x, y, gray_pixel);
			}
		}
	}

	return gray_image;
}

static BitmapImage copy_fabian_ist_voll_knorke(const BitmapImage& img) {
	const auto height = img.get_height();
	const auto width = img.get_width();

	auto return_value = BitmapImage(height, width);

	// Who knows in what order they store their pixel
	try {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				return_value.set_pixel(y, x, img.get_pixel(y, x));
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				return_value.set_pixel(x, y, img.get_pixel(x, y));
			}
		}
	}

	return return_value;
}

static BitmapImage mystery_fabian_ist_voll_knorke(const BitmapImage& img) {
	const auto construct_pixel = [](const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue) -> BitmapImage::BitmapPixel {
		switch (BitmapImage::BitmapPixel::channel_order) {
		case ChannelOrder::BGR:
			return { blue, green, red };
		case ChannelOrder::BRG:
			return { blue, red, green };
		case ChannelOrder::GBR:
			return { green, blue, red };
		case ChannelOrder::GRB:
			return { green, red, blue };
		case ChannelOrder::RBG:
			return { red, blue, green };
		case ChannelOrder::RGB:
			return { red, green, blue };
		}

		throw std::exception{};
		};

	const auto height = img.get_height();
	const auto width = img.get_width();

	// Who knows in what order they store their pixel
	try {
		auto working_copy = copy_fabian_ist_voll_knorke(img);

		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				const auto smallest_x = x;
				const auto largest_x = (x + 2 < width) ? x + 2 : width;

				const auto smallest_y = y;
				const auto largest_y = (y + 2 < height) ? y + 2 : height;

				auto red_acc = std::uint16_t{ 0 };
				auto green_acc = std::uint16_t{ 0 };
				auto blue_acc = std::uint16_t{ 0 };

				for (auto y_it = smallest_y; y_it < largest_y; y_it++) {
					for (auto x_it = smallest_x; x_it < largest_x; x_it++) {
						const auto pixel = img.get_pixel(y_it, x_it);
						const auto r = pixel.get_red_channel();
						const auto g = pixel.get_green_channel();
						const auto b = pixel.get_blue_channel();

						red_acc += r;
						green_acc += g;
						blue_acc += b;
					}
				}

				const auto red_cut = static_cast<std::uint8_t>(red_acc);
				const auto green_cut = static_cast<std::uint8_t>(green_acc);
				const auto blue_cut = static_cast<std::uint8_t>(blue_acc);

				const auto new_pixel = construct_pixel(red_cut, green_cut, blue_cut);

				working_copy.set_pixel(y, x, new_pixel);
			}
		}

		return working_copy;
	}
	catch (std::exception ex) {
		auto working_copy = copy_fabian_ist_voll_knorke(img);

		for (auto y = std::uint32_t(0); y < height; y++) {
			for (auto x = std::uint32_t(0); x < width; x++) {
				const auto smallest_x = x;
				const auto largest_x = (x + 2 < width) ? x + 2 : width;

				const auto smallest_y = y;
				const auto largest_y = (y + 2 < height) ? y + 2 : height;

				auto red_acc = std::uint16_t{ 0 };
				auto green_acc = std::uint16_t{ 0 };
				auto blue_acc = std::uint16_t{ 0 };

				for (auto y_it = smallest_y; y_it < largest_y; y_it++) {
					for (auto x_it = smallest_x; x_it < largest_x; x_it++) {
						const auto pixel = img.get_pixel(x_it, y_it);
						const auto r = pixel.get_red_channel();
						const auto g = pixel.get_green_channel();
						const auto b = pixel.get_blue_channel();

						red_acc += r;
						green_acc += g;
						blue_acc += b;
					}
				}

				const auto red_cut = static_cast<std::uint8_t>(red_acc);
				const auto green_cut = static_cast<std::uint8_t>(green_acc);
				const auto blue_cut = static_cast<std::uint8_t>(blue_acc);

				const auto new_pixel = construct_pixel(red_cut, green_cut, blue_cut);

				working_copy.set_pixel(x, y, new_pixel);
			}
		}

		return working_copy;
	}
}

static void benchmark_two_a_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& row_image = Holder::get_row_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel_coarse(row_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(row_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel_coarse(row_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_a_two_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& column_image = Holder::get_column_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel_coarse(column_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(column_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel_coarse(column_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_b_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& row_image = Holder::get_row_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel_fine(row_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(row_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel_fine(row_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_b_two_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& column_image = Holder::get_column_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel_fine(column_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(column_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel_fine(column_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_c_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& row_image = Holder::get_row_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel(row_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(row_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel(row_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_c_two_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& column_image = Holder::get_column_image();
	const auto& standard_key = Key::get_standard_key();

	for (auto _ : state) {
		const auto val = FES::encrypt_parallel(column_image, standard_key, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = FES::encrypt(column_image, standard_key);
	const auto parallel_answer = FES::encrypt_parallel(column_image, standard_key, number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_d_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& image = Holder::get_square_image();

	for (auto _ : state) {
		const auto val = image.transpose_parallel(number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = transpose_fabian_ist_voll_knorke(image);
	const auto parallel_answer = image.transpose_parallel(number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_e_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& image = Holder::get_square_image();

	for (auto _ : state) {
		const auto val = image.get_grayscale_parallel(number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = grayscale_fabian_ist_voll_knorke(image);
	const auto parallel_answer = image.get_grayscale_parallel(number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_f_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& image = Holder::get_row_image();

	auto working_image = copy_fabian_ist_voll_knorke(image);

	for (auto _ : state) {
		working_image.mystery_parallel(number_threads);
	}

	auto serial_answer = mystery_fabian_ist_voll_knorke(copy_fabian_ist_voll_knorke(image));

	auto parallel_answer = copy_fabian_ist_voll_knorke(image);
	parallel_answer.mystery_parallel(number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_two_f_two_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& image = Holder::get_column_image();

	auto working_image = copy_fabian_ist_voll_knorke(image);

	for (auto _ : state) {
		working_image.mystery_parallel(number_threads);
	}

	auto serial_answer = mystery_fabian_ist_voll_knorke(copy_fabian_ist_voll_knorke(image));

	auto parallel_answer = copy_fabian_ist_voll_knorke(image);
	parallel_answer.mystery_parallel(number_threads);

	if (!check_image_equality_fabian_ist_voll_knorke(serial_answer, parallel_answer)) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

BENCHMARK(benchmark_two_a_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_a_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_a_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_a_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_a_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_a_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_b_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_b_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_b_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_b_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_b_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_b_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_c_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_c_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_c_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_c_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_c_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_c_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_e_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_e_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_e_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_two_f_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_two_f_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_two_f_two_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);
