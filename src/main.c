#include <cub.h>

t_state *state(void)
{
	static t_state	state;

	return (&state);
}

static void move_player(int key)
{
	t_posd	pos;
	t_posd	dir;
	double	move_speed;

	pos = state()->player_pos;
	dir = state()->player_dir;
	move_speed = state()->player_move_speed;

	if (key == KEY_W || key == KEY_UP)
	{
		state()->player_pos.x += state()->player_delta.x;
		state()->player_pos.y += state()->player_delta.y;
	}
	if (key == KEY_S || key == KEY_DOWN)
	{
		state()->player_pos.x -= state()->player_delta.x;
		state()->player_pos.y -= state()->player_delta.y;
	}
	if (key == KEY_A || key == KEY_LEFT)
	{
		state()->player_angle -= 0.1;
		if (state()->player_angle < 0)
			state()->player_angle +=2*PI;
		state()->player_delta.x = cos(state()->player_angle) * 5;
		state()->player_delta.y = sin(state()->player_angle) * 5;
	}
	if (key == KEY_D || key == KEY_RIGHT)
	{
		state()->player_angle += 0.1;
		if (state()->player_angle > 2*PI)
			state()->player_angle -=2*PI;
		state()->player_delta.x = cos(state()->player_angle) * 5;
		state()->player_delta.y = sin(state()->player_angle) * 5;
	}
	mlx_clear_window(w()->init, w()->window);
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

int	main(void)
{
	int world_map[] = {
		4,4,4,4,4,4,4,4,
		4,0,4,0,0,0,0,4,
		4,0,4,0,0,0,0,4,
		4,0,4,0,0,0,0,4,
		4,0,0,0,0,0,0,4,
		4,0,0,0,0,4,0,4,
		4,0,0,0,0,0,0,4,
		4,4,4,4,4,4,4,4,
	};

	ft_memcpy(state()->world_map, world_map, 24 * 24 * sizeof(int));

	state()->player_pos.x = 300;
	state()->player_pos.y = 300;

	state()->player_dir.x = -1;
	state()->player_dir.y = 0;

	state()->player_plane.x = 0;
	state()->player_plane.y = 0.66;

	state()->player_delta.x = cos(state()->player_angle) * 5;
	state()->player_delta.y = sin(state()->player_angle) * 5;

	w__init(SCREEN_WIDTH, SCREEN_HEIGHT);
	w__open();
	mlx_loop_hook(w()->init, w__render, world_map);
	mlx_hook(w()->window, 17, WINDOW_X, w__close, NULL);
	// key press
	mlx_hook(w()->window, 2, 1L<<0, e__key_press, NULL);
	mlx_loop(w()->init);
	mlx_loop_end(w()->init);
	return (0);
}
