#include "minunit.h"
#include "cub.h"

MU_TEST(it_should_read_textures)
{
	t_parse_cub_result res;
	res = parse_cub_file("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture");

	mu_assert_string_eq(res.textures.NO, "./path_to_the_north_texture");
	mu_assert_string_eq(res.textures.SO, "./path_to_the_south_texture");
	mu_assert_string_eq(res.textures.WE, "./path_to_the_west_texture");
	mu_assert_string_eq(res.textures.EA, "./path_to_the_east_texture");
}

MU_TEST(it_should_read_textures_with_blank_space)
{
	t_parse_cub_result res;
	res = parse_cub_file("NO ./path_to_the_north _texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture");

	mu_assert_string_eq(res.textures.NO, "./path_to_the_north _texture");
	mu_assert_string_eq(res.textures.SO, "./path_to_the_south_texture");
	mu_assert_string_eq(res.textures.WE, "./path_to_the_west_texture");
	mu_assert_string_eq(res.textures.EA, "./path_to_the_east_texture");
}

MU_TEST(it_should_read_textures_without_variables)
{
	t_parse_cub_result res;
	res = parse_cub_file("\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture");

	mu_assert_string_eq(res.textures.NO, NULL);
	mu_assert_string_eq(res.textures.SO, "./path_to_the_south_texture");
	mu_assert_string_eq(res.textures.WE, "./path_to_the_west_texture");
	mu_assert_string_eq(res.textures.EA, "./path_to_the_east_texture");

	res = parse_cub_file("N ./path_to_the_north_texture\nSO ./path_to_the_south_texture\n ./path_to_the_west_texture\nEA ./path_to_the_east_texture");

	mu_assert_string_eq(res.textures.NO, NULL);
	mu_assert_string_eq(res.textures.SO, "./path_to_the_south_texture");
	mu_assert_string_eq(res.textures.WE, NULL);
	mu_assert_string_eq(res.textures.EA, "./path_to_the_east_texture");
}

MU_TEST(it_should_read_textures_with_letters)
{
	t_parse_cub_result res;
	res = parse_cub_file("NO ./path_to_the_nortSOh_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture");

	mu_assert_string_eq(res.textures.NO, "./path_to_the_nortSOh_texture");
	mu_assert_string_eq(res.textures.SO, "./path_to_the_south_texture");
	mu_assert_string_eq(res.textures.WE, "./path_to_the_west_texture");
	mu_assert_string_eq(res.textures.EA, "./path_to_the_east_texture");
}

MU_TEST_SUITE(test_textures)
{
	MU_RUN_TEST(it_should_read_textures);
	MU_RUN_TEST(it_should_read_textures_with_blank_space);
	MU_RUN_TEST(it_should_read_textures_without_variables);
	MU_RUN_TEST(it_should_read_textures_with_letters);
}


MU_TEST(it_should_read_colors)
{
	t_parse_cub_result res;

	res = parse_cub_file("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,0\nC 225,30,0");

	mu_assert_string_eq(res.colors.floor, "220,100,0");
	mu_assert_string_eq(res.colors.celing, "225,30,0");
}

MU_TEST(it_should_read_colors_without_variables)
{
	t_parse_cub_result res;

	res = parse_cub_file("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n 220,100,0\nC 225,30,0");

	mu_assert_string_eq(res.colors.floor, NULL);
	mu_assert_string_eq(res.colors.celing, "225,30,0");
}

MU_TEST(it_should_read_colors_with_same_letters)
{
	t_parse_cub_result res;

	res = parse_cub_file("NO ./path_to_theF_north_texture\nSO ./paCCC th_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,0\nC 225,30,0");

	mu_assert_string_eq(res.colors.floor, "220,100,0");
	mu_assert_string_eq(res.colors.celing, "225,30,0");
}

MU_TEST_SUITE(test_colors)
{
	MU_RUN_TEST(it_should_read_colors);
	MU_RUN_TEST(it_should_read_colors_without_variables);
	MU_RUN_TEST(it_should_read_colors_with_same_letters);
}


MU_TEST(it_should_read_map)
{
	t_parse_cub_result res;

	res = parse_cub_file("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,0\nC 225,30,0\n\n        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 111111111111\n");

	mu_assert_string_eq(res.map, "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 111111111111");
}

MU_TEST_SUITE(test_map)
{
	MU_RUN_TEST(it_should_read_map);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_textures);
	MU_RUN_SUITE(test_colors);
	MU_RUN_SUITE(test_map);
	MU_REPORT();
	return MU_EXIT_CODE;
}
