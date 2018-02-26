/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 12:24:15 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 12:24:18 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_digit_len(int digit)
{
	unsigned i;

	i = 1;
	while (digit / 10 != 0)
	{
		digit = digit / 10;
		i++;
	}
	return (i);
}

void	rev_arr(char **arr)
{
	int		i;
	char	*tmp;
	int		len;
	int		swaps;

	i = 0;
	len = 0;
	while (arr[len] != '\0')
		len++;
	swaps = len / 2;
	while (swaps > 0)
	{
		len--;
		tmp = arr[i];
		arr[i] = arr[len];
		arr[len] = tmp;
		i++;
		swaps--;
	}
}

void	error_path(int flag_e, t_flagls *flag, char *dir_path)
{
	if (flag_e == 0 && flag->show_path > 0)
		ft_printf("\n");
	if (flag_e == 0 && flag->expt == 0)
		ft_printf("%s:\n", dir_path);
	flag->show_path++;
}

char	*get_next_dir(char **cur_dir, char *next_dir)
{
	char *tmp;
	char *tmp2;

	if (ft_strcmp(*cur_dir, "/") != 0)
	{
		if (!(tmp = ft_strjoin(*cur_dir, "/")))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strdup(*cur_dir)))
			return (NULL);
	}
	if (!(tmp2 = ft_strjoin(tmp, next_dir)))
		return (NULL);
	free(tmp);
	return (tmp2);
}

int		permission_check(char *dir, t_flagls *flag)
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
		if (!(tmp2 = ft_strsub(tmp, 1, ft_strlen(tmp))))
		{
			free(tmp);
			return (0);
		}
	}
	else
		tmp2 = ft_strdup(dir);
	perm_error(tmp2);
	free(tmp2);
	return (0);
}
