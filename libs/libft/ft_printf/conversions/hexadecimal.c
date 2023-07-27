/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:22:06 by coder             #+#    #+#             */
/*   Updated: 2022/11/15 23:55:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_with_x(unsigned int arg, int fd)
{
	return (ft_putnbase_fd(arg, "0123456789abcdef", fd));
}

int	deal_with_x_upper(unsigned int arg, int fd)
{
	return (ft_putnbase_fd(arg, "0123456789ABCDEF", fd));
}
