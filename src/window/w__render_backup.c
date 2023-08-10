#include <cub.h>

void	w__draw_pixeli(t_posi p, int color)
{
	mlx_pixel_put(w()->init, w()->window, p.x, p.y, color);
}

void	w__draw_linei(t_posi p1, t_posi p2, int color)
{
	int		i;
	t_posi	d;
	t_posi	increment;
	int	steps;

	i = 0;
	d.x = (p2.x - p1.x);
	d.y = (p2.y - p1.y);
	steps = abs(d.x) > abs(d.y) ? abs(d.x) : abs(d.y);
	increment.x = d.x / steps;
	increment.y = d.y / steps;
	while (i <= steps)
	{
		w__draw_pixeli(p1, color);
		p1.x += increment.x;
		p1.y += increment.y;
		i++;
	}
}

double	degree_to_radians(double degree)
{
	return (degree * PI/180);
}

double	get_vector_angle(t_posd vector)
{
	return (atan2(vector.y, vector.x));
}

void	print_cast_result(t_cast_result result)
{
	print_posd(result.delta_length, "result.delta_length");
	print_posd(result.side_length, "result.side_length");
	print_posi(result.map_intersection_pos, "result.map_intersection_pos");
	printf("side %i\n", result.side);
	printf("\n\n");
}

t_cast_result	cast_vector(t_posd pos, t_posd ray_dir)
{
	double	side_dist_x;  // side x distance --> The distance between the first intersection with the next x square
	double	side_dist_y;  // side y distance --> The distance between the first intersection with the next y square
	double	delta_dist_x; // delta x distance -> The distance between the next intersection with the next x square
	double	delta_dist_y; // delta y distance -> The distance between the next intersection with the next y square
	t_posi	step;
	t_posi	map; // integer map position
	int		has_hit_wall;
	int		side;

	has_hit_wall = 0;
	map.x = pos.x;
	map.y = pos.y;

	// print_posd(pos,"pos");
	// print_posd(ray_dir, "ray_dir");

	if (ray_dir.x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir.y);

	// printf("delta_dist_x %f\n", delta_dist_x);
	// printf("delta_dist_y %f\n", delta_dist_y);
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist_x = (pos.x - map.x) * delta_dist_x;
	}
	else
	{
		step.x = 1;
		side_dist_x = (map.x + 1.0 - pos.x) * delta_dist_x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist_y = (pos.y - map.y) * delta_dist_y;
	}
	else
	{
		step.y = 1;
		side_dist_y = (map.y + 1.0 - pos.y) * delta_dist_y;
	}

	while (has_hit_wall == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map.y += step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (state()->world_map[map.x][map.y] > 0) has_hit_wall = 1;
	}

	t_cast_result result;
	result.map_intersection_pos = map;
	result.side_length = create_posd(side_dist_x, side_dist_y);
	result.side = side;
	result.delta_length = create_posd(delta_dist_x, delta_dist_y);
	print_cast_result(result);
	return (result);
}


