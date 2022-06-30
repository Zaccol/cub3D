/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:19:03 by lzaccome          #+#    #+#             */
/*   Updated: 2022/06/30 04:35:32 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"

# define PI 3.1415926535
# define TILE_SIZE 64
# define FOV_ANGLE 60 * (PI / 180)
// # define NUM_RAYS 

// mp = position sur la map
// dof = nombre d'intersections checked

// typedef struct s_raycast
// {
// 	int		r;
// 	int		mx;
// 	int		my;
// 	int		mp;
// 	int		dof;
// 	float	rx;
// 	float	ry;
// 	float	ra;
// 	float	xo;
// 	float	yo;
// }				t_raycast;

/*
 step = le pas pour arriver a la prochaine collision avec la grille
 intercept = les coordeonnees de l'intercection avec une ligne
 next_htouchy = coordonnees d'intersection +1 pour tomber dans la case
 */

typedef struct	s_raycast
{
	float	wall_hitx;
	float	wall_hity;
	float	hrz_wall_hitx;
	float	hrz_wall_hity;
	float	vrt_wall_hitx;
	float	vrt_wall_hity;
	float	v_distance;
	float	h_distance;
	float	distance;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	next_htouchx;
	float	next_htouchy;
	float	next_vtouchx;
	float	next_vtouchy;
	int		found_vhit;
	int		found_hhit;
	int		was_hit_vrt;
	int		up;
	int		down;
	int		right;
	int		left;
}					t_raycast;

typedef struct s_stuff
{
	int			line_count;
	int			line_len;
	int			player;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float 		pa; //player angle
	int			map_width;
	int			map_height;
	t_raycast	raycast;
	
}				t_stuff;

typedef struct s_data {
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}				t_data;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_combo {
	t_data		*mlx;
	t_stuff		*stuff;
	t_img		*img;
	char		**map;
	int			count;
}				t_combo;

typedef struct s_rect {
	int	x;
	int	y;
	int	width;
	int	height;
}				t_rect;


/* -------------------------------------------------------------------------- */
/*                              FILE = ./main.c                               */
/* -------------------------------------------------------------------------- */
char	**malloc_map(int fd, t_stuff *stuff);
void	get_map(int fd, char **map, t_stuff *stuff);
void	init_stuff(t_stuff *stuff);
void	display_map(char **map, t_stuff stuff);
int		main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./parse.c                              */
/* -------------------------------------------------------------------------- */
int		is_wrong_elem(char c, t_stuff *stuff, int i, int j);
void	verif_map(char **map, t_stuff *stuff);
void	parse_map(char **map, t_stuff *stuff);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./gnl_utils.c                          */
/* -------------------------------------------------------------------------- */
int		ft_strclen(char *s, char c);
char	*ft_strcdup(char *s, char c);
int		ft_strlen(char *str);
char	*ft_strcjoin(char *s1, char *s2, char c);
char	*ft_strchr(char *s, char c);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./get_next_line.c                      */
/* -------------------------------------------------------------------------- */
int		strchr_backslash(char *buf, int loop);
void	shift_str(char *str);
char	*get_next_line(int fd);
void	free_line(char *line);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./error.c                              */
/* -------------------------------------------------------------------------- */
void	error(void);
void	free_map(char **map, int line_count);
void	free_map_exit(char **map, int line_count, char *message);
void	free_map_exit2(char **map, int line_failed, char *message);
void	error_message(char *message);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./utils.c                              */
/* -------------------------------------------------------------------------- */
void	ft_putstr(char *str);
void	ft_bzero(void *s, size_t n);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./mini_mmap.c                          */
/* -------------------------------------------------------------------------- */
void	mini_map(char **map, t_stuff stuff);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		ft_cross(t_combo *combo);
void	free_mlx(t_data *mlx, t_img *img, char **map, int line_count);
void	fill_grey(int width, int height, t_img *img);
void	draw_player(t_img *img, t_stuff stuff);
void	build_walls(char **map, t_img *img, t_stuff *stuff);
void	draw_rays(t_img *img, t_stuff stuff, char **map);
// void	draw_map(t_stuff stuff, t_img *img);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./direction.c                          */
/* -------------------------------------------------------------------------- */
int		direction(int keycode, t_combo *combo);
void	move_right(t_combo *combo);
void	move_up(t_combo *combo);
void	move_left(t_combo *combo);
void	move_down(t_combo *combo);

#endif