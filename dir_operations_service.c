/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_operations_service.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:06:02 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/26 14:06:04 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_dir(const char *path)
{
	struct stat statbuf;

	if (lstat(path, &statbuf) == 0)
		if (S_ISLNK(statbuf.st_mode))
			return (0);
	if (stat(path, &statbuf) == -1)
		return (-1);
	return (S_ISDIR(statbuf.st_mode));
}

int			dir_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

void		perm_error(char *tmp2)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(tmp2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
