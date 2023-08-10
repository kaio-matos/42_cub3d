#include <cub.h>

void	w__draw_pixel(t_posd p, int color)
{
	// move to other draw functions for better performance
	if (p.x < 0)
		p.x = 0;
	if (p.x > w()->width)
		p.x = w()->width;
	if (p.y < 0)
		p.y = 0;
	if (p.y > w()->height)
		p.y = w()->height;
	mlx_pixel_put(w()->init, w()->window, p.x, p.y, color);
}

void	w__draw_line(t_posd p1, t_posd p2, int color)
{
	int		i;
	t_posd	d;
	t_posd	increment;
	double	steps;

	i = 0;
	d.x = (p2.x - p1.x);
	d.y = (p2.y - p1.y);
	steps = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	increment.x = d.x / steps;
	increment.y = d.y / steps;
	while (i <= steps)
	{
		w__draw_pixel(p1, color);
		p1.x += increment.x;
		p1.y += increment.y;
		i++;
	}
}

void	w__draw_line_weight(t_posd p1, t_posd p2, int color, int weight)
{
	int		i;
	t_posd	d;
	t_posd	increment;
	double	steps;
	int		current_w;

	i = 0;
	d.x = (p2.x - p1.x);
	d.y = (p2.y - p1.y);
	steps = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	increment.x = d.x / steps;
	increment.y = d.y / steps;
	current_w = weight;

	while (i <= steps)
	{
		current_w = 0;
		while (current_w <= weight)
		{
			w__draw_pixel(create_posd(p1.x + current_w, p1.y), color); // fix
			w__draw_pixel(create_posd(p1.x, p1.y + current_w), color);
			current_w++;
		}
		p1.x += increment.x;
		p1.y += increment.y;
		i++;
	}
}

void	w__draw_circle(t_posd p, int r, int color)
{
	double	i;
	double	angle;
	t_posd	current;

	i = 0;
	while (i < 360)
	{
		angle = i;
		current.x = r * cos(angle * PI / 180);
		current.y = r * sin(angle * PI / 180);
		w__draw_pixel(
			create_posd(p.x + current.x, p.y + current.y),
			color
		);
		i += 0.1;
	}
}

void	w__draw_circle_fill(t_posd p, int r, int color)
{
	double	i;
	double	angle;
	t_posd	current;

	while (r)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;
			current.x = r * cos(angle * PI / 180);
			current.y = r * sin(angle * PI / 180);
			w__draw_pixel(
				create_posd(p.x + current.x, p.y + current.y),
				color
			);
			i += 0.1;
		}
		r--;
	}
}

void	w__draw_square(t_posd corner1, t_posd corner4, int color)
{
	double	dist_x;
	double	dist_y;
	t_posd	corner2;
	t_posd	corner3;

	dist_x = fabs(corner1.x - corner4.x);
	dist_y = fabs(corner1.y - corner4.y);
	corner2 = create_posd(corner1.x + dist_x, corner1.y);
	corner3 = create_posd(corner1.x, corner1.y + dist_y);

	w__draw_line(corner1, corner2, color);
	w__draw_line(corner1, corner3, color);
	w__draw_line(corner2, corner4, color);
	w__draw_line(corner3, corner4, color);
}

void	w__draw_square_fill(t_posd corner1, t_posd corner4, int color)
{
	double	dist_x;
	double	dist_y;
	double	x;
	double	y;

	dist_x = fabs(corner1.x - corner4.x);
	dist_y = fabs(corner1.y - corner4.y);
	x = corner1.x;
	while (x < dist_x + corner1.x)
	{
		y = corner1.y;
		while (y < dist_y + corner1.y)
		{
			w__draw_pixel(create_posd(x, y), color);
			y++;
		}
		x++;
	}
}
