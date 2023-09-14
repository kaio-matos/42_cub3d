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

MU_TEST(it_should_read_colors)
{
	t_parse_cub_result res;

	res = parse_cub_file("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,0\nC 225,30,0");

	mu_assert_string_eq(res.colors.floor, "220,100,0");
	mu_assert_string_eq(res.colors.celing, "225,30,0");
}

MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(it_should_read_textures);
	MU_RUN_TEST(it_should_read_colors);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
