/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:02:44 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/06 20:24:53 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file_fd(int fd)
{
	char	*file;
	char	*temp;
	char	buffer[25];
	int		bytes;
	int		buffer_size;

	buffer_size = 25;
	file = NULL;
	bytes = read(fd, buffer, buffer_size - 2);
	if (!bytes)
		return (NULL);
	buffer[bytes] = '\0';
	file = ft_strljoin(file, buffer, bytes);
	while (bytes == buffer_size - 2)
	{
		bytes = read(fd, buffer, buffer_size - 2);
		if (!bytes)
			break ;
		buffer[bytes] = '\0';
		temp = file;
		file = ft_strljoin(file, buffer, ft_strlen(file) + bytes);
		free(temp);
	}
	return (file);
}
