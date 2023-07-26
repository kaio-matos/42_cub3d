/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:30:47 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/01/24 19:51:25 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_printf(const char *str, ...)
{
	char	*result;
	int		printed;
	t_slot	finded;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, STDOUT_FILENO);
	free(result);
	va_end(args);
	return (printed);
}

int	ft_vprintf(const char *str, va_list args)
{
	char	*result;
	int		printed;
	t_slot	finded;

	if (!str)
		return (-1);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, STDOUT_FILENO);
	free(result);
	return (printed);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	char	*result;
	int		printed;
	t_slot	finded;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, fd);
	free(result);
	va_end(args);
	return (printed);
}

int	ft_vfprintf(int fd, const char *str, va_list args)
{
	char	*result;
	int		printed;
	t_slot	finded;

	if (!str)
		return (-1);
	result = ft_strdup(str);
	finded = get_slot(result, 0);
	printed = deal_args(finded, args, 0, fd);
	free(result);
	return (printed);
}
