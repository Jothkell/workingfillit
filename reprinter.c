/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprinter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 00:18:25 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/05 17:14:38 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void			periods(char **res)
{
	int			j;
	int			i;

	j = 0;
	i = 0;
	while (i < 52)
	{
		res[i] = (char*)malloc(sizeof(char) * 53);
		j = 0;
		while (j < 52)
		{
			res[i][j] = '.';
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
}

void			printer(t_piece *p, t_boards *board)
{
	char		**res;
	int			j;
	int			k;
	uint64_t	hold;

	hold = 0;
	k = 0;
	j = 0;
	board->i = 0;
	board->ymax = 25;
	board->tly = 25;
	board->xmax = 0;
	board->tlx = 52;
	res = (char**)malloc(sizeof(char*) * 53);
	periods(res);
	while (p[board->i].id >= 'A' && p[board->i].id <= 'Z')
	{
		ip(hold, board, p, res);
		board->tly = ((p[board->i].ylast + 25) < board->tly) ?
			(p[board->i].ylast + 25) : (board->tly);
		board->i++;
	}
	print_res(res, board);
}

void			ip(uint64_t hold, t_boards *board, t_piece *p, char **res)
{
	int			k;
	int			j;

	j = 0;
	while (j < 4)
	{
		hold = p[board->i].value[j];
		k = 52;
		while (hold)
		{
			if (hold % 2 == 1)
			{
				res[25 + j + p[board->i].ylast][k] = p[board->i].id;
				board->xmax = (k > board->xmax) ? (k) : (board->xmax);
				board->ymax = ((p[board->i].ylast + j + 25) > board->ymax) ?
					(p[board->i].ylast + j + 25) : (board->ymax);
			}
			else if (hold % 2 == 0 && res[25 + j + p[board->i].ylast][k] == '.')
				res[25 + j + p[board->i].ylast][k] = ' ';
			hold /= 2;
			k--;
		}
		board->tlx = (k < board->tlx) ? (k + 1) : (board->tlx);
		j++;
	}
}

void			print_res(char **res, t_boards *board)
{
	int			i;
	int			j;
	int			flag;

	flag = 1;
	i = board->tly;
	j = board->tlx;
	while (i <= board->ymax || i < (board->size + board->tly))
	{
		j = board->tlx;
		while (j <= board->xmax || j < (board->size + board->tlx))
		{
			if (res[i][j] >= 'A' && res[i][j] <= 'Z')
				write(1, &res[i][j], 1);
			else
				write(1, ".", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
