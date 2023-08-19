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

int		screen_pos_to_map_pos(t_posd pos)
{
	int	py;
	int	px;
	int	res;

	py = pos.y / MAP_LENGTH;
	px = pos.x / MAP_LENGTH;
	res = (py * MAP_WIDTH) + px;
	if (res > MAP_LENGTH) return (0);
	return (res);
}

void	render_rays()
{
	int				r;
	double			ra;
	double			ca;
	t_cast_result	cast;
	double			dist;

	ra = fix_angle(state()->player_angle + 30);

	for (r = 0; r < 66; r++)
	{
		cast = cast_ray(state()->player_pos, ra);
		w__draw_line(
			state()->player_pos,
			cast.ray,
			PURPLE
		);
		// 3D walls
		ca = fix_angle(state()->player_angle - ra);
		dist = cast.distance * cos(degree_to_radians(ca));
		double lineH = (MAP_LENGTH * SCREEN_HEIGHT) / dist;
		float ty_step = 32.0 / (float) lineH;
		float ty_off = 0;
		if (lineH > SCREEN_HEIGHT)
		{
			ty_off = (lineH - SCREEN_HEIGHT) / 2.0;
			lineH = SCREEN_HEIGHT;
		}
		int	lineOff = (SCREEN_HEIGHT >> 1) - ((int) lineH >> 1);
		int color;

		// switch (state()->world_map[screen_pos_to_map_pos(cast.ray)])
		// {
		// 	case 1:  color = 0xFF0000; break; //red
		// 	case 2:  color = 0x00FF00; break; //green
		// 	case 3:  color = 0x0000FF; break; //blue
		// 	case 4:  color = 0xFFFFFF; break; //white
		// 	default: color = 0xFFFF00; break; //yellow
		// }
		int y;
		float ty = ty_off * ty_step;
		float tx;

		if (cast.shade == 1)
		{
			tx = (int) (cast.ray.x / 2.0) % 32;
			if (ra > 180)
				tx = 31 - tx;
		} else
		{
			tx = (int) (cast.ray.y / 2.0) % 32;
			if (ra < 90 && ra < 270)
				tx = 31 - tx;
		}

		ty += 32;
		for (y = 0; y < lineH; y++)
		{
			float c = All_Textures[(int) (ty) * 32 + (int) tx];
			if (c == 1)
				color = cast.shade == 0.5 ? 0xFFFFFF - 30 : 0xFFFFFF;
			else
				color = cast.shade == 0.5 ? 0x000000 + 30 : 0x000000;
			int w = -4;
			while (w < 4)
			{
				w__draw_pixel(
					create_posd(r * 8 + 530 + w, lineOff + y),
					color
				);
				w++;
			}
			// w__draw_line_weight(
			// 	create_posd(r * 8 + 530, lineOff),
			// 	create_posd(r * 8 + 530, lineOff + lineH),
			// 	color,
			// 	8
			// );
			ty += ty_step;
		}
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
