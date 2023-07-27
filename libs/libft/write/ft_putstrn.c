/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:30:42 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:43:11 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putstrn(char	*str, int n)
{
	int			i;
	int			printed;

	i = 0;
	printed = 0;
	while (*str && i < n)
	{
		printed += ft_putchar(str[i]);
		i++;
	}
	return (printed);
}
