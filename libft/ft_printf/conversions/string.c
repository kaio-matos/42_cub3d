/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:59 by coder             #+#    #+#             */
/*   Updated: 2022/11/15 23:46:04 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_with_s(char *arg, int fd)
{
	if (arg == NULL)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(arg, fd));
}
