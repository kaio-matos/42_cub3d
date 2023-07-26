/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:36:31 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	int		null_byte;

	null_byte = 1;
	srclen = ft_strlen(src);
	if (srclen + null_byte < size)
		ft_memcpy(dst, (char *)src, srclen + null_byte);
	else if (size != 0)
	{
		ft_memcpy(dst, (char *)src, size);
		dst[size - null_byte] = '\0';
	}
	return (srclen);
}
