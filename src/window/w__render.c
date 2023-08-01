#include <cub.h>

static void	draw_pixel(t_posi p, int color) {
	mlx_pixel_put(w()->init, w()->window, p.x, p.y, color);
}

static void	draw_linei(t_posi p1, t_posi p2, int color)
{
	//todo
}

static int	renderer(int world_map[MAP_HEIGHT][MAP_WIDTH], t_posd pos, t_posd dir, t_posd plane, int x)
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

	camera_x = 2 * x / SCREEN_WIDTH - 1;
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


	// Calculate the step
	// Calculate the first side distance (for both axis) after casting the ray
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

	//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if (side == 0) perp_wall_dist = (side_dist_x - delta_dist_x);
	else perp_wall_dist = (side_dist_y - delta_dist_y);


	//Calculate height of line to draw on screen
	line_height = (SCREEN_HEIGHT / perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0) draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;


	//choose wall color
	switch (world_map[map.x][map.y])
	{
		case 1:  color = 0xFFCCE5;  break; //red
		case 2:  color = 0x00FF00;  break; //green
		case 3:  color = 0x0000FF;   break; //blue
		case 4:  color = 0xFFFFFF;  break; //white
		default: color = 0xFFFF00; break; //yellow
	}

	// give x and y sides different brightness
	if (side == 1) color = color / 2;

	// draw the pixels of the stripe as a vertical line
	// verLine(x, draw_start, drawEnd, color);
	t_posi p = { x: 0, y: 0 };
	t_posi pend = { x: draw_start, y: draw_start };
	draw_linei(p, pend, color);
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
	pos.x = 22;
	pos.y = 12;

	dir.x = -1;
	dir.y = 0;

	plane.x = 0;
	plane.y = 0.66;

	// int	TILE_SIZE = 32;

	t_posi	center = {x: 300, y: 250};
	t_posi	current = {x: 490, y: 300};
	draw_pixel(current,0x00FF00);
	draw_linei(center, current, 0xFFFFFF);


	// while (x < MAP_WIDTH)
	// {
	// 	t_posi	center = {x: 300, y: 250};
	// 	t_posi	current = {x: 490, y: 300};
	// 	draw_linei(center, current, 0xFFFFFF);

	// 	// renderer(world_map, pos, dir, plane, x);
	// 	x++;
	// }

	return (0);
}
