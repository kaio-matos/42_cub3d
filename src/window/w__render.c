#include <cub.h>

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

	while (x < MAP_WIDTH)
	{
		renderer(world_map, pos, dir, plane, x);
		x++;
	}

	return (0);
}
