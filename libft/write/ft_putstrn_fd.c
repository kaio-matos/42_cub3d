/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:30:42 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/15 23:37:47 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putstrn_fd(char *str, int n, int fd)
{
	int			i;
	int			printed;

	i = 0;
	printed = 0;
	while (*str && i < n)
	{
		printed += ft_putchar_fd(str[i], fd);
		i++;
	}
	return (printed);
}
