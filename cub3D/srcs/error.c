/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:55:13 by lzaccome          #+#    #+#             */
/*   Updated: 2022/06/07 21:11:49 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

// unclosed map

void	free_map_exit(char **map, int line_failed, char *message)
{
	int	i;

	i = 0;
	while (i < line_failed)
	{
		free(map[i]);
		i++;
	}
	free(map);
	ft_putstr(message);
	exit(EXIT_FAILURE);
}
// unrectangular map

void	free_map_exit2(char **map, int line_failed, char *message)
{
	int	i;

	i = 0;
	while (i <= line_failed)
	{
		free(map[i]);
		i++;
	}
	free(map);
	ft_putstr(message);
	exit(EXIT_FAILURE);
}
void	free_map(char **map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
