/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:33:33 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/04 19:40:44 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char			get_final(t_piece *p, t_boards *board)
{
	int			i;
	int			j;
	int			height;

	height = 0;
	j = 0;
	i = 0;
	while (p[i].id >= 'A' && p[i].id <= 'Z')
	{
		j = 0;
		height = 0;
		if ((p[i].value[1] == 51539607552 && p[i].value[0] == 25769803776)
			|| (p[i].value[0] == 51539607552 && p[i].value[1] == 25769803776))
			p[i].width++;
		while (j++ < 4)
			if (p[i].value[j] > 0)
				height++;
		p[i].height = height;
		i++;
	}
	board->pnum = i;
	i--;
	return (p[i].id);
}

int				get_top(uint64_t *value)
{
	int			i;
	int			j;
	uint64_t	holder;

	j = 0;
	i = 0;
	while (i < 4)
	{
		holder = value[i];
		j = 0;
		while (j < 35 && holder)
		{
			holder /= 2;
			j++;
		}
		if (holder == 1)
			return (0);
		i++;
	}
	return (1);
}

void			switch_em(uint64_t *value)
{
	value[0] = value[1];
	value[1] = value[2];
	value[2] = value[3];
	value[3] = 0;
}

void			slider(uint64_t *value)
{
	while (get_top(value))
	{
		value[0] <<= 1;
		value[1] <<= 1;
		value[2] <<= 1;
		value[3] <<= 1;
	}
	while (value[0] == 0)
		switch_em(value);
}
