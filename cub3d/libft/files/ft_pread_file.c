/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pread_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaio <kaio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:03:57 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/01 20:28:27 by kaio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pread_file(char *filename)
{
	char	*file;

	file = ft_read_file(filename);
	if (!file)
		ft_throw_error("Empty file or unable to read the file");
	ft_new_memory(file);
	return (file);
}
