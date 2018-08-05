/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:38:23 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/04 20:18:00 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int				bitter(char *buf, t_piece *p)
{
	int			j;
	uint64_t	value;
	int			girth;

	p->width = 0;
	girth = 0;
	p->i = 1;
	value = 0;
	j = 0;
	while (p->i <= 20)
	{
		if (*buf == '#' || *buf == '.')
			value <<= 1;
		if (*buf == '#' && (girth += 1))
			value += 1;
		if (!(p->i % 5) && *buf == '\n' && ((value += 0) || !(value)))
		{
			p->width = (girth > p->width) ? (girth) : (p->width);
			p->value[j++] = value;
			girth = (value <<= 32) ? (0) : (0);
		}
		(p->i += 1) ? (buf += 1) : (buf += 1);
	}
	slider(p->value);
	return (0);
}

int				check_valid(char *buf)
{
	int			i;
	int			count;

	count = 0;
	i = 1;
	while (i <= 20)
	{
		if (!(i % 20) && (*buf != '\n' || (buf[1] != '\n' && buf[1])))
			return (0);
		if (((i % 5) && (*buf != '#' && *buf != '.'))
			|| (!(i % 5) && (*buf != '\n')))
			return (0);
		count += ((*buf == '#') ? 1 : 0);
		buf++;
		i++;
	}
	if (count != 4)
		return (0);
	return (1);
}

int				reader(int fd, t_piece *p)
{
	int			bytes;
	char		buf[22];
	char		letter;
	int			i;

	i = 0;
	letter = 'A';
	while ((bytes = read(fd, buf, 21)))
	{
		if (!(check_valid(buf)))
			return (0);
		bitter(buf, p);
		p->id = letter++;
		p += 1;
		i++;
	}
	p->id = 0;
	return (1);
}

int				zero_it(t_boards *board, t_piece *p)
{
	int			i;

	i = 0;
	while (i < 28)
	{
		p[i].placed = 0;
		p[i].firstcheck = 1;
		p[i].xlast = 0;
		p[i].ylast = 0;
		i++;
	}
	board[0].final = (char)malloc(sizeof(char));
	i = 0;
	board[0].tlx = 0;
	board[0].tly = 0;
	board[0].xmax = 0;
	board[0].ymax = 0;
	board[0].current = 0;
	board[0].i = 0;
	while (i < 52)
	{
		board[0].row[i] = 0;
		i++;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int			file;
	t_piece		p[27];
	t_boards	*board;

	if (argc != 2)
	{
		write(1, "this is error", 11);
		return (1);
	}
	file = open(argv[1], O_RDONLY);
	board = (t_boards*)malloc(sizeof(t_boards) * 2);
	zero_it(board, p);
	if (!reader(file, p))
	{
		write(1, "you did it wrong", 13);
		return (1);
	}
	board->final = get_final(p, board);
	board->size = 3;
	if (solver(p, board))
		printer(p, board);
	else
		write(1, "sorry, no answer\n", 17);
	return (0);
}
