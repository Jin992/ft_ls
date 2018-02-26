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
	unsigned int	i;
	unsigned int	j;
	struct stat		obj;
	struct stat		obj2;

	i = 0;
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
