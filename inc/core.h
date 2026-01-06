/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:52:34 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/05 13:48:08 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "miniRT.h"

typedef struct s_roots
{
	double	root1;
	double	root2;
	double	delta;
}			t_roots;

void	destroy_mini_rt(t_mini_rt *mini_rt);
void	init_mini_rt(t_mini_rt *mini_rt);
void	print_mini_rt(t_mini_rt mini_rt);
void	clean_exit(t_mini_rt *mini_rt, int exit_code);

// MATH

t_roots	*resolve_eq2(double a, double b, double c);
double	get_solution(double a, double b, double c);
t_point	vec_to_point(t_ray ray, double t);
#endif
