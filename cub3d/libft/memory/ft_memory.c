/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 00:06:38 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/03 20:58:36 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_memory(void **memory, int memory_nodes);
static void	*push_memory(void **memory, void *payload, int memory_nodes);

void	ft_memory(enum e_memory_actions action, void *payload)
{
	static void	**memory;
	static int	memory_nodes;

	if (action == FREE)
		return (free_memory(memory, memory_nodes));
	if (!payload)
		return ;
	if (action == PUSH)
	{
		memory = push_memory(memory, payload, memory_nodes);
		memory_nodes++;
	}
}

static void	free_memory(void **memory, int memory_nodes)
{
	int	i;

	i = 0;
	if (!memory)
		return ;
	while (i < memory_nodes && memory[i] != NULL)
	{
		free(memory[i]);
		i++;
	}
	free(memory);
}

static void	*push_memory(void **memory, void *payload, int memory_nodes)
{
	void	**temporary;
	int		new_space_to_allocate;
	int		old_space_to_allocate;

	temporary = memory;
	old_space_to_allocate = memory_nodes * sizeof(void *);
	new_space_to_allocate = (memory_nodes + 1) * sizeof(void *);
	memory = ft_salloc(new_space_to_allocate);
	if (temporary)
	{
		ft_memcpy(memory, temporary, old_space_to_allocate);
		free(temporary);
	}
	memory[memory_nodes] = payload;
	return (memory);
}
