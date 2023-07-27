/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:28:10 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/09 20:28:21 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxpush(char **mtx, char *string)
{
	char	**new;
	int		length;
	int		i;

	i = 0;
	length = ft_mtxlen(mtx);
	new = ft_salloc((length + 2) * sizeof(char *));
	while (i < length)
	{
		new[i] = mtx[i];
		i++;
	}
	new[i] = string;
	new[i + 1] = NULL;
	free(mtx);
	return (new);
}
