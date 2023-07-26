/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:03:55 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src_temp;
	char	*dest_temp;

	src_temp = (char *)src;
	dest_temp = (char *)dest;
	if (src_temp < dest_temp)
	{
		while (n--)
			dest_temp[n] = src_temp[n];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
