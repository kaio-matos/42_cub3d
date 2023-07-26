/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:01:54 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_temp;
	char	*dest_temp;

	if (src == NULL && dest == NULL)
		return (dest);
	src_temp = (char *)src;
	dest_temp = (char *)dest;
	while (n--)
	{
		*dest_temp = *src_temp;
		src_temp++;
		dest_temp++;
	}
	return (dest);
}
