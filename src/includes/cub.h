/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:51:43 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/07/26 22:07:22 by kmatos-s         ###   ########.fr       */
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

typedef struct s_window
{
	void	*window;
	void	*init;
	int		width;
	int		height;
}	t_window;

/******************************************************************************\
* WINDOW																	   *
\******************************************************************************/

t_window	*w(void);
void		w__init(int width, int height);
void		w__open(void);
int			w__close(void);

int			w__render(void);

#endif
