/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_throw_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:53:08 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/08 19:22:09 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_throw_error(char	*error_message)
{
	ft_putstr_fd(SHELL_R, STDERR_FILENO);
	perror(error_message);
	ft_putstr_fd(SHELL_RC, STDERR_FILENO);
	exit(1);
}
