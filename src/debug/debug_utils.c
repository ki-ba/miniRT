/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:22:56 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:48:28 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_binary(int const n)
{
	uint8_t	i;

	i = 8;
	while (--i ^ 0xFF)
		printf("%c", ((n >> i) & 1) + '0');
}

void	print_color(char *name, t_color color)
{
	printf("%s: (%d, %d, %d)\n", name, color.r, color.g, color.b);
}

void	print_vec3(char *name, t_vec3 vector)
{
	printf("%s: [%.2f, %.2f, %.2f]\n", name, vector.x, vector.y, vector.z);
}

void	print_viewport(t_viewport vp)
{
	printf("VIEWPORT :\n");
	printf("ori: %f %f %f\n", vp.ori.x, vp.ori.y, vp.ori.z);
	printf("hrz: %f %f %f \n", vp.hrz.x, vp.hrz.y, vp.hrz.z);
	printf("vrt: %f %f %f \n", vp.vrt.x, vp.vrt.y, vp.vrt.z);
	printf("delta_h: %f\n", vp.delta_h);
	printf("delta_v: %f\n", vp.delta_v);
	printf("viewport width: %f\n", vp.width);
	printf("viewport height: %f\n", vp.height);
}

void	print_camera(t_camera cam)
{
	printf("CAMERA :\n");
	print_vec3("origin", cam.ori);
	print_vec3("orientation", cam.dir);
	printf("fov : %f\n", cam.fov);
	printf("right vec: %f %f %f\n", cam.right.x, cam.right.y, cam.right.z);
	printf("up vec: %f %f %f\n\n", cam.up.x, cam.up.y, cam.up.z);
}

void	print_properties(t_mini_rt mini_rt)
{
	printf("AMBIENT LIGHT :\n");
	printf("intensity : %.2f\n", mini_rt.scene.amb.i);
	print_color("color", mini_rt.scene.amb.c);
	printf("\n\n");
	printf("intensity : %.2f\n", mini_rt.scene.amb.i);
	print_color("color", mini_rt.scene.amb.c);
	print_camera(mini_rt.scene.cam);
	print_viewport(mini_rt.scene.cam.vp);
	printf("\n\n");
}
