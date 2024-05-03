/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:25:12 by codespace         #+#    #+#             */
/*   Updated: 2024/01/29 15:49:52 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	key_hook(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 4 || key == 80)
		move_left(mlx);
	if (key == 22 || key == 81)
		move_down(mlx);
	if (key == 26 || key == 82)
		move_up(mlx);
	if (key == 7 || key == 79)
		move_right(mlx);
	return (0);
}

int	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
	return (0);
}

void	ft_free(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->map[i])
		free(mlx->map[i++]);
	i = 0;
	while (mlx->tmp[i])
		free(mlx->tmp[i++]);
	free(mlx->map);
	free(mlx->tmp);
	free(mlx);
}

void	rendering(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->height * 32, mlx->width * 32,
			"So_long");
	get_var(mlx);
	render_map(mlx);
	mlx_set_fps_goal(mlx->mlx, 60);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_hook, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, mlx->wall);
	mlx_destroy_image(mlx->mlx, mlx->ground);
	mlx_destroy_image(mlx->mlx, mlx->player);
	mlx_destroy_image(mlx->mlx, mlx->player_flip);
	mlx_destroy_image(mlx->mlx, mlx->enemy);
	mlx_destroy_image(mlx->mlx, mlx->player_back);
	mlx_destroy_image(mlx->mlx, mlx->player_front);
	mlx_destroy_image(mlx->mlx, mlx->coin);
	mlx_destroy_image(mlx->mlx, mlx->exit);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	close(mlx->fd);
	ft_free(mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2 || argc > 3)
		return (ft_error(2));
	mlx = malloc(sizeof(t_mlx));
	mlx->fd = open(argv[1], O_RDONLY);
	mlx->fd_tmp = open(argv[1], O_RDONLY);
	if (mlx->fd < 0 || !check_file(argv[1]))
	{
		free(mlx);
		return (ft_error(1));
	}
	if (!global_checker(mlx))
	{
		ft_free(mlx);
		return (ft_error(3));
	}
	rendering(mlx);
}
