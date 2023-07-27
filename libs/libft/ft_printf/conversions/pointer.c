/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:22:01 by coder             #+#    #+#             */
/*   Updated: 2022/11/15 23:45:37 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_with_p(long long int arg, int fd)
{
	int	printed;

	printed = 0;
	if (!arg)
		return (ft_putstr_fd("(nil)", fd));
	printed += ft_putstr_fd("0x", fd);
	printed += ft_putnbase_fd(arg, "0123456789abcdef", fd);
	return (printed);
}
