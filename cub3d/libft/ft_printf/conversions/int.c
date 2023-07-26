/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:22:03 by coder             #+#    #+#             */
/*   Updated: 2022/11/15 23:55:04 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_with_i(int arg, int fd)
{
	int	printed;

	printed = 0;
	if (arg == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (arg < 0)
	{
		arg = arg * -1;
		printed += ft_putchar('-');
	}
	return (ft_putnbase_fd(arg, "0123456789", fd) + printed);
}
