/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 00:09:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/15 23:38:50 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	deal_args(t_slot finded, va_list args, int printed, int fd)
{
	if (*finded.string == '\0')
		return (printed);
	printed += ft_putstrn_fd(finded.string, finded.p_initial, fd);
	if (finded.length == -1)
		return (printed);
	if (finded.conversion == 'c')
		printed += deal_with_c(va_arg(args, int), fd);
	if (finded.conversion == 's')
		printed += deal_with_s(va_arg(args, char *), fd);
	if (finded.conversion == 'p')
		printed += deal_with_p(va_arg(args, long long int), fd);
	if (finded.conversion == 'd')
		printed += deal_with_d(va_arg(args, int), fd);
	if (finded.conversion == 'i')
		printed += deal_with_i(va_arg(args, int), fd);
	if (finded.conversion == 'u')
		printed += deal_with_u(va_arg(args, unsigned int), fd);
	if (finded.conversion == 'x')
		printed += deal_with_x(va_arg(args, unsigned int), fd);
	if (finded.conversion == 'X')
		printed += deal_with_x_upper(va_arg(args, unsigned int), fd);
	if (finded.conversion == '%')
		printed += deal_with_percent('%', fd);
	finded.string += finded.p_end + 1;
	return (deal_args(get_slot(finded.string, 0), args, printed, fd));
}
