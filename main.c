/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mai.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:28:04 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/05 17:44:28 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	size_t		i;
	t_flagls	flag;
	char		**args;

	i = 0;
	args = NULL;
	if (validate_flags(argc, argv, &flag, &i) > 0)
		return (1);
	if (argc - i > 0)
		if ((args = sort_args_type(sort_args(argv, argc), &flag)) == NULL)
			return (0);
	i = 0;
	if (args == NULL)
		read_dir(".", &flag);
	else
		if (flag.flag[2] == 1)
		{
			while (args[i] != NULL)
				i++;
			while (i > 0)
			{
				i--;
				read_dir(args[i], &flag);
			}
		}
		else
			while (args[i] != NULL)
			{
				read_dir(args[i], &flag);
				i++;
			}
	return (0);
}
