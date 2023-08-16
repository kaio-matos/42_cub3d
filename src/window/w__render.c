#include <cub.h>

double	degree_to_radians(double degree)
{
	return (degree * PI/180);
}
int		fix_angle(int degree)
{
	if (degree > 359)
		degree -= 360;
	if (degree < 0)
		degree += 360;
	return degree;
}

double	get_vector_angle(t_posd vector)
{
	return (atan2(vector.y, vector.x));
}

double dist(double ax, double ay, double bx, double by, double ang)
{
	return (cos(degree_to_radians(ang)) * (bx - ax) - sin(degree_to_radians(ang)) * (by - ay));
}

typedef struct s_closer_cast_result {
	t_posd	ray;
	t_posd	offset;
	int		dof;
}	t_closer_cast_result;


typedef struct s_cast_result {
	t_posd	ray;
	int		distance;
}	t_cast_result;


/**
 * It will return the position of the
 * first encounter with a boundary in the x axis
 * and also the offset
*/
t_closer_cast_result	cast_x_closer_ray(t_posd from, int angle)
{
	t_closer_cast_result	r;
	double					tang;

	// Check Horizontal Lines
	r.dof = 0;
	tang = tan(degree_to_radians(angle));
	tang = 1.0 / tang;
	// 180degrees
	if (sin(degree_to_radians(angle)) > 0.001)  // looking up
	{
		//>> 6 =  dividing by MAP_LENGTH
		r.ray.y = (((int) from.y >> 6) << 6) - 0.0001;
		r.ray.x = (from.y - r.ray.y) * tang + from.x;
		r.offset.y = -MAP_LENGTH;
		r.offset.x = -r.offset.y * tang;
	}
	else if (sin(degree_to_radians(angle)) < -0.001)  // looking down
	{
		r.ray.y = (((int) from.y >> 6) << 6) + MAP_LENGTH;
		r.ray.x = (from.y - r.ray.y) * tang + from.x;
		r.offset.y = MAP_LENGTH;
		r.offset.x = -r.offset.y * tang;
	}
	else  // looking straght left or right
	{
		r.ray.x = from.x;
		r.ray.y = from.y;
		r.dof = 8;
	}
	return (r);
}

/**
 * It will return the position of the
 * first encounter with a boundary in the y axis
 * and also the offset
*/
t_closer_cast_result	cast_y_closer_ray(t_posd from, int angle)
{
	t_closer_cast_result	r;
	double					tang;

	r.dof = 0;
	tang = tan(degree_to_radians(angle));
	// 180degrees
	if (cos(degree_to_radians(angle)) > 0.001)  // looking left
	{
		//>> 6 =  dividing by MAP_LENGTH
		r.ray.x = (((int) from.x >> 6) << 6) + MAP_LENGTH;
		r.ray.y = (from.x - r.ray.x) * tang + from.y;
		r.offset.x = MAP_LENGTH;
		r.offset.y = -r.offset.x * tang;
	}
	else if (cos(degree_to_radians(angle)) < -0.001)  // looking right
	{
		r.ray.x = (((int) from.x >> 6) << 6) - 0.0001;
		r.ray.y = (from.x - r.ray.x) * tang + from.y;
		r.offset.x = -MAP_LENGTH;
		r.offset.y = -r.offset.x * tang;
	}
	else // looking up or down, no hit
	{
		r.ray.x = from.x;
		r.ray.y = from.y;
		r.dof = 8;
	}
	return (r);
}

/**
 * It will return the position of the
 * next encounter with a boundary in the x axis
*/
t_cast_result	cast_x_ray(int angle, t_posd from, t_posd offset)
{
	t_cast_result	r;
	t_posi			map;
	int				mp;
	double			ang_radians;
	int				dof;

	dof = 0;
	r.distance = 100000;
	ang_radians = degree_to_radians(angle);
	while (dof < 8)
	{
		map.x = (int) (from.x) >> 6;
		map.y = (int) (from.y) >> 6;
		mp = map.y * MAP_WIDTH + map.x;

		if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && state()->world_map[mp] > 0)
		{
			r.distance = cos(ang_radians) * (from.x - state()->player_pos.x) -
				sin(ang_radians) * (from.y - state()->player_pos.y);
			dof = 8;
		}
		else
		{
			from.x += offset.x;
			from.y += offset.y;
			dof += 1;
		}
	}
	r.ray = from;
	return (r);
}

