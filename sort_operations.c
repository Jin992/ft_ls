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

void	swap_strs(char **arg1, char **arg2)
{
	char *tmp;

	tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}

void	time_sort(char **arr, int n, char *dir)
{
	char			*file;
	int				i;
	int				j;
	struct stat		obj;
	struct stat		obj2;

	i = 0;
	while (i != n - 1)
	{
		j = 0;
		while (j != n - i - 1)
		{
			lstat((file = get_next_dir(&dir, arr[j])), &obj);
			free(file);
			lstat((file = get_next_dir(&dir, arr[j + 1])), &obj2);
			free(file);
			if (obj.st_mtimespec.tv_sec < obj2.st_mtimespec.tv_sec)
				swap_strs(&(arr[j]), &(arr[j + 1]));
			j++;
		}
		i++;
	}
}

void	sort_strs(char **arr, t_flagls *flagls, int n, char *dir)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (flagls->flag[8] == 1)
		return ;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
				swap_strs(&(arr[i]), &(arr[j]));
			j++;
		}
		i++;
	}
	if (flagls->flag[4] == 1)
		time_sort(arr, dir_len(arr), dir);
}
