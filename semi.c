/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:38:23 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/05 16:57:26 by jkellehe         ###   ########.fr       */
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
	if (!(valid_pieces(buf)))
		return (0);
	while (i <= 20)
	{
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
	char		hold;

	i = 0;
	letter = 'A';
	while (20 == (bytes = read(fd, buf, 20)))
	{
		if (!(check_valid(buf)))
			return (0);
		bitter(buf, p);
		p->id = letter++;
		if (!(bytes = read(fd, &hold, 1)))
			return (1);
		p += 1;
		i++;
	}
	return (0);
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
		write(1, "usage: ./fillit input_file\n", 27);
		return (1);
	}
	file = open(argv[1], O_RDONLY);
	board = (t_boards*)malloc(sizeof(t_boards) * 2);
	zero_it(board, p);
	if (!reader(file, p))
	{
		write(1, "error\n", 6);
		return (1);
	}
	board->final = get_final(p, board);
	board->size = 3;
	if (solver(p, board))
		printer(p, board);
	return (0);
}
