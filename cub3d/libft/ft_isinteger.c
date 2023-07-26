/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:37:51 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/02/16 21:23:41 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_less_or_plus(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	is_integer(char *number, int sign)
{
	long long	converted;

	if (is_less_or_plus(number[0]) && !ft_isdigit(number[1]))
		return (0);
	if ((ft_strlen(number) + sign) > MAX_INT_LENGTH)
		return (0);
	converted = ft_atol(number);
	if (converted > __INT_MAX__ || converted < -__INT_MAX__ - 1)
		return (0);
	return (1);
}

int	ft_isinteger(char *string)
{
	int	sign;
	int	i;

	sign = 0;
	i = 0;
	if (string[i] == '-')
		sign = -1;
	while (string[i] && is_less_or_plus(string[i]))
	{
		if (i != 0 && (is_less_or_plus(string[i - 1]) || !string[i + 1]))
			return (0);
		i++;
	}
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	if (!is_integer(string, sign))
		return (0);
	return (1);
}
