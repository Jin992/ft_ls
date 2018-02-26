/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get_perm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:37:37 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 16:37:39 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			user_perm(mode_t perm, char *mode_string)
{
	mode_string[1] = (perm & S_IRUSR) ? 'r' : '-';
	mode_string[2] = (perm & S_IWUSR) ? 'w' : '-';
	if (perm & S_ISUID && perm & S_IXUSR)
		mode_string[3] = 's';
	else if (perm & S_ISUID && !(perm & S_IXUSR))
		mode_string[3] = 'S';
	else
		mode_string[3] = (perm & S_IXUSR) ? 'x' : '-';
}

static void			group_perm(mode_t perm, char *mode_string)
{
	mode_string[4] = (perm & S_IRGRP) ? 'r' : '-';
	mode_string[5] = (perm & S_IWGRP) ? 'w' : '-';
	if (perm & S_ISGID && perm & S_IXGRP)
		mode_string[6] = 's';
	else if (perm & S_ISGID && !(perm & S_IXGRP))
		mode_string[6] = 'S';
	else
		mode_string[6] = (perm & S_IXGRP) ? 'x' : '-';
}

static void			other_perm(mode_t perm, char *mode_string)
{
	mode_string[7] = (perm & S_IROTH) ? 'r' : '-';
	mode_string[8] = (perm & S_IWOTH) ? 'w' : '-';
	if (perm & S_ISVTX && perm & S_IXOTH)
		mode_string[9] = 't';
	else if (perm & S_ISVTX && !(perm & S_IXOTH))
		mode_string[9] = 'T';
	else
		mode_string[9] = (perm & S_IXOTH) ? 'x' : '-';
}

static void			acl_check(t_margin margin, char *mode_string)
{
	if (margin.acl > 0)
	{
		mode_string[10] = '@';
		mode_string[11] = ' ';
	}
	else
	{
		mode_string[10] = ' ';
		mode_string[11] = ' ';
	}
}

char				*get_permissions(struct stat obj, t_margin margin)
{
	char	*mode_string;
	mode_t	perm;

	mode_string = ft_strnew(12);
	perm = obj.st_mode;
	if (S_ISDIR(perm))
		mode_string[0] = 'd';
	else if (S_ISLNK(perm))
		mode_string[0] = 'l';
	else if (S_ISBLK(perm))
		mode_string[0] = 'b';
	else if (S_ISCHR(perm))
		mode_string[0] = 'c';
	else if (S_ISFIFO(perm))
		mode_string[0] = 'f';
	else if (S_ISREG(perm))
		mode_string[0] = '-';
	else if (S_ISSOCK(perm))
		mode_string[0] = 's';
	user_perm(perm, mode_string);
	group_perm(perm, mode_string);
	other_perm(perm, mode_string);
	acl_check(margin, mode_string);
	return (mode_string);
}
