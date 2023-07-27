/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:48:52 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/10/18 03:00:43 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxdup(char **mtx, size_t rows)
{
	char	**mtx_cpy;
	size_t	i;

	i = 0;
	if (!rows)
		return (NULL);
	mtx_cpy = ft_salloc((rows + 1) * sizeof(char *));
	while (i < rows && mtx[i])
	{
		mtx_cpy[i] = ft_strdup(mtx[i]);
		i++;
	}
	mtx_cpy[i] = NULL;
	return (mtx_cpy);
}
