/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:14:23 by lzaccome          #+#    #+#             */
/*   Updated: 2022/06/30 05:12:43 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// float	x;
	// float	y;
	// (void)img;

	// x = stuff.px;
	// y = stuff.py;
	// stuff.raycast.ra = stuff.pa;
	// while (stuff.raycast.r < 1)
	// {

	// 	stuff.raycast.dof = 0;
	// 	aTan = -1 / tan(stuff.raycast.ra);
	// 	if (stuff.raycast.ra > PI)
	// 	{
	// 		stuff.raycast.ry = (((int)stuff.py>>6)<<6) -0.0001;
	// 		stuff.raycast.rx = (stuff.py - stuff.raycast.ry) * aTan + stuff.px;
	// 		stuff.raycast.yo = -64;
	// 		stuff.raycast.xo = -stuff.raycast.yo * aTan;
	// 	}
	// 	if (stuff.raycast.ra < PI)
	// 	{
	// 		stuff.raycast.ry = (((int)stuff.py>>6)<<6) +64;
	// 		stuff.raycast.rx = (stuff.py - stuff.raycast.ry) * aTan + stuff.px;
	// 		stuff.raycast.yo = 64;
	// 		stuff.raycast.xo = -stuff.raycast.yo * aTan;
	// 	}
	// 	if (stuff.raycast.ra == 0 || stuff.raycast.ra == PI)
	// 	{
	// 		stuff.raycast.rx = stuff.px;
	// 		stuff.raycast.ry = stuff.py;
	// 		stuff.raycast.dof = 8;
	// 	}
	// 	while (stuff.raycast.dof < 8)
	// 	{
	// 		stuff.raycast.mx = (int)(stuff.raycast.rx) >> 6;
	// 		stuff.raycast.my = (int)(stuff.raycast.ry) >> 6;
	// 		printf("mx : %i\n", stuff.raycast.mx);
	// 		printf("my : %i\n", stuff.raycast.my);
	// 		if (stuff.raycast.my < stuff.line_count && stuff.raycast.mx < stuff.line_len && stuff.raycast.my > 0 && stuff.raycast.mx > 0 && map[stuff.raycast.my][stuff.raycast.mx] == 1)
	// 			stuff.raycast.dof = 8;
	// 		else
	// 		{
	// 			stuff.raycast.rx += stuff.raycast.xo;
	// 			stuff.raycast.ry += stuff.raycast.yo;
	// 			stuff.raycast.dof += 1;
	// 		}
	// 	}
	// 	x = stuff.px;
	// 	y = stuff.py;
	// 	while ((int)x != (int)stuff.raycast.rx && (int)y != (int)stuff.raycast.ry)
	// 	{
	// 		x += stuff.pdx;
	// 		y += stuff.pdy;
	// 		printf("x : %f\nrx : %f\n", x, stuff.raycast.rx);
	// 		printf("y : %f\nry : %f\n", y, stuff.raycast.ry);
	// 		if ((x > 0 && x < stuff.map_width) && (y > 0 && y < stuff.map_height))
	// 			my_mlx_pixel_put(img, x, y, 0x00FF4141);
	// 		else
	// 			break;
	// 	}
	// 	stuff.raycast.r++;
	// }

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
	int x;
	int y;

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
	while (i < 50)
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

void	draw_rays(t_img *img, t_stuff stuff, char **map)
{
	//////////////////////////////////////
	// HORIONTAL RAY-GRID INTERSECTIONS
	//////////////////////////////////////
	int		i;
	int		num_rays;
	int		column_id;
	float	ray_angle;
	int		bc_angle;

	i = 0;
	num_rays = stuff.map_width;
	column_id = 0;
	ray_angle = stuff.pa - (FOV_ANGLE / 2);
	while (i < num_rays)
	{
		bc_angle = 0;
		stuff.raycast.found_vhit = 0;
		stuff.raycast.found_hhit = 0;
		stuff.raycast.was_hit_vrt = 0;
		if (ray_angle < 0)
			ray_angle += 2*PI;
		if (ray_angle > 2*PI)
		ray_angle -= 2*PI;
		check_direction(&stuff.raycast, ray_angle);
		// y-coord of the closest horizontal grid intersection
		stuff.raycast.yintercept = (floor(stuff.py / TILE_SIZE) * TILE_SIZE);
		if (stuff.raycast.down)
			stuff.raycast.yintercept += TILE_SIZE;
			
		// x-coord of the cosst horizontal grid intersection
		stuff.raycast.xintercept = stuff.px + (stuff.raycast.yintercept - stuff.py) / tan(ray_angle);
		
		// calculate increment xstep step
		stuff.raycast.ystep = TILE_SIZE;
		if (stuff.raycast.up)
			stuff.raycast.ystep *= -1;
			
		stuff.raycast.xstep = TILE_SIZE / tan(ray_angle);
		if (stuff.raycast.left && stuff.raycast.xstep > 0)
			stuff.raycast.xstep *= -1;
		if (stuff.raycast.right && stuff.raycast.xstep < 0)
			stuff.raycast.xstep *= -1;
			
		stuff.raycast.next_htouchx = stuff.raycast.xintercept;
		stuff.raycast.next_htouchy = stuff.raycast.yintercept;
		
		if (stuff.raycast.up)
			bc_angle = 1;
		
		// increment xstep and ystep until we find a wall
		while (is_in_map(stuff.raycast.next_htouchx, stuff.raycast.next_htouchy, stuff.map_width, stuff.map_height))
		{
			if (has_wall_at(stuff.raycast.next_htouchx, stuff.raycast.next_htouchy - bc_angle, map, stuff))
			{
				stuff.raycast.found_hhit = 1;
				stuff.raycast.hrz_wall_hitx = stuff.raycast.next_htouchx;
				stuff.raycast.hrz_wall_hity = stuff.raycast.next_htouchy;
				// my_mlx_pixel_put(img, stuff.raycast.hrz_wall_hitx, stuff.raycast.hrz_wall_hity, 0xFF4141);
				break;
			}
			else
			{
				stuff.raycast.next_htouchx += stuff.raycast.xstep;
				stuff.raycast.next_htouchy += stuff.raycast.ystep;
			}
		}
		bc_angle = 0;
		//////////////////////////////////////
		// VERTICAL RAY-GRID INTERSECTIONS
		//////////////////////////////////////

		// check_direction(&stuff.raycast, ray_angle);
		// x-coord of the closest vertical grid intersection
		stuff.raycast.xintercept = (floor(stuff.px / TILE_SIZE) * TILE_SIZE);
		if (stuff.raycast.right)
			stuff.raycast.xintercept += TILE_SIZE;
			
		// y-coord of the cosst vertical grid intersection
		stuff.raycast.yintercept = stuff.py + (stuff.raycast.xintercept - stuff.px) * tan(ray_angle);
		
		// calculate increment xstep step
		stuff.raycast.xstep = TILE_SIZE;
		if (stuff.raycast.left)
			stuff.raycast.xstep *= -1;
			
		stuff.raycast.ystep = TILE_SIZE * tan(ray_angle);
		if (stuff.raycast.up && stuff.raycast.ystep > 0)
			stuff.raycast.ystep *= -1;
		if (stuff.raycast.down && stuff.raycast.ystep < 0)
			stuff.raycast.ystep *= -1;
			
		stuff.raycast.next_vtouchx = stuff.raycast.xintercept;
		stuff.raycast.next_vtouchy = stuff.raycast.yintercept;
		
		if (stuff.raycast.left)
			bc_angle = 1;
		
		// increment xstep and ystep until we find a wall
		while (is_in_map(stuff.raycast.next_vtouchx, stuff.raycast.next_vtouchy, stuff.map_width, stuff.map_height))
		{
			if (has_wall_at(stuff.raycast.next_vtouchx - bc_angle, stuff.raycast.next_vtouchy, map, stuff))
			{
				stuff.raycast.found_vhit = 1;
				stuff.raycast.vrt_wall_hitx = stuff.raycast.next_vtouchx;
				stuff.raycast.vrt_wall_hity = stuff.raycast.next_vtouchy;
				// my_mlx_pixel_put(img, stuff.raycast.vrt_wall_hitx, stuff.raycast.vrt_wall_hity, 0xFF4141);
				break;
			}
			else
			{
				stuff.raycast.next_vtouchx += stuff.raycast.xstep;
				stuff.raycast.next_vtouchy += stuff.raycast.ystep;
			}
		}
		bc_angle = 0;
		// chosse the smallest value bet vert and horz
		if (stuff.raycast.found_hhit)
			stuff.raycast.h_distance = distance_bet_points(stuff.px, stuff.py, stuff.raycast.hrz_wall_hitx, stuff.raycast.hrz_wall_hity);
		else
			stuff.raycast.h_distance = 99999999.9;
		if (stuff.raycast.found_vhit)
			stuff.raycast.v_distance = distance_bet_points(stuff.px, stuff.py, stuff.raycast.vrt_wall_hitx, stuff.raycast.vrt_wall_hity);
		else
			stuff.raycast.v_distance = 99999999.9;

		if (stuff.raycast.h_distance < stuff.raycast.v_distance)
		{
			stuff.raycast.wall_hitx = stuff.raycast.hrz_wall_hitx;
			stuff.raycast.wall_hity = stuff.raycast.hrz_wall_hity;
			stuff.raycast.distance = stuff.raycast.h_distance;
		}
		else
		{
			stuff.raycast.wall_hitx = stuff.raycast.vrt_wall_hitx;
			stuff.raycast.wall_hity = stuff.raycast.vrt_wall_hity;
			stuff.raycast.distance = stuff.raycast.v_distance;
			stuff.raycast.was_hit_vrt = 1;
		}
		float j = 0;
		float x = stuff.px;
		float y = stuff.py;
		while (j < stuff.raycast.distance)
		{
			my_mlx_pixel_put(img, /*stuff.raycast.wall_hitx*/x, /*stuff.raycast.wall_hity*/y, 0xFF63EB);
			x += cos(ray_angle);
			y += sin(ray_angle);
			j++;
		}
		i++;
		column_id++;
		ray_angle += FOV_ANGLE / num_rays;
	}
}

void	mini_map(char **map, t_stuff stuff)
{
	t_data	mlx;
	t_combo	combo;
	t_img	img;

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
	ft_bzero(&mlx, sizeof(t_data));
	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		free_map(map, stuff.line_count);
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.mlx, stuff.map_width, stuff.map_height, "Mini Map");
	combo.mlx = &mlx;
	img.img = mlx_new_image(mlx.mlx, stuff.map_width, stuff.map_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// draw_map()
	fill_grey(stuff.map_width, stuff.map_height, &img);
	build_walls(map, &img, &stuff);
	draw_player(&img, stuff);
	draw_rays(&img, stuff, map);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// my_mlx_pixel_put(&img, 7, 7, 0x00FF0000);
	combo.img = &img;
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 0L, &ft_cross, &combo);
	mlx_hook(mlx.win, 2, 1L << 0, direction, &combo);
	mlx_loop(mlx.mlx);
	return ;
}