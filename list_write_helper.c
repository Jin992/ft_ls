/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_write_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:23:41 by earteshc          #+#    #+#             */
/*   Updated: 2018/02/26 14:23:44 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_acl(t_margin margin, char *tmp2)
{
	ssize_t	attr_size;
	int		i;

	i = 0;
	if (margin.acl > 0 && margin.ext_atr == 1)
		while (margin.acl > 0)
		{
			attr_size = getxattr(tmp2,\
			&margin.acl_buff[i], NULL, sizeof(margin.acl_buff),\
			0, XATTR_NOFOLLOW);
			if (attr_size == -1)
				break ;
			write(1, "        ", 8);
			while (margin.acl_buff[i] != '\0')
				write(1, &(margin.acl_buff[i++]), 1);
			i++;
			ft_printf("\t%4zd\n", attr_size);
			margin.acl--;
		}
}
