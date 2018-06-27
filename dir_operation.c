/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:31:23 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/06 10:31:24 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**get_cur_dir(t_flagls *flag, char *dir, int *flag_e)
{
	char			**res;
	DIR				*dir_fd;
	size_t			i_j[2];

	i_j[0] = 0;
	if (!(res = make_arr(dir, flag, flag_e, &i_j[0])))
		return (NULL);
	if ((dir_fd = opendir(dir)) == NULL)
		return (NULL);
	i_j[1] = 0;
	if (read_bls(dir_fd, flag, res, i_j) == -1)
		return (NULL);
	closedir(dir_fd);
	sort_strs(res, flag, dir_len(res), dir);
	return (res);
}

static int		procces_block(char *dir_path, char ***dir, t_flagls *flag)
{
	int				flag_e;

	flag_e = 0;
	if (dir_path == NULL)
		return (-1);
	if (is_dir(dir_path) == 0)
	{
		if (is_dir(dir_path) && flag->show_path > 0)
			write(1, "\n", 1);
		list_or_not(flag, *dir, dir_path);
		flag->show_path++;
		return (-1);
	}
	if ((*dir = get_cur_dir(flag, dir_path, &flag_e)) == NULL)
	{
		error_path(flag_e, flag, dir_path);
		return (-1);
	}
	if (flag->show_path > 0)
		ft_printf("\n");
	if ((flag->flag[1] == 1 && flag->show_path > 0)
		|| ((flag->argc - (flag->flag_cnt + 1) > 1) && is_dir(dir_path) == 1))
		ft_printf("%s:\n", dir_path);
	list_or_not(flag, *dir, dir_path);
	return (0);
}

static int		recursive_cycle(char *dir_path, t_flagls *flag, char **dir)
{
	char	*tmp;
	size_t	i;
	char	*path;
	char	*check_path;

	i = 0;
	while (dir[i] != NULL)
	{
		check_path = get_next_dir(&dir_path, dir[i]);
		if (is_dir(check_path) == 1
			&& ft_strcmp(dir[i], ".") != 0
			&& ft_strcmp(dir[i], "..") != 0)
		{
			if (!(tmp = ft_strdup(dir_path)))
				return (0);
			path = get_next_dir(&tmp, dir[i]);
			read_dir(path, flag);
			free(path);
			free(tmp);
		}
		free(check_path);
		i++;
	}
	return (0);
}

int				read_dir(char *dir_path, t_flagls *flag)
{
	char		**dir;

	dir = NULL;
	if (dir_path == NULL)
		return (0);
	if (dir_path[0] == '\0')
		return (0);
	if (procces_block(dir_path, &dir, flag) == -1)
		return (0);
	flag->show_path++;
	if (flag->flag[1] == 1)
	{
		if (flag->flag[2] == 1)
			rev_arr(dir);
		recursive_cycle(dir_path, flag, dir);
	}
	ft_free_str_arr(dir);
	return (0);
}
