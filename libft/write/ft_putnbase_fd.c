/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbase_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:31:23 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/15 23:56:09 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putnbase_fd(unsigned long long nb, char *base, int fd)
{
	int		printed;
	size_t	base_len;

	printed = 0;
	base_len = ft_strlen(base);
	if (nb >= base_len)
		printed += ft_putnbase_fd(nb / base_len, base, fd);
	printed += ft_putchar_fd(base[nb % base_len], fd);
	return (printed);
}
