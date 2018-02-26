/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_operations_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 12:36:11 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 12:36:15 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	file_qnt(DIR *dir_fd, t_flagls *flag, size_t *i)
{
	struct dirent	*obj;

	while ((obj = readdir(dir_fd)) != NULL)
	{
		if (flag->flag[0] == 1)
		{
			if (flag->flag[0] == 1 && flag->flag[9] == 0)
				*i += 1;
			else if (flag->flag[0] == 1 && flag->flag[9] == 1)
				if (ft_strcmp(obj->d_name, ".") != 0
					&& ft_strcmp(obj->d_name, "..") != 0)
					*i += 1;
		}
		else
		{
			if (obj->d_name[0] != '.')
				*i += 1;
		}
	}
}

int			dir_reader(char *dir, int *flag_e, t_flagls *flag, size_t *i)
{
	DIR				*dir_fd;

	if ((dir_fd = opendir(dir)) == NULL)
	{
		if (flag->show_path == 0 && is_dir(dir))
			ft_printf("%s:\n", dir);
		permission_check(dir, flag);
		*flag_e = 1;
		return (-1);
	}
	file_qnt(dir_fd, flag, i);
	closedir(dir_fd);
	if (*i == 0 && flag->show_path == 0 && flag->argc == 2)
		*flag_e = 1;
	return (0);
}

int			r(t_flagls *flag, char **res, size_t *i_j, struct dirent *obj)
{
	if (flag->flag[0] == 1 && flag->flag[9] == 0)
	{
		if (!(res[i_j[0]] = ft_strdup(obj->d_name)))
			return (-1);
	}
	else if (flag->flag[0] == 1 && flag->flag[9] == 1)
		if (ft_strcmp(obj->d_name, ".") != 0
			&& ft_strcmp(obj->d_name, "..") != 0)
			if (!(res[i_j[1]++] = ft_strdup(obj->d_name)))
				return (-1);
	return (0);
}

int			read_bls(DIR *dir_fd, t_flagls *flag, char **res, size_t *i_j)
{
	struct dirent	*obj;

	while ((obj = readdir(dir_fd)) != NULL)
	{
		if (flag->flag[0] == 1)
		{
			if (r(flag, res, i_j, obj) == -1)
				return (-1);
		}
		else
		{
			if (obj->d_name[0] != '.')
				if (!(res[i_j[1]++] = ft_strdup(obj->d_name)))
					return (-1);
		}
		i_j[0]++;
	}
	return (0);
}

char		**make_arr(char *dir, t_flagls *flag, int *flag_e, size_t *i)
{
	char	**res;
	int		j;

	j = 0;
	if (dir_reader(dir, flag_e, flag, i) == -1)
		return (NULL);
	if (*i == 0 || !(res = (char **)malloc(sizeof(char *) * (*i + 1))))
	{
		while (dir[j] != '\0')
			j++;
		if (flag->flag[6] == 1 && (dir[0] == '-' && (ft_isalpha(dir[j - 1]))))
			*flag_e = 1;
		if (flag->argc - flag->flag_cnt == 2 && ((dir[0] == '-'
			&& dir[1] == '\0') || (dir[0] == '-' && dir[1] != '\0')))
			*flag_e = 1;
		return (NULL);
	}
	res[*i] = 0;
	*i = 0;
	return (res);
}
