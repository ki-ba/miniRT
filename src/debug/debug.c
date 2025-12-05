/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:35:49 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/05 18:25:53 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

void	print_properties(t_miniRT mini_rt)
{
	printf("AMBIANT LIGHT :\n");
	printf("intensity : %.2f\n", mini_rt.ambient_light.intensity);
	printf("color : %d, %d, %d\n", mini_rt.ambient_light.color.r, mini_rt.ambient_light.color.g, mini_rt.ambient_light.color.b);
	printf("\n\n");
	printf("CAMERA :\n");
	printf("origin :	%.2f,	%.2f,	%.2f\n", mini_rt.camera.origin.x, mini_rt.camera.origin.y, mini_rt.camera.origin.z);
	printf("orientation : %.2f, %.2f, %.2f\n", mini_rt.camera.orientation.x, mini_rt.camera.orientation.y, mini_rt.camera.orientation.z);
	printf("fov : %d\n", mini_rt.camera.fov);
	printf("\n\n");
}

void	print_item_lst(t_list *lst)
{
	t_item_type	type;
	t_cylinder	cy;
	t_plane		pl;
	t_sphere	sp;
	t_light		l;

	printf("[START]\n");
	while (lst)
	{
		type = ((t_shape *)lst->content)->type;
		if (type == CYLINDER)
		{
			printf("CYLINDER\n");
			cy = *(t_cylinder *)(((t_shape *)lst->content)->shape);
			printf("height :	%.2f\n", cy.height);
			printf("diameter :	%.2f\n", cy.diameter);
			printf("normal :	[%.2f,	%.2f,	%.2f]\n", cy.normal.x, cy.normal.y, cy.normal.z);
			printf("center:	[%.2f,	%.2f,	%.2f]\n", cy.center.x, cy.center.y, cy.center.z);
			printf("color :	(%d,	%d,	%d)\n", cy.c.r, cy.c.g, cy.c.b);
		}
		else if (type == PLANE)
		{
			printf("PLANE\n");
			pl = *(t_plane *)(((t_shape *)lst->content)->shape);
			printf("normal :	%.2f,	%.2f,	%.2f\n", pl.normal.x, pl.normal.y, pl.normal.z);
			printf("point:	[%.2f,	%.2f,	%.2f]\n", pl.p.x, pl.p.y, pl.p.z);
			printf("color :	(%d,	%d,	%d)\n", pl.c.r, pl.c.g, pl.c.b);
		}
		else if (type == SPHERE)
		{
			printf("SPHERE\n");
			sp = *(t_sphere *)(((t_shape *)lst->content)->shape);
			printf("diameter :	%.2f\n", sp.diameter);
			printf("center:	[%.2f,	%.2f,	%.2f]\n", sp.center.x, sp.center.y, sp.center.z);
			printf("color :	(%d,	%d,	%d)\n", sp.c.r, sp.c.g, sp.c.b);
		}
		else if (type == LIGHT)
		{
			printf("LIGHT\n");
			l = *(t_light *)(((t_shape *)lst->content)->shape);
			printf("point:	[%.2f,	%.2f,	%.2f]\n", l.origin.x, l.origin.y, l.origin.z);
			printf("brightness :	%.2f\n", l.intensity);
			printf("color :	(%d,	%d,	%d)\n", l.color.r, l.color.g, l.color.b);
		}
		lst = lst->next;
		printf("\n\n");
	}
	printf("[END]\n\n\n");
}
