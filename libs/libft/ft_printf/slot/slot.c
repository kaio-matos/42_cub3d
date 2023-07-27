/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:33:41 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/09/20 01:32:38 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_slot_length(char *string)
{
	int	length;

	length = ft_strdigit(string);
	if (ft_isconversion(string[length]))
		return (length + 2);
	return (0);
}

t_slot	reset_slot(t_slot *item)
{
	item->string = NULL;
	item->conversion = '\0';
	item->p_initial = -1;
	item->p_end = -1;
	item->length = -1;
	return (*item);
}

t_slot	get_slot(char *string, int starts)
{
	t_slot	item;

	reset_slot(&item);
	item.string = string;
	item.p_initial = ft_strchri(string + starts, '%');
	if (item.p_initial == -1)
	{
		item.p_initial = ft_strlen(item.string);
		return (item);
	}
	item.p_initial += starts;
	item.length = get_slot_length(string + item.p_initial + 1);
	if (item.length <= 1)
		return (get_slot(string, item.p_initial + 1));
	item.p_end = (item.p_initial + item.length) - 1;
	item.conversion = item.string[item.p_end];
	return (item);
}
