/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:54:33 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/01 20:01:38 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_notify(char	*success_message)
{
	ft_printf(SHELL_G);
	ft_printf("%s\n", success_message);
	ft_printf(SHELL_RC);
}
