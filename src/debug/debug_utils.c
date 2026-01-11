/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:22:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:27:06 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_vec3(char *name, t_vec3 point)
{
	printf("%s: [%.2f, %.2f, %.2f]\n", name, point.x, point.y, point.z);
}

void	print_color(char *name, t_color color)
{
	printf("%s: (%d, %d, %d)\n", name, color.r, color.g, color.b);
}

void	print_vector(char *name, t_vec3 vector)
{
	printf("%s: [%.2f, %.2f, %.2f]\n", name, vector.x, vector.y, vector.z);
}

void	print_properties(t_mini_rt mini_rt)
{
	printf("AMBIENT LIGHT :\n");
	printf("intensity : %.2f\n", mini_rt.amb.intensity);
	print_color("color", mini_rt.amb.color);
	printf("\n\n");
	printf("CAMERA :\n");
	print_vec3("origin", mini_rt.cam.origin);
	print_vector("orientation", mini_rt.cam.dir);
	printf("fov : %f\n", mini_rt.cam.fov);
	printf("right vec: %f %f %f\n", mini_rt.cam.right.x, mini_rt.cam.right.y, mini_rt.cam.right.z);
	printf("up vec: %f %f %f\n", mini_rt.cam.up.x, mini_rt.cam.up.y, mini_rt.cam.up.z);
	printf("viewport width: %f\n", mini_rt.cam.vp_width);
	printf("viewport height: %f\n", mini_rt.cam.vp_height);
	printf("\n\n");
}
