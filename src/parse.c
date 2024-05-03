/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:17:34 by bapasqui          #+#    #+#             */
/*   Updated: 2024/01/29 19:50:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	find_size(t_mlx *data)
{
	int		i;
	int		len;
	char	*test;

	i = 0;
	len = 0;
	while (1)
	{
		test = get_next_line(data->fd_tmp);
		if (!test)
		{
			free(test);
			break ;
		}
		len += ft_strlen(test);
		free(test);
		i++;
	}
	close(data->fd_tmp);
	return (len);
}

int	check_lines(t_mlx *data)
{
	int	x;
	int	tmp;
	int	y;

	x = 0;
	tmp = 0;
	while (data->map[x] != NULL)
	{
		y = 0;
		while (data->map[x][y] != '\n' && data->map[x][y] != '\0')
			y++;
		if (y != data->height)
			return (0);
		x++;
	}
	return (1);
}

char	**initialize_map(t_mlx *data)
{
	int	i;

	i = 0;
	data->map = malloc(find_size(data) * sizeof(char *));
	if (!data->map)
	{
		ft_free(data);
		return (NULL);
	}
	while (1)
	{
		data->map[i] = get_next_line(data->fd);
		if (!data->map[i])
			break ;
		i++;
	}
	close(data->fd);
	return (data->map);
}

void	flood_fill(char **map_tmp, t_mlx *data, int x, int y)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height
		|| map_tmp[x][y] == '1' || map_tmp[x][y] == 'S')
		return ;
	if (map_tmp[x][y] == 'C')
		data->coin_count++;
	else if (map_tmp[x][y] == 'E')
		data->exit_count++;
	map_tmp[x][y] = 'S';
	flood_fill(map_tmp, data, x + 1, y);
	flood_fill(map_tmp, data, x - 1, y);
	flood_fill(map_tmp, data, x, y + 1);
	flood_fill(map_tmp, data, x, y - 1);
}
