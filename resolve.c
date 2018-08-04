/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:17:05 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/03 20:51:52 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    toggle(boards *board, piece *p)//toggle the piece in board and toggle is->placed.
{//add toggle firstcheck
    board->row[p[board->current].ylast] ^= p[board->current].value[0];
    board->row[p[board->current].ylast + 1] ^= p[board->current].value[1];
    board->row[p[board->current].ylast + 2] ^= p[board->current].value[2];
    board->row[p[board->current].ylast + 3] ^= p[board->current].value[3];
}

void  shifter(piece *p, boards *board, uint8_t lr)//lr 1 means right shift 1, 
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

int checkit(piece *p, boards *board)
{
    if (!(board->row[p[board->current].ylast] & p[board->current].value[0]) 
		&& !(board->row[p[board->current].ylast + 1] & p[board->current].value[1])
        && !(board->row[p[board->current].ylast + 2] & p[board->current].value[2]) 
		&& !(board->row[p[board->current].ylast + 3] & p[board->current].value[3]))
        return (1);
    return (0);
}

void unshift(piece *p, boards *board)
{
	p[board->current].value[0] <<= p[board->current].xlast;
	p[board->current].value[1] <<= p[board->current].xlast;
	p[board->current].value[2] <<= p[board->current].xlast;
	p[board->current].value[3] <<= p[board->current].xlast;
}

int sameas(piece *p, boards *board)
{
	if (p[board->current].value[0] == p[(board->current- 1)].value[0]
		&& p[board->current].value[1] == p[(board->current- 1)].value[1]
		&& p[board->current].value[2] == p[(board->current- 1)].value[2]
		&& p[board->current].value[3] == p[(board->current- 1)].value[3])
		return (1);
	return (0);
}

int checker(piece *p, boards *board)
{
	int flag = 1;
	if (!(p[board->current].id >= 'A' && p[board->current].id <= 'Z'))
		return (1);
    if ((p[board->current].width > board->size) || (p[board->current].height > board->size))
        return (2);
    p[board->current].xlast = 0;
    p[board->current].ylast= 0;
	if (p[board->current].id != 'A' && sameas(p, board))
	{
		p[board->current].xlast = p[board->current - 1].xlast;
		p[board->current].ylast = p[board->current - 1].ylast;
	}
	while ((p[board->current].ylast + p[board->current].height) <= board->size)
	{
		while ((p[board->current].xlast + p[board->current].width) <= board->size)
		{
			if (checkit(p, board))
			{
				toggle(board, p);
                board->current++;
                if ((flag = checker(p, board)) == 1)
                    return (1);
                board->current--;
                toggle(board, p);
				if (flag == 2)//if piece was too big in any pos
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

int     solver(piece *p, boards *board)
{
	board->size = 3;
    while (board->size < 52)
    {
		zero_it(board, p);
        if(checker(p, board) == 1)
            return (1);
        board->size++;
    }
    return (0);
}
