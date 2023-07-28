#include <cub.h>

static int	renderer(t_posd pos, t_posd dir, t_posd plane, int x)
{
	double	camera_x;
	t_posd	ray_dir;
	t_posi	map; // integer map position
	t_posd	side_dist; // side distance
	t_posd	delta_dist; // delta distance
	t_posd	perp_dist; // perpendicular distance
	t_posi	step;
	int		has_hit_wall;
	int		side; // was a NS or a EW wall hit

	camera_x = 2 * x / MAP_WIDTH - 1;
	ray_dir.x = dir.x * plane.x * camera_x;
	ray_dir.y = dir.y * plane.y * camera_x;

	map.x = pos.x;
	map.y = pos.y;

	if (ray_dir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1 / ray_dir.y);

	has_hit_wall = 0;

}

int	w__render(int world_map[MAP_HEIGHT][MAP_WIDTH])
{
	int		x;
	t_posd	pos;
	t_posd	dir;
	t_posd	plane;

	x = 0;
	pos.x = 22;
	pos.y = 12;

	dir.x = -1;
	dir.y = 0;

	plane.x = 0;
	plane.y = 0.66;

	while (x < MAP_WIDTH)
	{
		renderer(pos, dir, plane, x);
		x++;
	}

	return (0);
}
