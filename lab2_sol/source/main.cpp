#include "encryption/FES.h"
#include "encryption/Key.h"
#include "io/image_parser.h"

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

#include <bit>

int main(int argc, char** argv) {
	auto lab_cli_app = CLI::App{ "" };

	auto image_path = std::filesystem::path{};
	auto file_option = lab_cli_app.add_option("--file", image_path);

	auto output_path = std::filesystem::path{};
	auto output_option = lab_cli_app.add_option("--output", output_path);

	file_option->check(CLI::ExistingFile);
	output_option->check(CLI::ExistingDirectory);

	CLI11_PARSE(lab_cli_app, argc, argv);

	const auto& endianness = std::endian::native;

	auto bitmap_image = ImageParser::read_bitmap(image_path);

	const auto key_1 = Key::get_standard_key();
	const auto key_2 = Key::produce_new_key(key_1);

	auto transposed_image = bitmap_image.transpose();

	auto encrypted_image = FES::encrypt(bitmap_image, key_1);
	auto transposed_encrypted_image = encrypted_image.transpose();

	auto encryted_transposed_encryted_image = FES::encrypt(transposed_encrypted_image, key_2);

	auto decrypted_image = FES::decrypt(encrypted_image, key_1);

	ImageParser::write_bitmap(output_path / "clean.bmp", bitmap_image);
	ImageParser::write_bitmap(output_path / "transposed.bmp", transposed_image);

	ImageParser::write_bitmap(output_path / "encrypted_image.bmp", encrypted_image);
	ImageParser::write_bitmap(output_path / "decrypted_image.bmp", decrypted_image);

	ImageParser::write_bitmap(output_path / "encryted_transposed_encryted_image.bmp", encryted_transposed_encryted_image);

	return 0;
}
