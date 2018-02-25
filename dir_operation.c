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

int permission_check(char *dir, t_flagls *flag)
{
	char *tmp;
	char *tmp2;

	if (flag->show_path > 0)
		ft_printf("\n");
	if (flag->show_path > 0)
		ft_printf("%s:\n", dir);
	if (flag->flag[1] == 1)
	{
		if (!(tmp = ft_strrchr(dir, '/')))
			return (0);
		if(!(tmp2 = ft_strsub(tmp, 1, ft_strlen(tmp))))
		{
			free(tmp);
			return (0);
		}
	}
	else
		tmp2 = ft_strdup(dir);
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(tmp2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

static char **make_array(char *dir, t_flagls *flag, int *flag_e, size_t *i)
{
	char			**res;
	struct dirent	*obj;
	DIR				*dir_fd;

	if ((dir_fd = opendir(dir)) == NULL)
	{
		permission_check(dir, flag);
		*flag_e = 1;
		return (NULL);
	}
	while((obj = readdir(dir_fd)) != NULL)
	{
		if (flag->flag[0] == 1)
			*i += 1;
		else
			if (obj->d_name[0] != '.')
				*i += 1;
	}
	closedir(dir_fd);
	if (*i == 0 || !(res = (char **)malloc(sizeof(char *) * (*i + 1))))
	{
		int j = 0;
		while (dir[j] != '\0')
			j++;
		if (flag->flag[6] == 1 && (dir[0] == '-' && (ft_isalpha(dir[j - 1]) )))
			*flag_e = 1;
		if (flag->argc - flag->flag_cnt == 2 && ((dir[0] == '-' && dir[1] == '\0') || (dir[0] == '-' && dir[1] != '\0')))
			*flag_e = 1;
		return (NULL);
	}
	res[*i] = 0;
	*i = 0;
	return (res);
}

char **get_cur_dir(t_flagls *flag, char *dir, int *flag_e)
{
	char			**res;
	struct dirent	*obj;
	DIR				*dir_fd;
	size_t			i;
	size_t			j;

	i = 0;
	if (!(res = make_array(dir, flag, flag_e, &i)))
		return (NULL);
	if ((dir_fd = opendir(dir)) == NULL)
		return (NULL);
	j = 0;
	while ((obj = readdir(dir_fd)) != NULL)
	{
		if (flag->flag[0] == 1)
			res[i] = ft_strdup(obj->d_name);
		else
			if (obj->d_name[0] != '.')
				res[j++] = ft_strdup(obj->d_name);
		i++;
	}
	closedir(dir_fd);
	sort_strs(res, flag, dir_len(res), dir);
	return (res);
}

char *get_next_dir(char **cur_dir, char *next_dir)
{
	char *tmp;
	char *tmp2;

	if (ft_strcmp(*cur_dir, "/") != 0)
	{
		if (!(tmp = ft_strjoin(*cur_dir, "/")))
			return (NULL);
	}
	else
		if (!(tmp = ft_strdup(*cur_dir)))
			return (NULL);
	if (!(tmp2 = ft_strjoin(tmp, next_dir)))
		return (NULL);
	free(tmp);
	return (tmp2);
}



static int		procces_block(char *dir_path, char ***dir, t_flagls *flag)
{
	int flag_e;

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
		if (flag_e == 0 && flag->show_path > 0)
			ft_printf("\n");
		if (flag_e == 0 && flag->expt == 0)
			ft_printf("%s:\n", dir_path);
		flag->show_path++;
		return (-1);
	}
	if (flag->show_path > 0)
		ft_printf("\n");
	if ((flag->flag[1] == 1 && flag->show_path > 0) || ((flag->argc - (flag->flag_cnt + 1) > 1) && is_dir(dir_path) == 1 /*&& flag->show_path > 0*/))
		ft_printf("%s:\n", dir_path);
	list_or_not(flag,*dir, dir_path);
	return (0);
}

int		read_dir(char *dir_path, t_flagls *flag) {
	char **dir;
	char *tmp;
	size_t i;

	i = 0;
	dir = NULL;
	if (dir_path == NULL)
		return (0);
	if (procces_block(dir_path, &dir, flag) == -1)
		return (0);
	flag->show_path++;
	if (flag->flag[1] == 1)
	{
		if (flag->flag[2] == 1)
		{
			while (dir[i] != 0)
				i++;
			while (i > 0)
			{
				i--;
				if (is_dir(get_next_dir(&dir_path, dir[i])) == 1 && ft_strcmp(dir[i], ".") != 0
					&& ft_strcmp(dir[i], "..") != 0) {
					if (!(tmp = ft_strdup(dir_path)))
						return (0);
					read_dir(get_next_dir(&tmp, dir[i]), flag);
				}
			}
		}
		else
		{
			while (dir[i] != NULL)
			{
				if (is_dir(get_next_dir(&dir_path, dir[i])) == 1 && ft_strcmp(dir[i], ".") != 0
					&& ft_strcmp(dir[i], "..") != 0) {
					if (!(tmp = ft_strdup(dir_path)))
						return (0);
					read_dir(get_next_dir(&tmp, dir[i]), flag);
				}
				i++;
			}
		}
	}
	ft_free_str_arr(&dir);

	return (0);
}


