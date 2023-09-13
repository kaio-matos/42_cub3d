#ifndef STRUCTS_H

typedef struct s_window
{
	void	*window;
	void	*init;
	int		width;
	int		height;
}	t_window;

typedef struct s_posi
{
	int	x;
	int	y;
}	t_posi;

typedef struct s_posd
{
	double	x;
	double	y;
}	t_posd;


typedef struct s_state
{
	t_posd	player_pos;
	t_posd	player_delta;
	double	player_angle;
	int		world_map[64];
	double	player_move_speed;
	double	player_rot_speed;
}	t_state;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

/******************************************************************************\
* WINDOW																	   *
\******************************************************************************/

typedef struct s_closer_cast_result {
	t_posd	ray;
	t_posd	offset;
	int		dof;
}	t_closer_cast_result;

typedef struct s_cast_result {
	t_posd	ray;
	int		distance;
	float	shade;
}	t_cast_result;

#endif
