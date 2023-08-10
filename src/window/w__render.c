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

double dist(double ax, double ay, double bx, double by, double ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	render_rays()
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xoffset;
	double	yoffset;
	double	distT;

	ra = state()->player_angle - DR*30;
	// Make sure the angle is withing bounds
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;

	for (r = 0; r < 66; r++)
	{
		// Check Horizontal Lines
		dof = 0;
		double distH = 10000000;
		double hx = state()->player_pos.x;
		double hy = state()->player_pos.y;
		double aTan = -1 / tan(ra); // fix issue with big result
		// 180degrees
		if (ra > PI)  // looking up
		{
			//>> 6 dividign by 64
			ry = (((int) state()->player_pos.y >> 6) << 6) - 0.0001;
			rx = (state()->player_pos.y - ry) * aTan + state()->player_pos.x;
			yoffset = -64;
			xoffset = -yoffset * aTan;
		}
		if (ra < PI)  // looking down
		{
			ry = (((int) state()->player_pos.y >> 6) << 6) + 64;
			rx = (state()->player_pos.y - ry) * aTan + state()->player_pos.x;
			yoffset = 64;
			xoffset = -yoffset * aTan;
		}
		if (ra == 0 || ra == PI || ra == 2*PI)  // looking straght left or right
		{
			rx = state()->player_pos.x;
			ry = state()->player_pos.y;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * 8 + mx;

			if (mp > 0 && mp < 8 * 8 && state()->world_map[mp] > 0)
			{
				hx = rx;
				hy = ry;
				distH = dist(state()->player_pos.x, state()->player_pos.y, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xoffset;
				ry += yoffset;
				dof += 1;
			}
		}

		// Check Vertical Lines
		dof = 0;
		double distV = 10000000;
		double vx = state()->player_pos.x;
		double vy = state()->player_pos.y;
		double nTan = -tan(ra);
		// 180degrees
		if (ra > P2 && ra < P3)  // looking left
		{
			//>> 6 dividign by 64
			rx = (((int) state()->player_pos.x >> 6) << 6) - 0.0001;
			ry = (state()->player_pos.x - rx) * nTan + state()->player_pos.y;
			xoffset = -64;
			yoffset = -xoffset * nTan;
		}
		if (ra < P2 || ra > P3)  // looking right
		{
			rx = (((int) state()->player_pos.x >> 6) << 6) + 64;
			ry = (state()->player_pos.x - rx) * nTan + state()->player_pos.y;
			xoffset = 64;
			yoffset = -xoffset * nTan;
		}
		if (ra == 0 || ra == PI || ra == 2*PI)  // looking straght left or right
		{
			rx = state()->player_pos.x;
			ry = state()->player_pos.y;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * 8 + mx;

			if (mp > 0 && mp < 8 * 8 && state()->world_map[mp] > 0)
			{
				vx = rx;
				vy = ry;
				distV = dist(state()->player_pos.x, state()->player_pos.y, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xoffset;
				ry += yoffset;
				dof += 1;
			}
		}

		// Get the smaller distance
		int side;
		if (distV < distH)
		{
			rx = vx;
			ry = vy;
			distT = distV;
			side = 1;
		}
		if (distH < distV)
		{
			rx = hx;
			ry = hy;
			distT = distH;
			side = 0;
		}

		w__draw_line(
			create_posd(state()->player_pos.x, state()->player_pos.y),
			create_posd(rx, ry),
			PURPLE
		);

		// 3D walls
		double ca = state()->player_angle - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		distT = distT * cos(ca);
		double lineH = 64 * 320 / distT;
		if (lineH > 320)
			lineH = 320;

		double lineO = 160 - lineH / 2;

		int color = RED;
		if (side == 1)
			color = color * 0.99;
		w__draw_line_weight(
			create_posd(r * 8 + 530, lineO),
			create_posd(r * 8 + 530, lineH + lineO),
			color,
			8
		);

		ra += DR;
		// Make sure the angle is withing bounds
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
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
