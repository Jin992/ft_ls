/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 18:16:34 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/23 18:16:39 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int 	last_flag_position(char **argv, int argc)
{
	int		i;

	i = 1;
	if (argc < 2)
		return (0);
	while ( argv[i][0] == '-'  )
	{
		if (argv[i][0] == '-' && argv[i][1] == '\0')
			break ;
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		{
			i++;
			break;
		}
		if (argv[i + 1] == NULL)
			break;
		i++;
	}
	return (i);
}

static void time_sort_arg(char **arr, int n)
{
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
				lstat(arr[i], &obj);
				lstat(arr[j], &obj2);
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

static void	sort_arguments(char **tmp)
{
	int		i;
	int		j;
	char 	*tmp_str;

	i = 0;
	j = 0;
	while (tmp[i] != NULL)
	{
		if (tmp[i + 1] != 0)
			if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
			{
				tmp_str = tmp[i + 1];
				tmp[i + 1] = tmp[i];
				tmp[i] = tmp_str;
				j = 1;
			}
		i++;
		if (j == 1)
		{
			i = 0;
			j = 0;
		}
	}
}

char	**sort_args(char **argv, int argc)
{
	int		i;
	int		j;
	char	**tmp;
	int 	objects;

	j = 0;
	i = last_flag_position(argv, argc);
	tmp = NULL;
	if ((objects = (argc ) - (i)) > 0)
	{
		if(!(tmp = (char **)malloc(sizeof(char *) * (objects + 1))))
			return (NULL);
		tmp[objects] = 0;
		while (argv[i] != NULL)
			if (!(tmp[j++] = ft_strdup(argv[i++])))
				return (NULL);
	}
	sort_arguments(tmp);
	return (tmp);
}

int		clean_array(int i, int j, char **args, char **tmp)
{
	char *tmp_s;

	if (args[i][0] == '\0')
		return (-1);
	while (args[i] != NULL)
	{
		if (args[i][0] != '\0')
			if (!(tmp[j++] = ft_strdup(args[i])))
				return (-1);
		i++;
	}
	i = 0;
	while (tmp[i] != NULL)
	{
		if (i > 0)
		{
			if (!is_dir(tmp[i]) && is_dir(tmp[i-1]))
			{
				tmp_s = tmp[i];
				tmp[i] = tmp[i - 1];
				tmp[i - 1] = tmp_s;
				i = 0;
			}
		}
		i++;
	}
	return (0);
}

char **sort_args_type(char **args, t_flagls *flag)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	if (doesnt_exist(args, flag) == -1)
		return (NULL);
	while (args[i] != NULL)
		i++;
	if (flag->flag[4] == 1)
		time_sort_arg(args, i);
	while (args[i] != NULL)
	{
		if (args[i][0] == '\0')
			j++;
		i++;
	}
	if (!(tmp = ft_new_str_arr(tmp, ((size_t)i - j))))
		return (NULL);
	if (clean_array(0, 0, args, tmp) == -1)
	{
		//ft_free_str_arr(&tmp);
		return (NULL);
	}
	i = 0;

	return (tmp);
}