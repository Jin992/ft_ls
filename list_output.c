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

int ls_digit_len(int digit)
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

unsigned int	total_sum_ls(char **str, t_margin *margin, char *dir_path)
{
	unsigned i;
	unsigned total;
	struct stat obj;
	struct passwd *usr_data;
	size_t len;
	struct group *grp;

	i = 0;
	total = 0;
	char *tmp;
	if (str != NULL) {
		while (str[i] != 0) {
			tmp = get_next_dir(&dir_path, str[i]);
			lstat(tmp, &obj);
			if ((usr_data = getpwuid(obj.st_uid)) == NULL)
				return (0);
			len = ft_strlen(usr_data->pw_name);
			if (len > (size_t) margin->uid)
				margin->uid = (int) len;
			len = (size_t) ls_digit_len((int) obj.st_nlink);
			if (len > (size_t) margin->block)
				margin->block = (int) len;
			grp = getgrgid(obj.st_gid);
			len = (size_t) ft_strlen(grp->gr_name);
			if (len > (size_t) margin->group)
				margin->group = (int) len;
			len = (size_t) ls_digit_len((int) obj.st_size);
			if (len > (size_t) margin->size)
				margin->size = (int) len;
			total += obj.st_blocks;
			i++;
		}
	}
	else
	{
		//tmp = get_next_dir(&dir_path, str[i]);
		lstat(dir_path, &obj);
		if ((usr_data = getpwuid(obj.st_uid)) == NULL)
			return (0);
		len = ft_strlen(usr_data->pw_name);
		if (len > (size_t) margin->uid)
			margin->uid = (int) len;
		len = (size_t) ls_digit_len((int) obj.st_nlink);
		if (len > (size_t) margin->block)
			margin->block = (int) len;
		grp = getgrgid(obj.st_gid);
		len = (size_t) ft_strlen(grp->gr_name);
		if (len > (size_t) margin->group)
			margin->group = (int) len;
		len = (size_t) ls_digit_len((int) obj.st_size);
		if (len > (size_t) margin->size)
			margin->size = (int) len;
		total = (unsigned )-1;
	}
	return (total);
}
void      major_minor_device(struct stat k)
{
	ft_printf("%*d,%*d ", 4, 4, k.st_rdev >> 24 & 0xff, k.st_rdev & 0xffffff);
}

char *get_permissions(struct stat obj)
{

	char *mode_string;
	mode_t perm;

	mode_string = ft_strnew(10);

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
		mode_string[1] = (perm & S_IRUSR) ? 'r' : '-';
		mode_string[2] = (perm & S_IWUSR) ? 'w' : '-';
		if (perm & S_ISUID && perm & S_IXUSR)
			mode_string[3] = 's';
		else if (perm & S_ISUID && !(perm & S_IXUSR))
			mode_string[3] = 'S';
		else
			mode_string[3] = (perm & S_IXUSR) ? 'x' : '-';
		mode_string[4] = (perm & S_IRGRP) ? 'r' : '-';
		mode_string[5] = (perm & S_IWGRP) ? 'w' : '-';
		if (perm & S_ISGID && perm & S_IXGRP)
			mode_string[6] = 's';
		else if (perm & S_ISGID && !(perm & S_IXGRP))
			mode_string[6] = 'S';
		else
			mode_string[6] = (perm & S_IXGRP) ? 'x' : '-';
		mode_string[7] = (perm & S_IROTH) ? 'r' : '-';
		mode_string[8] = (perm & S_IWOTH) ? 'w' : '-';
		if (perm & S_ISVTX && perm & S_IXOTH)
			mode_string[9] = 't';
		else if (perm & S_ISVTX && !(perm & S_IXOTH))
			mode_string[9] = 'T';
		else
			mode_string[9] = (perm & S_IXOTH) ? 'x' : '-';
		return (mode_string);
}

void print_list(char *dir, t_margin margin, char *dir_path)
{
	char *tmp;
	struct stat obj;
	struct passwd *usr;
	struct group  *grp;
	char *time1;
	char *tmp2;
	char *buff;

	if (dir_path != NULL)
		tmp2 = get_next_dir(&dir_path, dir);
	else
		tmp2 = ft_strdup(dir);
	if (lstat(tmp2, &obj) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		return;
	}
	else
	{
		tmp = get_permissions(obj);
		ft_printf("%s", tmp);
		ft_printf("  %*d", margin.block, obj.st_nlink);
		usr = getpwuid(obj.st_uid);
		ft_printf(" %-*s", margin.uid, usr->pw_name);
		grp = getgrgid(obj.st_gid);
		ft_printf("  %-*s", margin.group, grp->gr_name);
	 	if (S_ISBLK(obj.st_mode) || S_ISCHR(obj.st_mode))
			major_minor_device(obj);
		if (!(S_ISBLK(obj.st_mode) || S_ISCHR(obj.st_mode)))
			ft_printf("  %*zu", margin.size, obj.st_size);
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

		ft_printf(" %-s", dir);
		if (S_ISLNK(obj.st_mode))
		{
			buff = (char *)malloc(sizeof(char) * 5000);
			readlink(tmp2, buff,5000);
			ft_printf(" -> ");
			ft_printf("%s", buff);
		}
		ft_printf("\n");
		free(tmp);
	}

}

void list_or_not(t_flagls *flags, char **dir, char *dir_path)
{
	unsigned i;
	unsigned total;
	t_margin margin;

	margin.size = 0;
	margin.block = 0;
	margin.uid = 0;
	margin.group = 0;
	total = total_sum_ls(dir, &margin, dir_path);

	if (flags->flag[3] == 1 && (int)total >= 0)
		ft_printf("total %u\n", total);
	i = 0;
	if (flags->flag[2] == 1)
	{
		if (dir != NULL)
		{
			while (dir[i] != 0)
				i++;
			while (i > 0) {
				i--;
				if (flags->flag[3] == 1)
					print_list(dir[i], margin, dir_path);
				else
					ft_printf("%s\n", dir[i]);
			}
		}
		else
		{
			if (flags->flag[3] == 1)
				print_list(dir_path, margin, NULL);
			else
				ft_printf("%s\n", dir_path);
		}
	}
	else {
		if (dir != NULL)
			while (dir[i] != 0)
			{
				if (flags->flag[3] == 1)
				print_list(dir[i], margin, dir_path);
				else
					ft_printf("%s\n", dir[i]);
				i++;

			}
		else
		{
			if (flags->flag[3] == 1)
				print_list(dir_path, margin, NULL);
			else
				ft_printf("%s\n", dir_path);
		}
	}
	//ft_printf("\n");
}
