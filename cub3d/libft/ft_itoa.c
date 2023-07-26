/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:50:31 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	intchar(int n)
{
	return (n + '0');
}

int	get_int_len(int value)
{
	int	l;

	l = 1;
	if (value < 0)
	{
		value = -value;
		l++;
	}
	while (value > 9)
	{
		l++;
		value /= 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		abs_n;
	int		len;

	abs_n = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		abs_n = -n;
	len = get_int_len(n);
	number = (char *)malloc(len + 1);
	if (!number)
		return (NULL);
	number[len] = '\0';
	while (len)
	{
		if (n < 0 && len == 1)
			number[0] = '-';
		else
			number[len - 1] = intchar(abs_n % 10);
		abs_n /= 10;
		len--;
	}
	return (number);
}
