/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:39:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 11:52:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"
#include "core.h"

static int handle_move_keypress(int keysym, void *param)
{
	t_mini_rt *mini_rt;

	mini_rt = (t_mini_rt *)param;
	if (keysym == 119)
		mini_rt->cam.ori.y += MOVE_STEP;
	else if (keysym == 115)
		mini_rt->cam.ori.y -= MOVE_STEP;
	else if (keysym == 100)
		mini_rt->cam.ori.x -= MOVE_STEP;
	else if (keysym == 97)
		mini_rt->cam.ori.x += MOVE_STEP;
	else if (keysym == 65362)
		mini_rt->cam.ori.z += MOVE_STEP;
	else if (keysym == 65364)
		mini_rt->cam.ori.z -= MOVE_STEP;
	else if (keysym == 114)
	{
		mini_rt->cam.ori.x = 0;
		mini_rt->cam.ori.y = 0;
		mini_rt->cam.ori.z = 0;
	}
	return (0);
}

/**
	* @brief Handles keypress events.
* @param keysym The key symbol of the pressed key.
* @param mini_rt Pointer to the miniRT structure.
* @return 0 on success.
* @note Exits the program if the Escape 65307 key / q 113 key is pressed.
*/
int	handle_keypress(int keysym, void *param)
{
	t_mini_rt *mini_rt;

	mini_rt = (t_mini_rt *)param;
	// printf("Key pressed: %d\n", keysym);
	if (keysym == 65307 || keysym == 113)
		clean_exit(mini_rt, SUCCESS);
	else if (keysym == 32)
	{
		if (mini_rt->scale == 1)
			mini_rt->scale = 8;
		else
			mini_rt->scale = 1;
	}
	else if (mini_rt->scale == 8)
		handle_move_keypress(keysym, param);
	else
		return (0);
	shoot_rays(mini_rt);
	return (0);
}

int	handle_window_close(void *param)
{
	t_mini_rt *mini_rt;

	mini_rt = (t_mini_rt *)param;
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
