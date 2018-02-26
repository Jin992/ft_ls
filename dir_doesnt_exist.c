/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_doesnt_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:47:47 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 16:47:49 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		write_perm(char **args, int i)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(args[i], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free(args[i]);
	args[i] = ft_strnew(0);
}

static int		check_link(char **args, int *i)
{
	char		*buff;
	struct stat	obj;

	if (!(buff = ft_strnew(1000)))
		return (-1);
	if (readlink(args[*i], buff, 1000) != -1)
	{
		if (lstat(buff, &obj) == -1)
		{
			free(buff);
			(*i)++;
			return (1);
		}
		if (is_dir(buff))
		{
			free(args[*i]);
			if (!(args[*i] = ft_strdup(buff)))
				return (-1);
		}
	}
	return (0);
}

int				doesnt_exist(char **args, t_flagls *flags)
{
	int	i;
	int	dir_res;
	int	res;

	i = 0;
	if (args == NULL)
		return (-1);
	while (args[i] != NULL)
	{
		dir_res = is_dir(args[i]);
		if (dir_res == -1)
			write_perm(args, i);
		else if (dir_res == 0 && flags->flag[3] == 0)
		{
			if ((res = check_link(args, &i)) == 1)
				continue;
			else if (res == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
