/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:31:23 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:40:54 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putnbase(unsigned long long nb, char *base)
{
	int		printed;
	size_t	base_len;

	printed = 0;
	base_len = ft_strlen(base);
	if (nb >= base_len)
		printed += ft_putnbase(nb / base_len, base);
	printed += ft_putchar(base[nb % base_len]);
	return (printed);
}
