/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:49:26 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/01 20:01:02 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_new_memory(void *content)
{
	ft_memory(PUSH, content);
}

void	ft_free_memory(void)
{
	ft_memory(FREE, NULL);
}
