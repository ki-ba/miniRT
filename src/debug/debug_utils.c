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

void	print_viewport(t_viewport vp)
{
	printf("VIEWPORT :\n");
	printf("lower_left: %f %f %f\n", vp.lower_left.x, vp.lower_left.y,vp.lower_left.z);
	printf("hrz: %f %f %f \n", vp.hrz.x, vp.hrz.y, vp.hrz.z);
	printf("vrt: %f %f %f \n", vp.vrt.x, vp.vrt.y, vp.vrt.z);
	printf("delta_u: %f %f %f\n", vp.delta_u.x, vp.delta_u.y, vp.delta_u.z);
	printf("delta_v: %f %f %f\n", vp.delta_v.x, vp.delta_v.y, vp.delta_v.z);
	printf("viewport width: %f\n", vp.vp_width);
	printf("viewport height: %f\n", vp.vp_height);
}

void	print_properties(t_mini_rt mini_rt)
{
	printf("AMBIENT LIGHT :\n");
	printf("intensity : %.2f\n", mini_rt.amb.i);
	print_color("color", mini_rt.amb.c);
	printf("\n\n");
	printf("CAMERA :\n");
	print_vec3("origin", mini_rt.cam.ori);
	print_vector("orientation", mini_rt.cam.dir);
	printf("fov : %f\n", mini_rt.cam.fov);
	printf("right vec: %f %f %f\n", mini_rt.cam.right.x, mini_rt.cam.right.y, mini_rt.cam.right.z);
	printf("up vec: %f %f %f\n", mini_rt.cam.up.x, mini_rt.cam.up.y, mini_rt.cam.up.z);
	print_viewport(mini_rt.cam.vp);
	printf("\n\n");
}
