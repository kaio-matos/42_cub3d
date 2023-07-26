/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:41:48 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/15 23:43:22 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	printed;

	printed = 0;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
		printed++;
	}
	return (printed);
}
