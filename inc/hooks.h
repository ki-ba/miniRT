/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:22 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/23 14:58:46 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

typedef struct s_vec3	t_vec3;

// SETTINGS
# define SENSIVITY	 	0.002
# define DEADZONE	 	0.1
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

typedef struct s_mini_rt	t_mini_rt;
typedef struct s_hooks		t_hooks;
typedef enum e_bool			t_bool;

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

void					handle_hook_mode(t_mini_rt *mrt, int keysym);
int						handle_keypress(int keysym, void *param);
int						handle_window_close(void *param);
int						handle_mouse_scroll(int mouse_event, int x, int y, void *param);
void					lock_mouse(t_mini_rt *mrt, t_vec3 *pos, int x, int y);
int						handle_mouse_move(int x, int y, void *param);
t_bool					is_set_bit(unsigned int v, unsigned int flag);

#endif
