/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:22 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/16 19:18:32 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

// SETTINGS
# define SENSIVITY	 	0.02
# define MIN_FOV_DEG 	0
# define MAX_FOV_DEG 	180

// KEYSYMS
# define ESCAPE			65307

// CONTROLS
// moves
# define K_FORWARD		'w'
# define K_BACKWARD		's'
# define K_LEFT 		'a'
# define K_RIGHT 		'd'
# define K_UP			'c'
# define K_DOWN			'z'
# define K_RESET		'x'

// modes
# define K_RENDER		'r'
# define K_OBJ			'o'

typedef struct 	s_mini_rt	t_mini_rt;
typedef struct 	s_hooks	t_hooks;
typedef enum	e_bool	t_bool;

enum	e_mlx_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum	e_hooks_mode
{
	RENDER,
	OBJ,
	HOOKS_MODE_QTY,
	
};

struct	s_hooks
{
	unsigned int v: HOOKS_MODE_QTY;
};

int		handle_keypress(int keysym, t_mini_rt *mini_rt);
int		handle_mouse_scroll(int mouse_event, int x, int y, t_mini_rt	*mini_rt);
int		handle_mouse_move(int x, int y, t_mini_rt *mini_rt);
int		handle_window_close(t_mini_rt *mini_rt);
t_bool is_set_bit(unsigned int v, unsigned int flag);

#endif
