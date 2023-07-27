/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:30:05 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:40:58 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putstr(char *str)
{
	int	printed;

	printed = 0;
	while (*str)
	{
		printed += ft_putchar(*str);
		str++;
	}
	return (printed);
}
