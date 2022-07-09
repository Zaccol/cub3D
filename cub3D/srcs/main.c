/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:43:52 by lzaccome          #+#    #+#             */
/*   Updated: 2022/07/08 17:28:42 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**malloc_map(int fd, t_stuff *stuff)
{
	char	**map;
	char	*line;

	map = NULL;
	line = get_next_line(fd);
	if (!line || line[0] == 0)
	{
		free(line);
		error();
	}
	stuff->line_len = ft_strlen(line);
	while (line)
	{
		free(line);
		(stuff->line_count)++;
		line = get_next_line(fd);
	}
	map = malloc((stuff->line_count) * sizeof(char *));
	if (!map)
		error();
	return (map);
}

void	get_map(int fd, char **map, t_stuff *stuff)
{
	int	i;

	i = 0;
	map[i] = get_next_line(fd);
	if (!map[i])
		free_map_exit(map, i, "Error : gnl failed\n");
	i++;
	while (i < stuff->line_count)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			free_map_exit(map, i, "Error : gnl failed\n");
		if (ft_strlen(map[i]) != stuff->line_len)
			free_map_exit2(map, i, "Error : unrectangular map\n");
		i++;
	}
	parse_map(map, stuff);
	return ;
}

// void	init_stuff(t_stuff *stuff)
// {
// 	stuff->line_count = 0;
// 	stuff->line_len = 0;
// 	stuff->player = 0;
// 	stuff->px = 0;
// 	stuff->py = 0;
// 	stuff->pdx = 0;
// 	stuff->pdy = 0;
// 	stuff->pa = 0;
// 	return ;
// }

void	display_map(char **map, t_stuff stuff)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	// printf("lline_count : %i\nline_len : %i\n", stuff.line_count, stuff.line_len);
	while (i < stuff.line_count)
	{
		while (j < stuff.line_len)
		{
			printf("%c ", map[i][j]);
			j++;
		}
		j = 0;
		printf("\n");
		i++;
	}
	return ;
}

int	main(int ac, char **av)
{
	int		fd;
	t_stuff	stuff;
	char	**map;
	
	// init_stuff(&stuff);
	ft_bzero(&stuff, sizeof(t_stuff));
	if (ac != 2)
		error();
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error();
	map = malloc_map(fd, &stuff);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error();
	get_map(fd, map, &stuff);
	display_map(map, stuff);
	mini_map(map, stuff);
	free_map(map, stuff.line_count);
	return (1);
}