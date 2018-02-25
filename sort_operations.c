/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:30:41 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/06 15:30:45 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



int is_dir(const char *path)
{
	struct stat statbuf;

	if (lstat(path, &statbuf) == 0)
		if (S_ISLNK(statbuf.st_mode))
			return (0);
	if (stat(path, &statbuf) == -1)
		return -1;
	return S_ISDIR(statbuf.st_mode);
}

int doesnt_exist(char **args, t_flagls *flags)
{
	int i;
	int		dir_res;
	char 	*buff;
	struct stat obj;

	i = 0;
	if (args == NULL)
		return (-1);
	while (args[i] != NULL)
	{
		dir_res = is_dir(args[i]);
		if (dir_res == -1)
		{
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			free(args[i]);
			args[i] = ft_strnew(0);
		}
		else if (dir_res == 0 && flags->flag[3] == 0 )
		{
			if (!(buff = ft_strnew(1000)))
				return (-1);
			if (readlink(args[i], buff, 1000) != -1 )
			{
				if (lstat(buff, &obj) == -1)
				{
					free(buff);
					i++;
					continue ;
				}
				if (is_dir(buff))
				{
					free(args[i]);
					if (!(args[i] = ft_strdup(buff)))
						return (-1);
				}
			}

		}
		i++;
	}
	return (0);
}

void swap_strs(char **arg1, char **arg2)
{
	char *tmp;

	tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}

int dir_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

void time_sort(char **arr, int n, char *dir)
{
	char *file;
	unsigned int i;
	unsigned int j;
	struct stat obj;
	struct stat obj2;

	i = 0;
	if (n > 1)
	{
		while ((int)i < n - 1)
		{
			j = i + 1;
			while ((int)j < n)
			{
				lstat((file = get_next_dir(&dir, arr[i])), &obj);
				free(file);
				lstat((file = get_next_dir(&dir, arr[j])), &obj2);
				free(file);
				if (obj.st_mtimespec.tv_sec - obj2.st_mtimespec.tv_sec < 0)
					swap_strs(&(arr[i]), &(arr[j]));
				else if (obj.st_mtimespec.tv_sec == obj2.st_mtimespec.tv_sec)
					if (obj.st_mtimespec.tv_nsec - obj2.st_mtimespec.tv_nsec < 0)
						swap_strs(&(arr[i]), &(arr[j]));
				j++;
			}
			i++;
		}
	}
}

void sort_strs(char **arr, t_flagls * flagls, int n, char *dir)
{
	int i = 0;
	int j = 0;

	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i],arr[j]) > 0)
				swap_strs(&(arr[i]), &(arr[j]));
			j++;
		}
		i++;
	}
	if (flagls->flag[4] == 1)
		time_sort(arr, dir_len(arr), dir);
}