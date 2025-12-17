/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:52:34 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:52:52 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "miniRT.h"

void	destroy_mini_rt(t_mini_rt *mini_rt);
void	init_mini_rt(t_mini_rt *mini_rt);
void	print_mini_rt(t_mini_rt mini_rt);
void	clean_exit(t_mini_rt *mini_rt, int exit_code);

#endif