static void	renderer(int world_map[MAP_HEIGHT][MAP_WIDTH], t_posd pos, t_posd dir, t_posd plane, int x)
{
	double	camera_x;
	t_posd	ray_dir;
	t_posi	map; // integer map position
	double	side_dist_x;  // side x distance --> The distance between the first intersection with the next x square
	double	side_dist_y;  // side y distance --> The distance between the first intersection with the next y square
	double	delta_dist_x; // delta x distance -> The distance between the next intersection with the next x square
	double	delta_dist_y; // delta y distance -> The distance between the next intersection with the next y square
	double	perp_wall_dist; // perpendicular distance
	t_posi	step;
	int		has_hit_wall;
	int		side; // was a NS or a EW wall hit
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	camera_x = 2 * x / w()->width - 1;
	ray_dir.x = dir.x + plane.x * camera_x;
	ray_dir.y = dir.y + plane.y * camera_x;

	map.x = pos.x;
	map.y = pos.y;

	if (ray_dir.x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir.y);

	// print_posd(ray_dir, "ray_dir");
	// printf("delta_dist x:%f, y:%f\n", delta_dist_x, delta_dist_y);
	// Calculate the step
	// Calculate the first side distance (for both axis) after casting the ray
	usleep(100);
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist_x = (pos.x - map.x) * delta_dist_x;
	}
	else
	{
		step.x = 1;
		side_dist_x = (map.x + 1.0 - pos.x) * delta_dist_x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist_y = (pos.y - map.y) * delta_dist_y;
	}
	else
	{
		step.y = 1;
		side_dist_y = (map.y + 1.0 - pos.y) * delta_dist_y;
	}

	has_hit_wall = 0;


	//perform DDA
	while (has_hit_wall == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map.y += step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (world_map[map.x][map.y] > 0) has_hit_wall = 1;
	}

	// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if (side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y - delta_dist_y);

	//Calculate height of line to draw on screen
	line_height = (w()->height / perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + w()->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + w()->height / 2;
	if (draw_end >= w()->height)
		draw_end = w()->height - 1;

	// if (side == 1)
	// 	printf("---------------- SIDE 1 -------------------\n");
	// else
	// 	printf("---------------- SIDE 0 -------------------\n");
	//choose wall color
	switch (world_map[map.x][map.y])
	{
		case 1:  color = 0xFF0000;  break; //red
		case 2:  color = 0x00FF00;  break; //green
		case 3:  color = 0x0000FF;   break; //blue
		case 4:  color = 0xFFFFFF;  break; //white
		default: color = 0xFFFF00; break; //yellow
	}

	// give x and y sides different brightness
	if (side == 1) color = color / 2;

	// draw the pixels of the stripe as a vertical line
	t_posi p = { x: x, y: draw_start };
	t_posi pend = { x: x, y: draw_end };

	w__draw_linei(p, pend, color);
}

