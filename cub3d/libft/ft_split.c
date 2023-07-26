/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:10:38 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:29:17 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static unsigned int	count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		j = 0;
		while (s[j + i] != c && s[j + i] != '\0')
			j++;
		if (j > 0)
		{
			i += j;
			counter++;
		}
		else
			i++;
	}
	return (counter);
}

static char	**fill_rows(char **rows, char const *s, char c, unsigned int n_rows)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < n_rows)
	{
		j = 0;
		while (*(s + j) != c && *(s + j) != '\0')
			j++;
		if (j > 0)
		{
			rows[i] = ft_substr(s, 0, j);
			if (!rows[i])
			{
				free(rows);
				return (NULL);
			}
			while (*(s + j) == c && *(s + j) != '\0')
				j++;
			s += j;
		}
		else
			s++;
	}
	return (rows);
}

char	**ft_split(char const *s, char c)
{
	char			**splitted;
	unsigned int	rows;

	while (*s == c && *s != '\0')
		s++;
	rows = count_words(s, c);
	splitted = (char **)malloc((rows + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted = fill_rows(splitted, s, c, rows);
	if (!splitted)
		return (NULL);
	splitted[rows] = NULL;
	return (splitted);
}
