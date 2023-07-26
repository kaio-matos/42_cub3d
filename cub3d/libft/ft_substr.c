/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:22:44 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	count_size(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	s += start;
	while (*s && i < len)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	size = count_size(s, start, len);
	i = 0;
	s += start;
	substr = (char *)malloc(sizeof(char) * size + 1);
	if (!substr)
		return (NULL);
	while (*s && i < len)
	{
		substr[i] = *s;
		i++;
		s++;
	}
	substr[i] = '\0';
	return (substr);
}
