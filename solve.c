/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:42:11 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/05 16:27:47 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			toggle(t_boards *board, t_piece *p)
{
	board->row[p[board->current].ylast] ^= p[board->current].value[0];
	board->row[p[board->current].ylast + 1] ^= p[board->current].value[1];
	board->row[p[board->current].ylast + 2] ^= p[board->current].value[2];
	board->row[p[board->current].ylast + 3] ^= p[board->current].value[3];
}

void			shifter(t_piece *p, t_boards *board, uint8_t lr)
{
	if (lr)
	{
		p[board->current].value[0] >>= 1;
		p[board->current].value[1] >>= 1;
		p[board->current].value[2] >>= 1;
		p[board->current].value[3] >>= 1;
	}
	else
	{
		p[board->current].value[0] <<= 1;
		p[board->current].value[1] <<= 1;
		p[board->current].value[2] <<= 1;
		p[board->current].value[3] <<= 1;
	}
}

int				sub_checker(t_piece *p, t_boards *board)
{
	if (!(p[board->current].id >= 'A' && p[board->current].id <= 'Z'))
		return (1);
	if ((p[board->current].width > board->size)
		|| (p[board->current].height > board->size))
		return (2);
	p[board->current].xlast = 0;
	p[board->current].ylast = 0;
	if (p[board->current].id != 'A' && sameas(p, board))
	{
		p[board->current].xlast = p[board->current - 1].xlast;
		p[board->current].ylast = p[board->current - 1].ylast;
	}
	return (0);
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
