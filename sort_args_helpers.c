/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:43:51 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 16:43:52 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		folder_file_sort(char **tmp, t_flagls *flag)
{
	int		i;
	char	*tmp_s;

	i = 0;
	if (flag->flag[8] == 1)
		return ;
	while (tmp[i] != NULL)
	{
		if (i > 0)
		{
			if (!is_dir(tmp[i]) && is_dir(tmp[i - 1]))
			{
				tmp_s = tmp[i];
				tmp[i] = tmp[i - 1];
				tmp[i - 1] = tmp_s;
				i = 0;
			}
		}
		i++;
	}
}

int				clean_array(int i, t_flagls *flag, char **args, char **tmp)
{
	int j;

	j = 0;
	if (args[i][0] == '\0')
		return (-1);
	while (args[i] != NULL)
	{
		if (args[i][0] != '\0')
			if (!(tmp[j++] = ft_strdup(args[i])))
				return (-1);
		i++;
	}
	folder_file_sort(tmp, flag);
	return (0);
}
