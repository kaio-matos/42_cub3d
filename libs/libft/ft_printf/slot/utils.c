/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:35:50 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:32:38 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isconversion(char c)
{
	char	*valid_chars;
	char	*result;

	valid_chars = "cspdiuxX%";
	result = ft_strchr(valid_chars, c);
	if (result != NULL && *result != '\0')
		return (1);
	return (0);
}

int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int	ft_strchri(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 127)
		c %= 256;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}
