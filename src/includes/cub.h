/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:51:43 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/09/13 21:05:33 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# include <stdio.h>
# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <structs.h>

/**
	Allowed Functions:

	open, close, read, write,
	printf, malloc, free, perror,
	strerror, exit

	- All functions of the math
	library (-lm man man 3 math)

	- All functions of the MinilibX
*/

# define WINDOW_X 16777216

# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define MAP_LENGTH 64

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Colors
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define PURPLE 0x912cee

# define PI 3.14159265358979323846
// Circle quadrants start angles
# define P2 PI / 2
# define P3 3 * PI / 2

# define DR 0.0174533 // one degree in radians

extern int All_Textures[];

/******************************************************************************\
* WINDOW																	   *
\******************************************************************************/

t_window	*w(void);
void		w__init(int width, int height);
void		w__open(void);
int			w__close(void);

int			w__render(int world_map[64]);

void		w__draw_pixel(t_img *image, t_posd p, int color);
void		w__draw_line(t_img *image, t_posd p1, t_posd p2, int color);
void		w__draw_line_weight(t_img *image, t_posd p1, t_posd p2, int color, int weight);
void		w__draw_square(t_img *image, t_posd corner1, t_posd corner4, int color);
void		w__draw_square_fill(t_img *image, t_posd corner1, t_posd corner4, int color);
void		w__draw_circle(t_img *image, t_posd p, int r, int color);
void		w__draw_circle_fill(t_img *image, t_posd p, int r, int color);
t_img		w__create_image(void *mlx_ptr, int width, int height);
t_cast_result	cast_ray(t_posd from, int angle);

/******************************************************************************\
* MODELS																	   *
\******************************************************************************/

/* Position */
t_posd	create_posd(double x, double y);
t_posi	create_posi(int x, int y);
t_posd	posi_to_posd(t_posi pi);
void	print_posi(t_posi p, char *name);
void	print_posd(t_posd p, char *name);

/******************************************************************************\
* STATE																		   *
\******************************************************************************/

t_state *state(void);
void	*textures(void); // TODO

/******************************************************************************\
* UTILS																		   *
\******************************************************************************/
t_parse_cub_result	parse_cub_file(char *content);

/******************************************************************************\
* UTILS																		   *
\******************************************************************************/

void	print_map(int array[MAP_HEIGHT][MAP_WIDTH]);



/******************************************************************************\
* MATH																		   *
\******************************************************************************/
double	degree_to_radians(double degree);
int		fix_angle(int degree);

#endif
