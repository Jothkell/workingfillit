/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:33:33 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/05 16:55:10 by jkellehe         ###   ########.fr       */
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

int				valid_pieces(char *buf)
{
	if (haystack(buf, "#...#...#...#", 0) ||
		haystack(buf, "####", 0) ||
		haystack(buf, "#...#...##", 0) ||
		haystack(buf, "##...#...#", 0) ||
		haystack(buf, "..#.###", 0) ||
		haystack(buf, "###.#", 0) || haystack(buf, ".#...#..##", 0) ||
		haystack(buf, "##..#...#", 0) || haystack(buf, "#...###", 0) ||
		haystack(buf, "###...#", 0) || haystack(buf, "##..##", 0) ||
		haystack(buf, "###..#", 0) || haystack(buf, ".#..###", 0) ||
		haystack(buf, "#...##..#", 0) || haystack(buf, ".#..##...#", 0) ||
		haystack(buf, "##...##", 0) || haystack(buf, ".#..##..#", 0) ||
		haystack(buf, "##.##", 0) || haystack(buf, "#...##...#", 0))
		return (1);
	return (0);
}

int				haystack(char *haystack, char *needle, int rewind)
{
	if (*needle == '\0')
		return (1);
	while (*haystack != '\0' && !(rewind = 0))
	{
		if (*haystack == '\n')
			haystack++;
		if (*haystack == needle[rewind])
		{
			while (*haystack == needle[rewind] || *haystack == '\n')
			{
				if (*haystack == '\0')
					return (0);
				if (*haystack != '\n')
				{
					rewind++;
					if (needle[rewind] == '\0')
						return (1);
				}
				haystack++;
			}
			haystack -= rewind;
		}
		haystack++;
	}
	return (0);
}
