/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;

	if (!size || !nmemb)
		return (NULL);
	if (((nmemb * size) / nmemb) != size)
		return (NULL);
	new = (char *)malloc(size * nmemb);
	if (!new)
		return (NULL);
	ft_bzero(new, size * nmemb);
	return (new);
}
