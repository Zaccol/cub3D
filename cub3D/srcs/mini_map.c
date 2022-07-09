/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:14:23 by lzaccome          #+#    #+#             */
/*   Updated: 2022/07/09 17:12:07 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_mlx(t_data *mlx, t_img *img, char **map, int line_count)
{
	if (mlx->mlx)
	{
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free_map(map, line_count);
	exit(0);
}

int	ft_cross(t_combo *combo)
{
	free_mlx(combo->mlx, combo->img, combo->map, combo->stuff->line_count);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rect(t_rect rect, int color, t_img *img)
{
	float x;
	float y;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	return ;
}

unsigned int	get_pixel_color(t_img txt, int x, int y)
{
	char *dst;

	dst = txt->east.addr + (x * (txt->east.bits_per_pixel / 8) + y * txt->east.line_length);
	return((*(unsigned int*)dst));
}

t_img	get_wall_text(t_txt txt, float pa, int orientation)
{
	
}

void	draw_wall(t_img *img, t_stuff *stuff, t_txt txt, int x)
{
	int		y_off;
	int		x_off;
	int		y_start;
	int		y_end;
	float	wallstrip_height;
	int		txt_wallstrip;

	txt_wallstrip = 0;
	wallstrip_height = stuff->raycast->wallstrip_height;
	if (wallstrip_height > WINDOW_HEIGHT)
	{
		y_start = 0;
		y_end = WINDOW_HEIGHT;
	}
	else
	{
		y_start = (WINDOW_HEIGHT / 2 - wallstrip_height / 2);
		y_end = y_start + wallstrip_height;
	}
	if (stuff->raycast->was_hit_vrt[x] == 0)
	{
		x_off = (int)stuff->raycast->tab_hrz_x[x] % (int)TILE_SIZE;
		// printf("xoff x: %i\n", x_off);
	}
	else
	{
		x_off = (int)stuff->raycast->tab_hrz_y[x] % (int)TILE_SIZE;
		// printf("xoff y: %i\n", x_off);
	}
	x_off = (x_off * 64) / TILE_SIZE;
	if (wallstrip_height > WINDOW_HEIGHT)
		y_off = (wallstrip_height / 2 - WINDOW_HEIGHT / 2);
	else
		y_off = 0;
	while (y_start < y_end)
	{
		int txt_wallstrip = 0;
		while (txt_wallstrip < WALL_STRIP)
		{
			my_mlx_pixel_put(img, x, y_start, get_pixel_color(get_wall_text(txt, stuff->pa, stuff->raycast->was_hit_vrt[x]), x_off, (y_off * 64) / wallstrip_height));
			txt_wallstrip++;
		}
		y_start++;
		y_off++;
	}
}

void	fill_grey(int width, int height, t_img *img)
{
	int x;
	int y;
	// (void)width;
	// (void)height;

	x = 0;
	y = 0;
	while (y < height)
	{
		while (x < width)
		{
			my_mlx_pixel_put(img, x, y, 0x50505050);
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

int		has_wall_at(float x, float y, char **map, t_stuff stuff)
{
	int map_posx;
	int map_posy;

	if (x < 0 || x > stuff.map_width || y < 0 || y > stuff.map_height)
		return (1);
	map_posx = floor(x / TILE_SIZE);
	map_posy = floor(y / TILE_SIZE);
	if (map[map_posy][map_posx] == '1')
		return (1);
	return (0);
}

void	build_walls(char **map, t_img *img, t_stuff *stuff)
{
	int x;
	int y;
	t_rect	block;

	x = 0;
	y = 0;
	block.width = TILE_SIZE - 2;
	block.height = TILE_SIZE - 2;
	block.y = 0;
	block.x = 0;
	while (y < stuff->line_count)
	{
		while (x < stuff->line_len)
		{
			if (map[y][x] == '0' || map[y][x] == 'P')
				draw_rect(block, 0x00000000, img);
			else
				draw_rect(block, 0x009CFF9F, img);
			x++;
			block.x += TILE_SIZE;
		}
		block.x = 0;
		x = 0;
		block.y += TILE_SIZE;
		y++;
	}
	return ;
}

void	draw_player(t_img *img, t_stuff stuff)
{
	int width;
	int height;
	int i;

	width = -2;
	height = -2;
	i = 0;
	// printf("px : %i\npy : %i\n", px, py);
	while (height < 3)
	{
		while (width < 3)
		{
			my_mlx_pixel_put(img, stuff.px + width, stuff.py + height, 0xFFDC16);
			width++;
		}
		width = -2;
		height++;
	}
	while (i < (50 * MINIMAP_SCALE_FACTOR))
	{
		stuff.px += stuff.pdx/5;
		stuff.py += stuff.pdy/5;
		my_mlx_pixel_put(img, stuff.px, stuff.py, 0xFFDC16);
		i++;
	}
	return ;
}

// void	normalize_angle()
// {
	
// }

void	check_direction(t_raycast *raycast, float pa)
{
	raycast->down = 0;
	raycast->up = 0;
	raycast->left = 0;
	raycast->right = 0;
	if (pa > 0 && pa < PI)
		raycast->down = 1;
	else
		raycast->up = 1;
	if (pa < 0.5 * PI || pa > 1.5 * PI)
		raycast->right = 1;
	else
		raycast->left = 1;
	// printf("up : %i - down : %i - left : %i - right : %i\n", raycast->up, raycast->down, raycast->left, raycast->right);
}

int		is_in_map(float x, float y, float width, float length)
{
	if (x >= 0 && x <= width && y >= 0 && y <= length)
		return (1);
	return (0);
}

float	distance_bet_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	draw_rays(t_img *img, t_stuff *stuff, char **map)
{
	//////////////////////////////////////
	// HORIONTAL RAY-GRID INTERSECTIONS
	//////////////////////////////////////
	int		i;
	int		column_id;
	int		bc_angle;
	float	ray_angle;

	i = 0;
	stuff->raycast->num_rays = WINDOW_WIDTH / WALL_STRIP;
	column_id = 0;
	ray_angle = stuff->pa - (FOV_ANGLE / 2);
	stuff->raycast->rays = malloc(stuff->raycast->num_rays * sizeof(float));
	stuff->raycast->rays_angle = malloc(stuff->raycast->num_rays * sizeof(float));
	stuff->raycast->tab_hrz_x = malloc(stuff->raycast->num_rays * sizeof(float));
	stuff->raycast->tab_hrz_y = malloc(stuff->raycast->num_rays * sizeof(float));
	stuff->raycast->was_hit_vrt = malloc(stuff->raycast->num_rays * sizeof(float));
	if (!stuff->raycast->rays)
		return;
	while (i < stuff->raycast->num_rays)
	{
		bc_angle = 0;
		stuff->raycast->found_vhit = 0;
		stuff->raycast->found_hhit = 0;
		stuff->raycast->was_hit_vrt[i] = 0;
		if (ray_angle < 0)
			ray_angle += 2*PI;
		if (ray_angle > 2*PI)
		ray_angle -= 2*PI;
		check_direction(stuff->raycast, ray_angle);
		// y-coord of the closest horizontal grid intersection
		stuff->raycast->yintercept = (floor(stuff->py / TILE_SIZE) * TILE_SIZE);
		if (stuff->raycast->down)
			stuff->raycast->yintercept += TILE_SIZE;
			
		// x-coord of the cosst horizontal grid intersection
		stuff->raycast->xintercept = stuff->px + (stuff->raycast->yintercept - stuff->py) / tan(ray_angle);
		
		// calculate increment xstep step
		stuff->raycast->ystep = TILE_SIZE;
		if (stuff->raycast->up)
			stuff->raycast->ystep *= -1;
			
		stuff->raycast->xstep = TILE_SIZE / tan(ray_angle);
		if (stuff->raycast->left && stuff->raycast->xstep > 0)
			stuff->raycast->xstep *= -1;
		if (stuff->raycast->right && stuff->raycast->xstep < 0)
			stuff->raycast->xstep *= -1;
			
		stuff->raycast->next_htouchx = stuff->raycast->xintercept;
		stuff->raycast->next_htouchy = stuff->raycast->yintercept;
		
		if (stuff->raycast->up)
			bc_angle = 1;
		
		// increment xstep and ystep until we find a wall
		while (is_in_map(stuff->raycast->next_htouchx, stuff->raycast->next_htouchy, stuff->map_width, stuff->map_height))
		{
			if (has_wall_at(stuff->raycast->next_htouchx, stuff->raycast->next_htouchy - bc_angle, map, *stuff))
			{
				stuff->raycast->found_hhit = 1;
				stuff->raycast->hrz_wall_hitx = stuff->raycast->next_htouchx;
				stuff->raycast->hrz_wall_hity = stuff->raycast->next_htouchy;
				// my_mlx_pixel_put(img, stuff->raycast->hrz_wall_hitx, stuff->raycast->hrz_wall_hity, 0xFF4141);
				break;
			}
			else
			{
				stuff->raycast->next_htouchx += stuff->raycast->xstep;
				stuff->raycast->next_htouchy += stuff->raycast->ystep;
			}
		}
		bc_angle = 0;
		//////////////////////////////////////
		// VERTICAL RAY-GRID INTERSECTIONS
		//////////////////////////////////////

		// check_direction(&stuff->raycast, ray_angle);
		// x-coord of the closest vertical grid intersection
		stuff->raycast->xintercept = (floor(stuff->px / TILE_SIZE) * TILE_SIZE);
		if (stuff->raycast->right)
			stuff->raycast->xintercept += TILE_SIZE;
			
		// y-coord of the cosst vertical grid intersection
		stuff->raycast->yintercept = stuff->py + (stuff->raycast->xintercept - stuff->px) * tan(ray_angle);
		
		// calculate increment xstep step
		stuff->raycast->xstep = TILE_SIZE;
		if (stuff->raycast->left)
			stuff->raycast->xstep *= -1;
			
		stuff->raycast->ystep = TILE_SIZE * tan(ray_angle);
		if (stuff->raycast->up && stuff->raycast->ystep > 0)
			stuff->raycast->ystep *= -1;
		if (stuff->raycast->down && stuff->raycast->ystep < 0)
			stuff->raycast->ystep *= -1;
			
		stuff->raycast->next_vtouchx = stuff->raycast->xintercept;
		stuff->raycast->next_vtouchy = stuff->raycast->yintercept;
		
		if (stuff->raycast->left)
			bc_angle = 1;
		
		// increment xstep and ystep until we find a wall
		while (is_in_map(stuff->raycast->next_vtouchx, stuff->raycast->next_vtouchy, stuff->map_width, stuff->map_height))
		{
			if (has_wall_at(stuff->raycast->next_vtouchx - bc_angle, stuff->raycast->next_vtouchy, map, *stuff))
			{
				stuff->raycast->found_vhit = 1;
				stuff->raycast->vrt_wall_hitx = stuff->raycast->next_vtouchx;
				stuff->raycast->vrt_wall_hity = stuff->raycast->next_vtouchy;
				// my_mlx_pixel_put(img, stuff->raycast->vrt_wall_hitx, stuff->raycast->vrt_wall_hity, 0xFF4141);
				break;
			}
			else
			{
				stuff->raycast->next_vtouchx += stuff->raycast->xstep;
				stuff->raycast->next_vtouchy += stuff->raycast->ystep;
			}
		}
		bc_angle = 0;
		// chosse the smallest value bet vert and horz
		if (stuff->raycast->found_hhit)
			stuff->raycast->h_distance = distance_bet_points(stuff->px, stuff->py, stuff->raycast->hrz_wall_hitx, stuff->raycast->hrz_wall_hity);
		else
			stuff->raycast->h_distance = 99999999.9;
		if (stuff->raycast->found_vhit)
			stuff->raycast->v_distance = distance_bet_points(stuff->px, stuff->py, stuff->raycast->vrt_wall_hitx, stuff->raycast->vrt_wall_hity);
		else
			stuff->raycast->v_distance = 99999999.9;

		if (stuff->raycast->h_distance < stuff->raycast->v_distance)
		{
			stuff->raycast->wall_hitx = stuff->raycast->hrz_wall_hitx;
			stuff->raycast->wall_hity = stuff->raycast->hrz_wall_hity;
			stuff->raycast->distance = stuff->raycast->h_distance;
			stuff->raycast->tab_hrz_x[i] = stuff->raycast->hrz_wall_hitx;
			stuff->raycast->tab_hrz_y[i] = stuff->raycast->hrz_wall_hity;
		}
		else
		{
			stuff->raycast->wall_hitx = stuff->raycast->vrt_wall_hitx;
			stuff->raycast->wall_hity = stuff->raycast->vrt_wall_hity;
			stuff->raycast->distance = stuff->raycast->v_distance;
			stuff->raycast->was_hit_vrt[i] = 1;
			stuff->raycast->tab_hrz_x[i] = stuff->raycast->vrt_wall_hitx;
			stuff->raycast->tab_hrz_y[i] = stuff->raycast->vrt_wall_hity;
		}
		float j = 0;
		float x = stuff->px;
		float y = stuff->py;
		while (j < stuff->raycast->distance)
		{
			my_mlx_pixel_put(img, /*stuff->raycast->wall_hitx*/x, /*stuff.raycast->wall_hity*/y, 0xFF63EB);
			x += cos(ray_angle);
			y += sin(ray_angle);
			j++;
		}
		stuff->raycast->rays[i] = stuff->raycast->distance;
		stuff->raycast->rays_angle[i] = ray_angle;
		i++;
		column_id++;
		ray_angle += FOV_ANGLE / stuff->raycast->num_rays;
	}
}

