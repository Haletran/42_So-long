/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:14:44 by codespace         #+#    #+#             */
/*   Updated: 2024/01/29 19:45:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[0][y] != '\n')
		if (map[0][y++] != '1')
			return (0);
	y = 0;
	while (map[x + 1] != NULL)
		x++;
	while (y < x)
		if (map[y++][0] != '1')
			return (0);
	y = 0;
	while (map[x] != NULL && map[x][y] != '\0')
		if (map[x][y++] != '1')
			return (0);
	x = 0;
	while (map[x] != NULL && map[x][y - 1] != '\0')
		if (map[x++][y - 1] != '1')
			return (0);
	return (1);
}

static int	check_if_rectangle(t_mlx *data)
{
	int	i;

	i = 0;
	data = get_co(data);
	while (data->map[i] != NULL)
		i++;
	if (i == data->height)
		return (0);
	return (1);
}

static int	check_p(char **map)
{
	int	x;
	int	value;
	int	value2;
	int	y;

	x = 0;
	value = 0;
	value2 = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (map[x][y] == 'P')
				value++;
			if (map[x][y] == 'E')
				value2++;
			y++;
		}
		x++;
	}
	if (value == 1 && value2 == 1)
		return (1);
	return (0);
}

static int	check_collectibles(char **map)
{
	int	x;
	int	value;
	int	y;

	x = 0;
	value = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\n' && map[x][y] != '\0')
		{
			if (map[x][y] == 'C')
				value++;
			if (isnotinset(map[x][y]))
				return (0);
			y++;
		}
		x++;
	}
	if (value == 0)
		return (0);
	return (1);
}

int	global_checker(t_mlx *data)
{
	data->map = initialize_map(data);
	cpy(data->map, &(data->tmp));
	if (data->map == NULL || !ft_strlen(*data->map))
		return (0);
	if (!check_if_rectangle(data))
		return (0);
	if (!check_collectibles(data->map))
		return (0);
	if (!check_walls(data->map))
		return (0);
	if (!check_p(data->map))
		return (0);
	if (!check_lines(data))
		return (0);
	data->exit_count = 0;
	data->coin_count = 0;
	flood_fill(data->tmp, data, data->player_x, data->player_y);
	if (data->exit_count == 0 || data->coin_count == 0)
		return (0);
	return (1);
}
