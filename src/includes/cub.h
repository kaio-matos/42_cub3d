/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:51:43 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/07/27 21:54:34 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# include <stdio.h>
# include <libft.h>
# include <mlx.h>
# include <math.h>

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
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

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

/******************************************************************************\
* WINDOW																	   *
\******************************************************************************/

t_window	*w(void);
void		w__init(int width, int height);
void		w__open(void);
int			w__close(void);

int			w__render(int world_map[MAP_HEIGHT][MAP_WIDTH]);

#endif
