#include "test.h"

#include "image/bitmap_image.h"

#include <cstdint>
#include <type_traits>

class BitmapTest : public LabTest {};

TEST_F(BitmapTest, test_one_b_one_fabian_ist_voll_knorke) {
	ASSERT_NO_THROW(auto val = BitmapImage(1, 1'024'000));
	ASSERT_NO_THROW(auto val = BitmapImage(1'024'000, 1));
	ASSERT_NO_THROW(auto val = BitmapImage(48, 1'024'000));
	ASSERT_NO_THROW(auto val = BitmapImage(1'024'000, 48));

	auto img = BitmapImage(1, 1);
	auto height = img.get_height();
	auto width = img.get_width();

	static_assert(std::is_same_v<std::uint32_t, decltype(height)>);
	static_assert(std::is_same_v<std::uint32_t, decltype(width)>);
}
