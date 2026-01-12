/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:22 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:43:50 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "miniRT.h"

int	handle_keypress(int keysym, t_mini_rt *mini_rt);
int	handle_mouse(int mouse_event, t_mini_rt	*mini_rt);
int	mouse_move(int x, int y, t_mini_rt *mini_rt);
int	handle_window_close(t_mini_rt *mini_rt);

#endif
