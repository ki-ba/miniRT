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

void	print_point(char *name, t_point point)
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
	printf("intensity : %.2f\n", mini_rt.ambient_light.intensity);
	print_color("color", mini_rt.ambient_light.color);
	printf("\n\n");
	printf("CAMERA :\n");
	print_point("origin", mini_rt.camera.origin);
	print_vector("orientation", mini_rt.camera.dir);
	printf("fov : %f\n", mini_rt.camera.fov);
	printf("right vec: %f %f %f\n", mini_rt.camera.right.x, mini_rt.camera.right.y, mini_rt.camera.right.z);
	printf("up vec: %f %f %f\n", mini_rt.camera.up.x, mini_rt.camera.up.y, mini_rt.camera.up.z);
	printf("viewport width: %f\n", mini_rt.camera.vp_width);
	printf("viewport height: %f\n", mini_rt.camera.vp_height);
	printf("\n\n");
}