/**
 * It will return the position of the
 * next encounter with a boundary in the y axis
*/
t_cast_result	cast_y_ray(int angle, t_posd from, t_posd offset)
{
	t_cast_result	r;
	t_posi			map;
	int				mp;
	double			ang_radians;
	int				dof;

	dof = 0;
	r.distance = 100000;
	ang_radians = degree_to_radians(angle);
	while (dof < 8)
	{
		map.x = (int) (from.x) >> 6;
		map.y = (int) (from.y) >> 6;
		mp = map.y * MAP_WIDTH + map.x;

		if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && state()->world_map[mp] > 0)
		{
			r.distance = cos(ang_radians) * (from.x - state()->player_pos.x) -
				sin(ang_radians) * (from.y - state()->player_pos.y);
			dof = 8;
		} // hit
		else
		{
			from.x += offset.x;
			from.y += offset.y;
			dof += 1;
		}
	}
	r.ray = from;
	return (r);
}


void	render_rays()
{
	int						r;
	int						mx;
	int						my;
	int						mp;
	int						dof;
	int						side;
	double					vx;
	double					vy;
	double					ry;
	double					rx;
	double					xoffset;
	double					ra;
	double					distH;
	double					yoffset;
	double					distT;
	double					distV;
	double					ca;
	double					Tan;
	t_closer_cast_result	closer_cast;
	t_cast_result			cast;

	ra = fix_angle(state()->player_angle + 30);

	for (r = 0; r < 66; r++)
	{
		side = 0;
		// Check Vertical Lines;
		Tan = tan(degree_to_radians(ra));
		closer_cast = cast_y_closer_ray(state()->player_pos, ra);
		dof = closer_cast.dof;
		rx = closer_cast.ray.x;
		ry = closer_cast.ray.y;
		xoffset = closer_cast.offset.x;
		yoffset = closer_cast.offset.y;

		distV = 100000;
		if (closer_cast.dof != 8)
		{
			cast = cast_y_ray(ra, closer_cast.ray, closer_cast.offset);
			distV = cast.distance;
			rx = cast.ray.x;
			ry = cast.ray.y;
		}
		vx = rx;
		vy = ry;

		// Check Horizontal Lines
		distH = 100000;
		Tan = 1.0 / Tan;
		closer_cast = cast_x_closer_ray(state()->player_pos, ra);
		dof = closer_cast.dof;
		rx = closer_cast.ray.x;
		ry = closer_cast.ray.y;
		xoffset = closer_cast.offset.x;
		yoffset = closer_cast.offset.y;

		if (closer_cast.dof != 8)
		{
			cast = cast_x_ray(ra, closer_cast.ray, closer_cast.offset);
			distH = cast.distance;
			rx = cast.ray.x;
			ry = cast.ray.y;
		}

		// Get the smaller distance
		if (distV < distH)
		{
			rx = vx;
			ry = vy;
			distH = distV;
		}

		w__draw_line(
			create_posd(state()->player_pos.x, state()->player_pos.y),
			create_posd(rx, ry),
			PURPLE
		);

		// 3D walls
		ca = fix_angle(state()->player_angle - ra);
		distH = distH * cos(degree_to_radians(ca));
		double lineH = MAP_LENGTH * 320 / distH;
		if (lineH > SCREEN_HEIGHT)
			lineH = SCREEN_HEIGHT;

		int	lineOff = SCREEN_HEIGHT / 2 - lineH / 2; // fancy way to divide by 2, who knows why.

		int color = RED;
		if (side == 1)
			color = color * 0.99;

		w__draw_line_weight(
			create_posd(r * 8 + 530, lineOff),
			create_posd(r * 8 + 530, lineH + lineOff),
			color,
			8
		);

		ra = fix_angle(ra - 1);
	}
}

void	render_player(void)
{
	w__draw_square_fill(
		create_posd(state()->player_pos.x - 4, state()->player_pos.y - 4),
		create_posd(state()->player_pos.x + 4, state()->player_pos.y + 4),
		PURPLE
	);

	w__draw_line(
		create_posd(state()->player_pos.x, state()->player_pos.y),
		create_posd(state()->player_pos.x + state()->player_delta.x * 5, state()->player_pos.y + state()->player_delta.y * 5),
		PURPLE
	);
}

void	render_map()
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	color;

	for (y = 0; y < MAP_HEIGHT; y++){
		for (x = 0; x < MAP_WIDTH; x++){
			if (state()->world_map[y*8+x] > 0)
			{
				xo = x * 64;
				yo = y * 64;
				switch (state()->world_map[y*8+x])
				{
					case 1:  color = 0xFF0000; break; //red
					case 2:  color = 0x00FF00; break; //green
					case 3:  color = 0x0000FF; break; //blue
					case 4:  color = 0xFFFFFF; break; //white
					default: color = 0xFFFF00; break; //yellow
				}
				w__draw_square_fill(
					create_posd(xo + 1, yo + 1),
					create_posd(xo + 64 - 1, yo + 64 - 1),
					color
				);
			}
		}

	}
}

int	w__render(int world_map[64])
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
	render_map();
	render_player();
	render_rays();


	state()->player_move_speed = 0.16 * 5.0; //the constant value is in squares/second
	state()->player_rot_speed = 0.16 * 3.0; //the constant value is in radians/second

	return (0);
}
