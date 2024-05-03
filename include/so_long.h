/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:25:27 by codespace         #+#    #+#             */
/*   Updated: 2024/01/29 19:46:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../MacroLibX/includes/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	**map;
	char	**tmp;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		end_x;
	int		end_y;
	int		fd;
	int		fd_tmp;
	void	*ground;
	void	*wall;
	void	*player;
	void	*exit;
	void	*coin;
	void	*player_flip;
	void	*player_front;
	void	*player_back;
	void	*enemy;
	int		nb_move;
	int		coins;
	int		nb_coin;
	int		x;
	int		y;
	int		exit_count;
	int		coin_count;
}			t_mlx;

/* FUNCTIONS */
void		render_map(t_mlx *data);
int			store(t_mlx *data);
int			check_file(char *filename);
char		*ft_strstr(char *str, char *to_find);
char		**initialize_map(t_mlx *data);
int			ft_strcmp(char *s1, char *s2);
int			global_checker(t_mlx *data);
int			ft_error(int choice);
int			isnotinset(char c);
t_mlx		*get_co(t_mlx *data);
void		move_up(t_mlx *data);
void		get_var(t_mlx *data);
void		move_down(t_mlx *data);
void		move_right(t_mlx *data);
void		move_left(t_mlx *data);
void		ft_free(t_mlx *mlx);
void		flood_fill(char **map_tmp, t_mlx *data, int x, int y);
t_mlx		*get_map_size(t_mlx *data);
char		**initialize_map_tmp(t_mlx *data);
char		**cpy(char **src, char ***dest);
void		ft_end(t_mlx *mlx, int value);
int			check_lines(t_mlx *data);

#endif
