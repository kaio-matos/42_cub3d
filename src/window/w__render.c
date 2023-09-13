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

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

unsigned long	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	render_rays(t_img *image)
{
	int				r;
	double			ra;
	double			ca;
	t_cast_result	cast;
	double			dist;

	ra = fix_angle(state()->player_angle + 30);
	t_img	original;
	original.img = mlx_xpm_file_to_image(w()->init, "textures/wall.xpm", &original.width, &original.height);
	original.addr = mlx_get_data_addr(original.img, &original.bits_per_pixel, &original.line_length, &original.endian);
	for (r = 0; r < 66; r++)
	{
		cast = cast_ray(state()->player_pos, ra);
		w__draw_line(
			image,
			state()->player_pos,
			cast.ray,
			PURPLE
		);
		// 3D walls
		ca = fix_angle(state()->player_angle - ra);
		dist = cast.distance * cos(degree_to_radians(ca));
		double lineH = (MAP_LENGTH * SCREEN_HEIGHT) / dist;
		float ty_step = 16.0 / (float) lineH;
		float ty_off = 0;
		if (lineH > SCREEN_HEIGHT)
		{
			ty_off = (lineH - SCREEN_HEIGHT) / 2.0;
			lineH = SCREEN_HEIGHT;
		}
		int	lineOff = (SCREEN_HEIGHT >> 1) - ((int) lineH >> 1);

		int y;
		float ty = ty_off * ty_step;
		float tx;
		int PX_SIZE = 1;

		if (cast.shade == 1)
		{
			tx = (int) (cast.ray.x / 2.0) % PX_SIZE;
			if (ra > 180)
				tx = PX_SIZE - tx;
		} else
		{
			tx = (int) (cast.ray.y / 2.0) % PX_SIZE;
			if (ra < 90 && ra < 270)
				tx = PX_SIZE - tx;
		}

		ty += PX_SIZE;
		for (y = 0; y < lineH; y += PX_SIZE)
		{
			int OFFSET = 530;
			float y_percentage = ((y * 100) / lineH) / 100;
			float x_percentage = ((cast.ray.x + cast.ray.y) / MAP_LENGTH) - (int)((cast.ray.x + cast.ray.y) / MAP_LENGTH);
			int proportional_y_position = (int)(y_percentage * original.height);
			int proportional_x_position = (int)(x_percentage * original.width);
			int p1 = proportional_x_position * (original.bits_per_pixel / 8);
			int p2 = proportional_y_position * (original.width * (original.bits_per_pixel / 8));

			t_posd p_start = create_posd(r * 8 + 530, lineOff + y);
			t_posd p_end = create_posd(r * 8 + 530, lineOff + y + PX_SIZE);
			int color = *(int*)(original.addr + p1 + p2);

			w__draw_line_weight(
				image,
				p_start,
				p_end,
				create_trgb(get_t(color), get_r(color), get_g(color), get_b(color)), // TODO add shade
				8
			);
		}
		ra = fix_angle(ra - 1);
	}
	mlx_destroy_image(w()->init, original.img);
}

void	render_player(t_img *image)
{
	w__draw_square_fill(
		image,
		create_posd(state()->player_pos.x - 4, state()->player_pos.y - 4),
		create_posd(state()->player_pos.x + 4, state()->player_pos.y + 4),
		PURPLE
	);

	w__draw_line(
		image,
		create_posd(state()->player_pos.x, state()->player_pos.y),
		create_posd(state()->player_pos.x + state()->player_delta.x * 5, state()->player_pos.y + state()->player_delta.y * 5),
		PURPLE
	);
}

void	render_map(t_img *image)
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
					image,
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
	t_img	image;

	double	time; //time of current frame
	double	oldTime; //time of previous frame

	image = w__create_image(w()->init, w()->width, w()->height);
	x = 0;
	time = 0;
	oldTime = 0;
	render_map(&image);
	render_player(&image);
	render_rays(&image);

	mlx_put_image_to_window(w()->init, w()->window, image.img, 0, 0); // TODO
	mlx_destroy_image(w()->init, image.img);

	state()->player_move_speed = 0.16 * 5.0; //the constant value is in squares/second
	state()->player_rot_speed = 0.16 * 3.0; //the constant value is in radians/second

	return (0);
}
