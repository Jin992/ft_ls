/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:33:22 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/06 10:33:25 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		flags_init(t_flagls *flags, int argc)
{
	size_t i;

	i = 0;
	while (i < 10)
		flags->flag[i++] = 0;
	flags->show_path = 0;
	flags->flag_cnt = 0;
	flags->argc = argc;
	flags->expt = 0;
}

static int		illegal_option(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(((unsigned int)c), 2);
	ft_putstr_fd("\n", 2);
	return (10);
}

static int		ls_flags(char *str, t_flagls *flag)
{
	char	*flags;
	size_t	i;
	size_t	j;

	i = 1;
	flags = "aRrlt1*@fA";
	while (str[i] != '\0')
	{
		j = 0;
		while (flags[j] != '\0')
		{
			if (flags[j] == str[i])
			{
				flag->flag[j] = 1;
				break ;
			}
			j++;
		}
		bonus(str, i, flag);
		if (flags[j] == '\0')
			return (illegal_option(str[i]));
		i++;
	}
	flag->flag_cnt++;
	return (0);
}

static int		minus_validation(char **argv, size_t *i, t_flagls *flag)
{
	if (argv[*i][0] != '-')
		return (1);
	if (argv[*i][0] == '-' && argv[*i][1] == '\0')
		return (1);
	if (argv[*i][0] == '-' && argv[*i][1] == '-' && argv[*i][2] == '\0')
	{
		flag->flag_cnt++;
		flag->flag[6] = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int				val_flags(int argc, char **argv, t_flagls *flag, size_t *i)
{
	flags_init(flag, argc);
	*i = 1;
	if (argc < 2)
		return (0);
	if (argv[*i][0] == '-' && argv[*i][1] == '\0')
		return (0);
	while (*i < (size_t)argc)
	{
		if (minus_validation(argv, i, flag) == 1)
			return (0);
		if (ls_flags(argv[*i], flag) > 0)
		{
			ft_putstr_fd("usage: ls [-aRltr1@fA] [file ...]\n", 2);
			return (10);
		}
		(*i)++;
	}
	return (0);
}