void	render_3D(t_img *img, t_stuff *stuff, char **map, t_combo combo)
{
	(void)map;
	(void)img;
	int		i;
	float	ray;
	float	wallstrip_height;
	float	dist_project_plane;
	t_rect	rect;
	
	// clear the window with black, expect minimap
	int x = 0;
	int y = 0;
	while(y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (!(x < stuff->map_width && y < stuff->map_height))
			{
				if (y < WINDOW_HEIGHT / 2)
					my_mlx_pixel_put(img, x, y, 0x00002330);
				else
					my_mlx_pixel_put(img, x, y, 0x00103000);
			}
			x++;
		}
		y++;
	}
	
	i = 0;
	dist_project_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	while (i < stuff->raycast->num_rays)
	{
		ray = (stuff->raycast->rays[i] * cos(stuff->raycast->rays_angle[i] - stuff->pa));

		// projected wall height
		wallstrip_height = (TILE_SIZE / ray) * dist_project_plane;
		// if (wallstrip_height > WINDOW_HEIGHT)
		// 	wallstrip_height = WINDOW_HEIGHT;
		rect.x = i * WALL_STRIP;
		rect.y = (WINDOW_HEIGHT / 2) - (wallstrip_height / 2);
		rect.width = WALL_STRIP;
		rect.height = wallstrip_height;
		stuff->raycast->wallstrip_height = wallstrip_height;
		// printf("ray : %f\nx : %f\ny : %f\nwidth : %f\nheight : %f\n", ray, rect.x, rect.y, rect.width, rect.height);
		// my_mlx_pixel_put(img, rect.x, rect.y, 0x009CFF9F);
		// draw_rect(rect, 0x009CFF9F, img);
		
		draw_wall(img, stuff, combo.mlx->txt, i);
		
		i++;
	}
	free(stuff->raycast->rays_angle);
	free(stuff->raycast->rays);
}

