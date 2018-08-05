/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:17:05 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/04 20:24:18 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		checkit(t_piece *p, t_boards *board)
{
	if (!(board->row[p[board->current].ylast] & p[board->current].value[0])
		&& !(board->row[p[board->current].ylast + 1]
		& p[board->current].value[1])
		&& !(board->row[p[board->current].ylast + 2]
		& p[board->current].value[2])
		&& !(board->row[p[board->current].ylast + 3]
		& p[board->current].value[3]))
		return (1);
	return (0);
}

void	unshift(t_piece *p, t_boards *board)
{
	p[board->current].value[0] <<= p[board->current].xlast;
	p[board->current].value[1] <<= p[board->current].xlast;
	p[board->current].value[2] <<= p[board->current].xlast;
	p[board->current].value[3] <<= p[board->current].xlast;
}

int		sameas(t_piece *p, t_boards *board)
{
	if (p[board->current].value[0] == p[(board->current - 1)].value[0]
		&& p[board->current].value[1] == p[(board->current - 1)].value[1]
		&& p[board->current].value[2] == p[(board->current - 1)].value[2]
		&& p[board->current].value[3] == p[(board->current - 1)].value[3])
		return (1);
	return (0);
}

int		checker(t_piece *p, t_boards *board)
{
	if ((board->flag = sub_checker(p, board)))
		return (board->flag);
	while ((p[board->current].ylast + p[board->current].height) <= board->size)
	{
		while (p[board->current].xlast + p[board->current].width <= board->size)
		{
			if (checkit(p, board))
			{
				toggle(board, p);
				board->current++;
				if ((board->flag = checker(p, board)) == 1)
					return (1);
				board->current--;
				toggle(board, p);
				if (board->flag == 2)
					return (2);
			}
			shifter(p, board, 1);
			p[board->current].xlast++;
		}
		unshift(p, board);
		p[board->current].xlast = 0;
		p[board->current].ylast++;
	}
	return (0);
}

int		solver(t_piece *p, t_boards *board)
{
	board->size = (board->pnum) * 2;
	while (1 == checker(p, board))
	{
		board->current = 0;
		while (p[board->current].id >= 'A' && p[board->current].id <= 'Z')
		{
			unshift(p, board);
			board->current++;
		}
		p[board->current].xlast = 0;
		board->size--;
		zero_it(board, p);
	}
	board->current = 0;
	while (p[board->current].id >= 'A' && p[board->current].id <= 'Z')
	{
		unshift(p, board);
		board->current++;
	}
	p[board->current].xlast = 0;
	zero_it(board, p);
	board->size++;
	if (checker(p, board) == 1)
		return (1);
	return (0);
}
