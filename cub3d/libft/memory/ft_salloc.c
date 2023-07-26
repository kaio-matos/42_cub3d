/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_salloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:51:25 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/01/23 19:20:51 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_salloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem && size > 0)
	{
		ft_fprintf(2, "MEMORY ALLOCATION ERROR");
		exit(EXIT_FAILURE);
	}
	return (mem);
}
