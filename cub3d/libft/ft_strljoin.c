/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:07:22 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/06 20:24:31 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strljoin(char const *s1, char const *s2, int bytes)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * bytes + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 != NULL && *s1 && i < bytes)
	{
		new_str[i] = *s1;
		i++;
		s1++;
	}
	while (s2 != NULL && *s2 && i < bytes)
	{
		new_str[i] = *s2;
		i++;
		s2++;
	}
	new_str[i] = '\0';
	return (new_str);
}