void	render(void)
{
	int	x;
	int	y;
	int	TILE_SIZE = w()->width / MAP_WIDTH;
	int color;

	x = 0;
	y = 0;

	while (x < MAP_WIDTH)
	{
		y = 0;
		while (y < MAP_HEIGHT)
		{

			switch (state()->world_map[x][y])
			{
				case 1:  color = 0xFF0000;  break; //red
				case 2:  color = 0x00FF00;  break; //green
				case 3:  color = 0x0000FF;   break; //blue
				case 4:  color = 0xFFFFFF;  break; //white
				default: color = 0xFFFF00; break; //yellow
			}
			if (state()->world_map[x][y] != 0)
				w__draw_square_fill(
					create_posd(x * TILE_SIZE, y * TILE_SIZE),
					create_posd(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE),
					color
				);
			// if (state()->world_map[x][y] == 0)
			// 	w__draw_square(
			// 		create_posd(x * TILE_SIZE, y * TILE_SIZE),
			// 		create_posd(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE),
			// 		color
			// 	);
			// else
			// 	w__draw_square_fill(
			// 		create_posd(x * TILE_SIZE, y * TILE_SIZE),
			// 		create_posd(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE),
			// 		color
			// 	);
			y++;
		}
		x++;
	}


	t_posd pos = state()->player_pos;
	pos.x = (pos.x * TILE_SIZE) - (TILE_SIZE / 2);
	pos.y = (pos.y * TILE_SIZE) - (TILE_SIZE / 2);
	w__draw_square_fill(
		create_posd(pos.x, pos.y),
		create_posd(pos.x + TILE_SIZE, pos.y + TILE_SIZE),
		BLUE
	);

	t_posd	final;
	t_posd ray_dir;

	for (int i = -33; i < 33; i++)
	{
		final.x = state()->player_pos.x * TILE_SIZE;
		final.y = state()->player_pos.y * TILE_SIZE;

		// print_posd(state()->player_dir, "state()->player_dir");
		// print_posd(state()->player_plane, "state()->player_plane");
		// printf("radians: %f\n", degree_to_radians(i));
		ray_dir.x = state()->player_dir.x + state()->player_plane.x * degree_to_radians(i);
		ray_dir.y = state()->player_dir.y + state()->player_plane.y * degree_to_radians(i);
		print_posd(ray_dir, "ray_dir");
		t_cast_result res = cast_vector(state()->player_pos, ray_dir);
		final.x = res.side_length.x + (w()->width * cos(get_vector_angle(ray_dir)));
		final.y = res.side_length.y + (w()->height * sin(get_vector_angle(ray_dir)));
		w__draw_line(
			create_posd(state()->player_pos.x * TILE_SIZE, state()->player_pos.y * TILE_SIZE),
			create_posd(final.x * TILE_SIZE, final.y * TILE_SIZE),
			PURPLE
		);

	}
	// for (int i = 0; i < w()->width; i++)
	// {
	// 	final.x = state()->player_pos.x * TILE_SIZE;
	// 	final.y = state()->player_pos.y * TILE_SIZE;

	// 	double camera_x = 2 * x / w()->width - 1;
	// 	ray_dir.x = state()->player_dir.x + state()->player_plane.x * camera_x;
	// 	ray_dir.y = state()->player_dir.y + state()->player_plane.y * camera_x;
	// 	t_cast_result res = cast_vector(state()->player_pos, ray_dir);
	// 	// print_cast_result(res);
	// 	double perp_wall_dist;
	// 	// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	// 	if (res.side == 0)
	// 		perp_wall_dist = (res.side_length.x - res.delta_length.x);
	// 	else
	// 		perp_wall_dist = (res.side_length.y - res.delta_length.y);

	// 	// printf("perp_wall_dist %f\n", perp_wall_dist);

	// 	switch (state()->world_map[res.map_intersection_pos.x][res.map_intersection_pos.y])
	// 	{
	// 		case 1:  color = 0xFF0000; break; //red
	// 		case 2:  color = 0x00FF00; break; //green
	// 		case 3:  color = 0x0000FF; break; //blue
	// 		case 4:  color = 0xFFFFFF; break; //white
	// 		default: color = 0xFFFF00; break; //yellow
	// 	}

	// 	if (res.side == 1) color = color / 2;
	// 	//Calculate height of line to draw on screen
	// 	double line_height = (w()->height / perp_wall_dist);
	// 	// printf("line_height %f\n", line_height);

	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	double draw_start = -line_height / 2 + w()->height / 2;
	// 	if (draw_start < 0)
	// 		draw_start = 0;
	// 	double draw_end = line_height / 2 + w()->height / 2;
	// 	if (draw_end >= w()->height)
	// 		draw_end = w()->height - 1;


	// 	w__draw_line(
	// 		create_posd(i, draw_start),
	// 		create_posd(i, draw_end),
	// 		color
	// 	);
	// }
}

int	w__render(int world_map[MAP_HEIGHT][MAP_WIDTH])
{
	int		x;
	t_posd	pos; // x and y start position
	t_posd	dir; // vector -> initial direction vector
	t_posd	plane; // vector -> the 2d raycaster version of camera plane

	double	time; //time of current frame
	double	oldTime; //time of previous frame

	x = 0;
	time = 0;
	oldTime = 0;

	render();

	while (x < w()->width)
	{
		// w__draw_line(create_posd(x /2, 0), create_posd(x /2, w()->height / 3), 0xfffff);
		// renderer(world_map, state()->player_pos, state()->player_dir, state()->player_plane, x);
		x++;
	}

	//speed modifiers
	state()->player_move_speed = 0.16 * 5.0; //the constant value is in squares/second
	state()->player_rot_speed = 0.16 * 3.0; //the constant value is in radians/second

	return (0);
}
