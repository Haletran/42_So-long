/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:03:50 by bapasqui          #+#    #+#             */
/*   Updated: 2024/01/24 16:32:24 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_var(t_mlx *data)
{
	int	height;
	int	width;

	data->nb_move = 1;
	mlx_set_font_scale(data->mlx, data->win, "default", 20);
	data->wall = mlx_png_file_to_image(data->mlx, "images/test.png", &height,
			&width);
	data->ground = mlx_png_file_to_image(data->mlx, "images/black.png", &height,
			&width);
	data->exit = mlx_png_file_to_image(data->mlx, "images/exit.png", &height,
			&width);
	data->player = mlx_png_file_to_image(data->mlx, "images/player3.png",
			&height, &width);
	data->coin = mlx_png_file_to_image(data->mlx, "images/coin4.png", &height,
			&width);
	data->player_flip = mlx_png_file_to_image(data->mlx,
			"images/playerflip.png", &height, &width);
	data->player_front = mlx_png_file_to_image(data->mlx,
			"images/player_front.png", &height, &width);
	data->player_back = mlx_png_file_to_image(data->mlx,
			"images/player_back.png", &height, &width);
	data->enemy = mlx_png_file_to_image(data->mlx, "images/enemy.png", &height,
			&width);
}

void	render_enemy(t_mlx *data)
{
	data->x = 0;
	data->y = 0;
	mlx_string_put(data->mlx, data->win, 10, 28, 0xFFFFFFFF, "0");
	while (data->map[data->x] != NULL)
	{
		while (data->map[data->x][data->y] != '\0')
		{
			if (data->map[data->x][data->y] == 'Y')
				mlx_put_image_to_window(data->mlx, data->win, data->enemy,
					data->y * 32, data->x * 32);
			data->y++;
		}
		data->y = 0;
		data->x++;
	}
}

void	render_map(t_mlx *data)
{
	data->x = 0;
	data->y = 0;
	while (data->map[data->x] != NULL)
	{
		while (data->map[data->x][data->y] != '\0')
		{
			if (data->map[data->x][data->y] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall,
					data->y * 32, data->x * 32);
			else if (data->map[data->x][data->y] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->ground,
					data->y * 32, data->x * 32);
			else if (data->map[data->x][data->y] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->coin,
					data->y * 32, data->x * 32);
			else if (data->map[data->x][data->y] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player,
					data->player_y * 32, data->player_x * 32);
			data->y++;
		}
		data->y = 0;
		data->x++;
	}
	render_enemy(data);
}
