#include <cub.h>

static void move_player(int key)
{
	int	xo = 0;
	if (state()->player_delta.x < 0)
		xo = -20;
	else
		xo = 20;
	int	yo = 0;
	if (state()->player_delta.y < 0)
		yo = -20;
	else
		yo = 20;
	int	ipx = state()->player_pos.x / MAP_LENGTH;
	int	ipx_add_xo = (state()->player_pos.x + xo) / MAP_LENGTH;
	int	ipx_sub_xo = (state()->player_pos.x - xo) / MAP_LENGTH;

	int	ipy = state()->player_pos.y / MAP_LENGTH;
	int	ipy_add_yo = (state()->player_pos.y + yo) / MAP_LENGTH;
	int	ipy_sub_yo = (state()->player_pos.y - yo) / MAP_LENGTH;

	if (key == KEY_W || key == KEY_UP)
	{
		if (state()->world_map[ipy * MAP_WIDTH + ipx_add_xo] == 0)
			state()->player_pos.x += state()->player_delta.x * 10;
		if (state()->world_map[ipy_add_yo * MAP_WIDTH + ipx] == 0)
			state()->player_pos.y += state()->player_delta.y * 10;
	}
	if (key == KEY_S || key == KEY_DOWN)
	{
		if (state()->world_map[ipy * MAP_WIDTH + ipx_sub_xo] == 0)
			state()->player_pos.x -= state()->player_delta.x * 10;
		if (state()->world_map[ipy_sub_yo * MAP_WIDTH + ipx] == 0)
			state()->player_pos.y -= state()->player_delta.y * 10;
	}
	if (key == KEY_A || key == KEY_LEFT)
	{
		state()->player_angle += 5;
		state()->player_angle = fix_angle(state()->player_angle);
		state()->player_delta.x = cos(degree_to_radians(state()->player_angle));
		state()->player_delta.y = -sin(degree_to_radians(state()->player_angle));
	}
	if (key == KEY_D || key == KEY_RIGHT)
	{
		state()->player_angle -= 5;
		state()->player_angle = fix_angle(state()->player_angle);
		state()->player_delta.x = cos(degree_to_radians(state()->player_angle));
		state()->player_delta.y = -sin(degree_to_radians(state()->player_angle));
	}
}

static int e__key_press(int key)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == KEY_S
		|| key == KEY_A || key == KEY_D)
		move_player(key);
	else if (key == KEY_UP || key == KEY_DOWN
		|| key == KEY_LEFT || key == KEY_RIGHT)
		move_player(key);
	return (0);
}

void	print_map(int array[MAP_HEIGHT][MAP_WIDTH])
{
	int	i;
	int	j;

	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		while (i < MAP_WIDTH)
		{
			printf("%i", array[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	*textures(void)
{
	static void *img;
	int			height;
	int			width;
	// TODO
	if (!img) {
		img = mlx_xpm_file_to_image(w()->init, "textures/wall.xpm", &width, &height);
	}
	return (img);
}

int	main(void)
{
	int world_map[] = {
		1,4,4,4,4,4,4,4,
		1,0,3,0,0,0,0,4,
		1,0,3,0,0,0,0,4,
		1,0,3,0,0,0,0,4,
		1,0,0,0,0,0,0,4,
		1,0,0,0,0,2,0,4,
		1,0,0,0,0,0,0,4,
		1,2,2,2,2,2,2,2,
	};

	ft_memcpy(state()->world_map, world_map, MAP_LENGTH * sizeof(int));

	state()->player_pos.x = 150;
	state()->player_pos.y = 400;

	state()->player_angle = 90;

	state()->player_delta.x = cos(degree_to_radians(state()->player_angle));
	state()->player_delta.y = -sin(degree_to_radians(state()->player_angle));

	w__init(SCREEN_WIDTH, SCREEN_HEIGHT);
	w__open();
	textures();
	mlx_loop_hook(w()->init, w__render, world_map);
	mlx_hook(w()->window, 17, WINDOW_X, w__close, NULL);
	// key press
	mlx_hook(w()->window, 2, 1L<<0, e__key_press, NULL);
	mlx_loop(w()->init);
	mlx_loop_end(w()->init);
	return (0);
}
