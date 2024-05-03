/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:47:37 by baptiste          #+#    #+#             */
/*   Updated: 2024/01/29 19:44:21 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_mlx	*get_map_size(t_mlx *data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (data->map[x] != NULL)
		x++;
	data->width = x;
	x = 0;
	while (data->map[x][y] != '\0' && data->map[x][y] != '\n')
		y++;
	data->height = y;
	return (data);
}

t_mlx	*get_co(t_mlx *data)
{
	data->x = 0;
	data->y = 0;
	get_map_size(data);
	while (data->map[data->x] != NULL)
	{
		while (data->map[data->x][data->y] != '\0')
		{
			if (data->map[data->x][data->y] == 'E')
			{
				data->end_x = data->x;
				data->end_y = data->y;
			}
			if (data->map[data->x][data->y] == 'P')
			{
				data->player_x = data->x;
				data->player_y = data->y;
			}
			if (data->map[data->x][data->y] == 'C')
				data->coins++;
			data->y++;
		}
		data->y = 0;
		data->x++;
	}
	return (data);
}

void	ft_end(t_mlx *data, int value)
{
	if (value == 1)
	{
		mlx_loop_end(data->mlx);
		ft_printf("[ \033[1m\033[32mSUCCESS\033[0m ]\n");
	}
	else if (value == 2)
	{
		mlx_loop_end(data->mlx);
		ft_printf("[ \033[1m\033[31mGAME OVER\033[0m ]\n");
	}
}

char	**cpy(char **src, char ***dest)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (src[len] != NULL)
		len++;
	*dest = malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (src[i] != NULL)
	{
		(*dest)[i] = strdup(src[i]);
		i++;
	}
	(*dest)[i] = NULL;
	return (*dest);
}
