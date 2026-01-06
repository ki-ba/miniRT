/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/22 19:25:34 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

int	render_scene(t_mini_rt *mini_rt)
{
	if (!mini_rt)
		return (1);
	trace_rays(mini_rt);
	if (!mini_rt->rays)
		return (1);

	return (0);
}
