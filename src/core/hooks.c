/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:39:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 15:52:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"
#include "core.h"

/**
	* @brief Handles keypress events.
* @param keysym The key symbol of the pressed key.
* @param mini_rt Pointer to the miniRT structure.
* @return 0 on success.
* @note Exits the program if the Escape 65307 key / q 113 key is pressed.
*/
int	handle_keypress(int keysym, t_mini_rt *mini_rt)
{
	double step = 0.5;
	if (keysym == 65307 || keysym == 113)
		clean_exit(mini_rt, SUCCESS);
	else if (keysym == 119)
		mini_rt->camera.origin.y += step;
	else if (keysym == 115)
		mini_rt->camera.origin.y -= step;
	else if (keysym == 100)
		mini_rt->camera.origin.x -= step;
	else if (keysym == 97)
		mini_rt->camera.origin.x += step;
	else if (keysym == 65362)
		mini_rt->camera.origin.z += step;
	else if (keysym == 65364)
		mini_rt->camera.origin.z -= step;
	else if (keysym == 114)
	{
		mini_rt->camera.origin.x = 0;
		mini_rt->camera.origin.y = 0;
		mini_rt->camera.origin.z = 0;
	}
	// printf("Key pressed: %d\n", keysym);
	// printf("Camera position: x=%f, y=%f, z=%f\n", mini_rt->camera.origin.x, mini_rt->camera.origin.y, mini_rt->camera.origin.z);
	shoot_rays(mini_rt);
	return (0);
}

int	handle_window_close(t_mini_rt *mini_rt)
{
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
