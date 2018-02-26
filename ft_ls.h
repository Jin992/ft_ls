/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:28:54 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/06 10:29:01 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_MAIN_FT_LS_H
# define FT_LS_MAIN_FT_LS_H
# include "lib/includes/libft.h"
# include "lib/includes/ft_printf.h"
# include "errno.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>

typedef struct	s_flagls
{
	int flag[13];
	int show_path;
	int flag_cnt;
	int expt;
	int argc;
}				t_flagls;

typedef struct	s_margin
{
	int			block;
	int			uid;
	int			size;
	int			group;
	ssize_t		acl;
	char		acl_buff[2000];
	int			ext_atr;
}				t_margin;
int				val_flags(int argc, char **argv, t_flagls *flag, size_t *i);
int				read_dir(char *dir_path, t_flagls *flag);
char			**sort_args(char **argv, int argc, t_flagls *flag);
char			**sort_args_type(char **args, t_flagls *flag);
int				is_dir(const char *path);
int				dir_len(char **arr);
void			sort_strs(char **arr, t_flagls *flagls, int n, char *dir);
void			list_or_not(t_flagls *flags, char **dir, char *dir_path);
void			time_sort(char **arr, int n, char *dir);
void			swap_strs(char **arg1, char **arg2);
int				doesnt_exist(char **args, t_flagls *flags);
void			rev_arr(char **arr);
void			error_path(int flag_e, t_flagls *flag, char *dir_path);
char			*get_next_dir(char **cur_dir, char *next_dir);
int				permission_check(char *dir, t_flagls *flag);
int				dir_reader(char *dir, int *flag_e, t_flagls *flag, size_t *i);
char			**make_arr(char *dir, t_flagls *flag, int *flag_e, size_t *i);
void			print_list(char *dir, t_margin margin, char *dir_path);
char			*get_permissions(struct stat obj, t_margin margin);
unsigned int	total_sum_ls(char **str, t_margin *margin, char *dir_path);
int				ls_digit_len(int digit);
int				clean_array(int i, t_flagls *flag, char **args, char **tmp);
int				r(t_flagls *flag, char **res, size_t *i_j, struct dirent *obj);
int				read_bls(DIR *dir_fd, t_flagls *flag, char **res, size_t *i_j);
void			get_acl(t_margin margin, char *tmp2);
void			perm_error(char *tmp2);
void			bonus(char *str, size_t i, t_flagls *flag);
#endif
