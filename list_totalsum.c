/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_totalsum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:39:37 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 16:39:39 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_uid_grp(t_margin *margin, struct stat obj)
{
	struct passwd	*usr_data;
	struct group	*grp;
	size_t			len;

	if ((usr_data = getpwuid(obj.st_uid)) == NULL)
		return (-1);
	len = ft_strlen(usr_data->pw_name);
	if (len > (size_t)margin->uid)
		margin->uid = (int)len;
	len = (size_t)ls_digit_len((int)obj.st_nlink);
	if (len > (size_t)margin->block)
		margin->block = (int)len;
	grp = getgrgid(obj.st_gid);
	len = (size_t)ft_strlen(grp->gr_name);
	if (len > (size_t)margin->group)
		margin->group = (int)len;
	len = (size_t)ls_digit_len((int)obj.st_size);
	if (len > (size_t)margin->size)
		margin->size = (int)len;
	return (0);
}

unsigned int	total_sum_ls(char **str, t_margin *margin, char *dir_path)
{
	unsigned		i;
	unsigned		total;
	struct stat		obj;
	char			*tmp;

	i = 0;
	total = 0;
	if (str != NULL)
		while (str[i] != 0)
		{
			tmp = get_next_dir(&dir_path, str[i++]);
			lstat(tmp, &obj);
			if (get_uid_grp(margin, obj) == -1)
				return (0);
			total += obj.st_blocks;
			free(tmp);
		}
	else
	{
		lstat(dir_path, &obj);
		if (get_uid_grp(margin, obj) == -1)
			return (0);
		total = (unsigned)-1;
	}
	return (total);
}
