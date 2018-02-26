/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mai.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:28:04 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/05 17:44:28 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <fcntl.h>

void			bonus(char *str, size_t i, t_flagls *flag)
{
	if (str[i] == 'f')
		flag->flag[0] = 1;
	if (str[i] == 'A')
	{
		if (flag->flag[0] == 1)
			flag->flag[9] = 0;
		else
			flag->flag[0] = 1;
	}
	if (str[i] == 'a' && flag->flag[9] == 1)
		flag->flag[9] = 0;
	if (str[i] == '1' && flag->flag[3] == 1)
		flag->flag[3] = 0;
	else if (str[i] == 'l' && flag->flag[5] == 1)
		flag->flag[5] = 0;
}

static int		dir_reader_ls(char **args, t_flagls flag)
{
	size_t i;

	i = 0;
	if (args == NULL)
	{
		if (read_dir(".", &flag) == -1)
			return (-1);
	}
	else
	{
		if (flag.flag[2] == 1)
		{
			while (args[i] != NULL)
				i++;
			while (i > 0)
				if (read_dir(args[--i], &flag) == -1)
					return (-1);
		}
		else
			while (args[i] != NULL)
				if (read_dir(args[i++], &flag) == -1)
					return (-1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	size_t		i;
	t_flagls	flag;
	char		**args;
	char		**tmp;

	i = 0;
	args = NULL;
	if (val_flags(argc, argv, &flag, &i) > 0)
		return (1);
	if (argc - i > 0)
	{
		if (!(tmp = sort_args(argv, argc, &flag)))
			return (0);
		if ((args = sort_args_type(tmp, &flag)) == NULL)
		{
			ft_free_str_arr(tmp);
			return (0);
		}
		ft_free_str_arr(tmp);
	}
	if (dir_reader_ls(args, flag) == -1)
		return (1);
	ft_free_str_arr(args);
	return (0);
}
