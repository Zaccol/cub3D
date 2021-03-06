/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:51:23 by lzaccome          #+#    #+#             */
/*   Updated: 2022/07/10 18:08:49 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_wrong_elem(char c, t_stuff *stuff, int i, int j)
{
	if (c == '0')
		return (0);
	else if (c == '1')
		return (0);
	else if (c == 'P')
	{
		stuff->p_cnt++;
		if (stuff->p_cnt != 1)
			return (1);
		stuff->px = j;
		stuff->py = i;
		return (0);
	}
	return (1);
}

void	verif_map(char **map, t_stuff *stuff)
{
	if (stuff->p_cnt == 0)
		free_map_exit(map, stuff->line_count, "Error : nop_cnt\n");
	return ;
}

void	parse_map(char **map, t_stuff *stuff)
{
	int		i;
	int		j;

	i = 0;
	while (map && stuff && i < stuff->line_count && map[i])
	{
		j = 0;
		while (i < stuff->line_count && map[i][j])
		{
			if ((i == 0 || i == stuff->line_count - 1) && map[i][j] != '1')
				free_map_exit(map, stuff->line_count, "Err: unclosed map\n");
			else
				if ((j == 0 || j == stuff->line_len - 1) && map[i][j] != '1')
					free_map_exit(map, stuff->line_count, "Err: unclosed map\n");
			else if (is_wrong_elem(map[i][j], stuff, i, j))
				free_map_exit(map, stuff->line_count, "Err: invalid element\n");
			j++;
		}
		i++;
	}
	verif_map(map, stuff);
	return ;
}
