#include "test.h"

#include "authors.h"
#include "fmt/format.h"

TEST_F(LabTest, test_authors_fabian_ist_voll_knorke) {
	const auto message_1_a = fmt::format("1a) wurde bearbeitet von: {}\n", AUTHORS_ONE_A);
	const auto message_1_b = fmt::format("1b) wurde bearbeitet von: {}\n", AUTHORS_ONE_B);

	const auto message_2_a = fmt::format("2a) wurde bearbeitet von: {}\n", AUTHORS_TWO_A);
	const auto message_2_b = fmt::format("2b) wurde bearbeitet von: {}\n", AUTHORS_TWO_B);
	const auto message_2_c = fmt::format("2c) wurde bearbeitet von: {}\n", AUTHORS_TWO_C);
	const auto message_2_d = fmt::format("2d) wurde bearbeitet von: {}\n", AUTHORS_TWO_D);
	const auto message_2_e = fmt::format("2e) wurde bearbeitet von: {}\n", AUTHORS_TWO_E);
	const auto message_2_f = fmt::format("2f) wurde bearbeitet von: {}\n", AUTHORS_TWO_F);

	const auto message_3_a = fmt::format("3a) wurde bearbeitet von: {}\n", AUTHORS_THREE_A);
	const auto message_3_b = fmt::format("3b) wurde bearbeitet von: {}\n", AUTHORS_THREE_B);
	const auto message_3_c = fmt::format("3c) wurde bearbeitet von: {}\n", AUTHORS_THREE_C);
	const auto message_3_d = fmt::format("3d) wurde bearbeitet von: {}\n", AUTHORS_THREE_D);
	const auto message_3_e = fmt::format("3e) wurde bearbeitet von: {}\n", AUTHORS_THREE_E);
	const auto message_3_f = fmt::format("3f) wurde bearbeitet von: {}\n", AUTHORS_THREE_F);

	std::cout << message_1_a;
	std::cout << message_1_b;

	std::cout << message_2_a;
	std::cout << message_2_b;
	std::cout << message_2_c;
	std::cout << message_2_d;
	std::cout << message_2_e;
	std::cout << message_2_f;

	std::cout << message_3_a;
	std::cout << message_3_b;
	std::cout << message_3_c;
	std::cout << message_3_d;
	std::cout << message_3_e;
	std::cout << message_3_f;

	const auto authors_1_a = std::string(AUTHORS_ONE_A);
	const auto authors_1_b = std::string(AUTHORS_ONE_B);

	const auto authors_2_a = std::string(AUTHORS_TWO_A);
	const auto authors_2_b = std::string(AUTHORS_TWO_B);
	const auto authors_2_c = std::string(AUTHORS_TWO_C);
	const auto authors_2_d = std::string(AUTHORS_TWO_D);
	const auto authors_2_e = std::string(AUTHORS_TWO_E);
	const auto authors_2_f = std::string(AUTHORS_TWO_F);

	const auto authors_3_a = std::string(AUTHORS_THREE_A);
	const auto authors_3_b = std::string(AUTHORS_THREE_B);
	const auto authors_3_c = std::string(AUTHORS_THREE_C);
	const auto authors_3_d = std::string(AUTHORS_THREE_D);
	const auto authors_3_e = std::string(AUTHORS_THREE_E);
	const auto authors_3_f = std::string(AUTHORS_THREE_F);

	ASSERT_GT(authors_1_a.length(), 0);
	ASSERT_GT(authors_1_b.length(), 0);

	ASSERT_GT(authors_2_a.length(), 0);
	ASSERT_GT(authors_2_b.length(), 0);
	ASSERT_GT(authors_2_c.length(), 0);
	ASSERT_GT(authors_2_d.length(), 0);
	ASSERT_GT(authors_2_e.length(), 0);
	ASSERT_GT(authors_2_f.length(), 0);

	ASSERT_GT(authors_3_a.length(), 0);
	ASSERT_GT(authors_3_b.length(), 0);
	ASSERT_GT(authors_3_c.length(), 0);
	ASSERT_GT(authors_3_d.length(), 0);
	ASSERT_GT(authors_3_e.length(), 0);
	ASSERT_GT(authors_3_f.length(), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	const auto tests_return_code = RUN_ALL_TESTS();

	return tests_return_code;
}
