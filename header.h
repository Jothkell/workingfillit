/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dknoll <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:15 by dknoll            #+#    #+#             */
/*   Updated: 2018/08/04 20:18:36 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_piece		t_piece;
typedef struct s_boards		t_boards;

struct				s_piece
{
	uint64_t		value[4];
	uint8_t			id;
	int				xhold;
	int				xlast;
	int				ylast;
	uint8_t			placed;
	uint8_t			width;
	uint8_t			height;
	uint8_t			firstcheck;
	uint8_t			i;
};

struct				s_boards
{
	char			final;
	unsigned int	pnum;
	unsigned int	current;
	uint64_t		row[52];
	int				size;
	int				i;
	int				tlx;
	int				tly;
	int				xmax;
	int				ymax;
	uint8_t			count;
	uint8_t			hold;
	uint8_t			flag;
};

int					sameas(t_piece *p, t_boards *board);
int					sub_checker(t_piece *p, t_boards *board);
void				shifter(t_piece *p, t_boards *board, uint8_t lr);
char				get_final(t_piece *p, t_boards *board);
void				slider(uint64_t *value);
int					solver(t_piece *p, t_boards *board);
int					is_piece(t_piece is);
void				toggle(t_boards *board, t_piece *p);
int					checker(t_piece *p, t_boards *board);
int					zero_it(t_boards *board, t_piece *p);
void				widtheight(t_piece *p, t_boards *board);
void				printer(t_piece *p, t_boards *board);
void				print_res(char **res, t_boards *board);
void				periods(char **res);
void				printer(t_piece *p, t_boards *board);
void				ip(uint64_t hold, t_boards *board, t_piece *p, char **res);

#endif
