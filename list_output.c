/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:25:58 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/06 16:25:59 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	rev_print(char **dir, t_flagls *flag, t_margin mrg, char *dir_path)
{
	size_t i;

	i = 0;
	if (dir != NULL)
	{
		while (dir[i] != 0)
			i++;
		while (i > 0)
		{
			i--;
			if (flag->flag[3] == 1)
				print_list(dir[i], mrg, dir_path);
			else
				ft_printf("%s\n", dir[i]);
		}
	}
	else
	{
		if (flag->flag[3] == 1)
			print_list(dir_path, mrg, NULL);
		else
			ft_printf("%s\n", dir_path);
	}
}

static void	ord_print(char **dir, t_flagls *flag, t_margin mrg, char *dir_path)
{
	size_t i;

	i = 0;
	if (dir != NULL)
		while (dir[i] != 0)
		{
			if (flag->flag[3] == 1)
				print_list(dir[i], mrg, dir_path);
			else
				ft_printf("%s\n", dir[i]);
			i++;
		}
	else
	{
		if (flag->flag[3] == 1)
			print_list(dir_path, mrg, NULL);
		else
			ft_printf("%s\n", dir_path);
	}
}

void		list_or_not(t_flagls *flags, char **dir, char *dir_path)
{
	unsigned total;
	t_margin margin;

	margin.size = 0;
	margin.block = 0;
	margin.uid = 0;
	margin.group = 0;
	margin.acl = 0;
	margin.ext_atr = flags->flag[7];
	total = total_sum_ls(dir, &margin, dir_path);
	if (flags->flag[3] == 1 && (int)total >= 0)
		ft_printf("total %u\n", total);
	if (flags->flag[2] == 1)
		rev_print(dir, flags, margin, dir_path);
	else
		ord_print(dir, flags, margin, dir_path);
}