void	init_txt(t_data *mlx, t_img *txt, char *path, t_combo *combo)
{
	txt->img = mlx_xpm_file_to_image(mlx->mlx, path, &txt->h, &txt->w);
	if (!txt->img)
		free_mlx(mlx, txt, combo->map, combo->stuff->line_count);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
	&txt->line_length, &txt->endian);
}

void	get_txt(t_data *mlx, t_combo *combo)
{
	init_txt(mlx, &mlx->txt.east, EAST, combo);
	init_txt(mlx, &mlx->txt.north, NORTH, combo);
	init_txt(mlx, &mlx->txt.west, WEST, combo);
	init_txt(mlx, &mlx->txt.south, SOUTH, combo);
}

void	mini_map(char **map, t_stuff stuff)
{
	t_data		mlx;
	t_combo		combo;
	t_img		img;
	t_raycast 	raycast;

	stuff.px = TILE_SIZE*(stuff.px) + TILE_SIZE/2;
	stuff.py = TILE_SIZE*(stuff.py) + TILE_SIZE/2;
	stuff.map_width = TILE_SIZE*stuff.line_len;
	stuff.map_height = TILE_SIZE*stuff.line_count;
	stuff.pdx = cos(stuff.pa)*5;
	stuff.pdy = sin(stuff.pa)*5;
	// printf("mw : %i\npy : %i\n", stuff.map_width, stuff.map_height);
	combo.map = map;
	combo.stuff = &stuff;
	combo.count = 0;
	ft_bzero(&raycast, sizeof(t_raycast));
	stuff.raycast = &raycast;
	ft_bzero(&mlx, sizeof(t_data));
	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		free_map(map, stuff.line_count);
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D lzaccome");
	combo.mlx = &mlx;
	img.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// draw_map()
	get_txt(&mlx, &combo);
	fill_grey(stuff.map_width, stuff.map_height, &img);
	build_walls(map, &img, &stuff);
	draw_player(&img, stuff);
	draw_rays(&img, &stuff, map);
	// int i = 0;
	// while (stuff.raycast->rays[i])
	// {
	// 	printf("ray : %f\n", stuff.raycast->rays[i]);
	// 	i++;
	// }
	render_3D(&img, &stuff, map, combo);
	combo.img = &img;
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 0L, &ft_cross, &combo);
	mlx_hook(mlx.win, 2, 1L << 0, direction, &combo);
	mlx_loop(mlx.mlx);
	return ;
}