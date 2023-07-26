/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:40:39 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	check_in_range(char c, const char *set)
{
	int	is_inside_range;

	is_inside_range = 0;
	while (*set)
	{
		if (c == *set)
			is_inside_range = 1;
		set++;
	}
	return (is_inside_range);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		i;

	while (check_in_range(*s1, set) && *s1 != '\0')
		s1++;
	i = ft_strlen(s1);
	while (check_in_range(s1[i - 1], set) && i - 1 > 0)
		i--;
	trimmed_str = ft_substr(s1, 0, i);
	return (trimmed_str);
}
