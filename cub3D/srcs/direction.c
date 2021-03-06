/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 01:01:14 by lzaccome          #+#    #+#             */
/*   Updated: 2022/07/10 16:54:29 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	direction(int keycode, t_combo *combo)
{
	if (keycode == 65307)
		free_mlx(combo->mlx, combo->img, combo->map, combo->stuff->line_count);
	else if (keycode == 65363)
		move_right(combo);
	else if (keycode == 100)
		move_to_right(combo);
	else if (keycode == 119 || keycode == 65362)
		move_up(combo);
	else if (keycode == 65361)
		move_left(combo);
	else if (keycode == 97)
		move_to_left(combo);
	else if (keycode == 115 || keycode == 65364)
		move_down(combo);
	return (0);
}

void	move_right(t_combo *combo)
{
	combo->stuff->pa += 0.1;
	if (combo->stuff->pa > 2*PI)
		combo->stuff->pa -= 2*PI;
	combo->stuff->pdx=cos(combo->stuff->pa)*5;
	combo->stuff->pdy=sin(combo->stuff->pa)*5;
	// printf("%f\n", combo->stuff->pa);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}

void	move_up(t_combo *combo)
{
	combo->stuff->pdx=cos(combo->stuff->pa)*5;
	combo->stuff->pdy=sin(combo->stuff->pa)*5;
	if (!(has_wall_at(combo->stuff->px + combo->stuff->pdx, combo->stuff->py, combo->map, *combo->stuff)
		|| has_wall_at(combo->stuff->px, combo->stuff->py + combo->stuff->pdy, combo->map, *combo->stuff)))
	{
		combo->stuff->px += combo->stuff->pdx;
		combo->stuff->py += combo->stuff->pdy;
	}
	// printf("%f\n", combo->stuff->px);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}

void	move_left(t_combo *combo)
{
	combo->stuff->pa -= 0.1;
	if (combo->stuff->pa < 0)
		combo->stuff->pa += 2*PI;
	combo->stuff->pdx=cos(combo->stuff->pa)*5;
	combo->stuff->pdy=sin(combo->stuff->pa)*5;
	// printf("%f\n", combo->stuff->pa);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}

void	move_down(t_combo *combo)
{
	combo->stuff->pdx=cos(combo->stuff->pa)*5;
	combo->stuff->pdy=sin(combo->stuff->pa)*5;
	if (!(has_wall_at(combo->stuff->px - combo->stuff->pdx, combo->stuff->py, combo->map, *combo->stuff)
	|| has_wall_at(combo->stuff->px, combo->stuff->py - combo->stuff->pdy, combo->map, *combo->stuff)))
	{
		combo->stuff->px -= combo->stuff->pdx;
		combo->stuff->py -= combo->stuff->pdy;
	}
	// printf("%f\n", combo->stuff->px);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}

void	move_to_right(t_combo *combo)
{
	combo->stuff->pdx=cos((combo->stuff->pa + (PI / 2)))*5;
	combo->stuff->pdy=sin((combo->stuff->pa + (PI / 2)))*5;
	if (!(has_wall_at(combo->stuff->px + combo->stuff->pdx, combo->stuff->py, combo->map, *combo->stuff)
		|| has_wall_at(combo->stuff->px, combo->stuff->py + combo->stuff->pdy, combo->map, *combo->stuff)))
	{
		combo->stuff->px += combo->stuff->pdx;
		combo->stuff->py += combo->stuff->pdy;
	}
	// printf("%f\n", combo->stuff->pa);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}

void	move_to_left(t_combo *combo)
{
	combo->stuff->pdx=cos((combo->stuff->pa - (PI / 2)))*5;
	combo->stuff->pdy=sin((combo->stuff->pa - (PI / 2)))*5;
	if (!(has_wall_at(combo->stuff->px + combo->stuff->pdx, combo->stuff->py, combo->map, *combo->stuff)
		|| has_wall_at(combo->stuff->px, combo->stuff->py + combo->stuff->pdy, combo->map, *combo->stuff)))
	{
		combo->stuff->px += combo->stuff->pdx;
		combo->stuff->py += combo->stuff->pdy;
	}
	// printf("%f\n", combo->stuff->pa);
	// draw_map(*(combo->stuff), combo->img);
	fill_grey(combo->stuff->map_width, combo->stuff->map_height, combo->img);
	build_walls(combo->map, combo->img, combo->stuff);
	draw_player(combo->img, *(combo->stuff));
	draw_rays(combo->img, combo->stuff, combo->map);
	render_3D(combo->img, combo->stuff, combo->map, *combo);
	mlx_put_image_to_window(combo->mlx->mlx, combo->mlx->win, combo->img->img, 0, 0);
	return ;
}