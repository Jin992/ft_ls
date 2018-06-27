/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_write_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:35:15 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/25 16:35:18 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "ft_ls.h"

static void		major_minor_device(struct stat k)
{
	ft_printf("%*d,%*d ", 4, 4, k.st_rdev >> 24 & 0xff, k.st_rdev & 0xffffff);
}

static void		time_block(struct stat obj)
{
	char *time1;

	time1 = ctime(&(obj.st_mtimespec.tv_sec));
	if (time(NULL) - obj.st_mtimespec.tv_sec > 15768000)
	{
		time1[10] = '\0';
		ft_printf(" %s", time1 + 4);
		time1[24] = '\0';
		ft_printf("  %s", time1 + 20);
	}
	else if (time(NULL) - obj.st_mtimespec.tv_sec < 0)
	{
		time1[10] = '\0';
		ft_printf(" %s", time1 + 4);
		time1[29] = '\0';
		ft_printf(" %s", time1 + 23);
	}
	else
	{
		time1[16] = '\0';
		ft_printf(" %s", time1 + 4);
	}
}

static void		write_symlink(struct stat obj, char *tmp2)
{
	char *buff;

	buff = NULL;
	if (S_ISLNK(obj.st_mode))
	{
		buff = (char *)malloc(sizeof(char) * 128);
		bzero(buff, 128);
		readlink(tmp2, buff, 128);
		ft_putstr(" -> ");
		ft_putstr(buff);
	}
	if (buff != NULL)
		free(buff);
}

static void		w_list(struct stat obj, t_margin margin, char *dir, char *path)
{
	char			*tmp;
	struct passwd	*usr;
	struct group	*grp;

	tmp = get_permissions(obj, margin);
	ft_printf("%s", tmp);
	ft_printf("%*d", margin.block, obj.st_nlink);
	usr = getpwuid(obj.st_uid);
	ft_printf(" %-*s", margin.uid, usr->pw_name);
	grp = getgrgid(obj.st_gid);
	ft_printf("  %-*s", margin.group, grp->gr_name);
	if (S_ISBLK(obj.st_mode) || S_ISCHR(obj.st_mode))
		major_minor_device(obj);
	if (!(S_ISBLK(obj.st_mode) || S_ISCHR(obj.st_mode)))
		ft_printf("  %*zu", margin.size, obj.st_size);
	time_block(obj);
	ft_printf(" %-s", dir);
	write_symlink(obj, path);
	ft_printf("\n");
	get_acl(margin, path);
	free(tmp);
}

void			print_list(char *dir, t_margin margin, char *dir_path)
{
	struct stat	obj;
	char		*tmp2;

	if (dir_path != NULL)
		tmp2 = get_next_dir(&dir_path, dir);
	else
		tmp2 = ft_strdup(dir);
	if (lstat(tmp2, &obj) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		return ;
	}
	else
	{
		margin.acl = listxattr(tmp2, margin.acl_buff,\
		sizeof(margin.acl_buff), XATTR_NOFOLLOW);
		w_list(obj, margin, dir, tmp2);
	}
	if (tmp2 != NULL)
		free(tmp2);
}
