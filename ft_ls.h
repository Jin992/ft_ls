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
#define FT_LS_MAIN_FT_LS_H
#include "lib/includes/libft.h"
#include "lib/includes/ft_printf.h"
#include "errno.h"
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct	s_flagls
{
	int flag[12];
	int show_path;
	int flag_cnt;
	int expt;
	int argc;
}				t_flagls;

typedef struct s_margin
{
	int block;
	int uid;
	int size;
	int group;
}				t_margin;
typedef struct	s_grid
{
	int		term_cols;
	int		col_len;
	int		file_qnt;
}			t_grid;



int validate_flags(int argc, char **argv, t_flagls *flag, size_t *i);
int		read_dir(char *dir_path, t_flagls *flag);
char	**sort_args(char **argv, int argc);
char **sort_args_type(char **args, t_flagls *flag);
int is_dir(const char *path);
int dir_len(char **arr);
void sort_strs(char **arr, t_flagls * flagls, int n, char *dir);
void list_or_not(t_flagls *flags, char **dir, char *dir_path);
char *get_next_dir(char **cur_dir, char *next_dir);
void time_sort(char **arr, int n, char *dir);
void swap_strs(char **arg1, char **arg2);
int doesnt_exist(char **args, t_flagls *flags);
#endif //FT_LS_MAIN_FT_LS_H
