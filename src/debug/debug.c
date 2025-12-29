/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:35:49 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:39:34 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "debug.h"

void	print_cylinder(t_cylinder cy)
{
	printf("CYLINDER\n");
	printf("height :	%.2f\n", cy.height);
	printf("diameter :	%.2f\n", cy.diameter);
	print_vector("normal", cy.normal);
	print_point("center", cy.center);
	print_color("color", cy.c);
}

void	print_plane(t_plane pl)
{
	printf("PLANE\n");
	print_vector("normal", pl.normal);
	print_point("point", pl.p);
	print_color("color", pl.c);
}

void	print_sphere(t_sphere sp)
{
	printf("SPHERE\n");
	printf("diameter :	%.2f\n", sp.diameter);
	print_point("center", sp.center);
	print_color("color", sp.c);
}

void	print_light(t_light l)
{
	printf("LIGHT\n");
	print_point("origin", l.origin);
	print_color("color", l.color);
	printf("brightness :	%.2f\n", l.intensity);
}

void	print_item_lst(t_list *lst)
{
	enum e_item_type	type;
	t_shape				*shape;

	printf("[START]\n");
	while (lst)
	{
		shape = (t_shape *)(lst->content);
		type = shape->type;
		if (type == CYLINDER)
			print_cylinder(*(t_cylinder *)(shape->shape));
		else if (type == PLANE)
			print_plane(*(t_plane *)(shape->shape));
		else if (type == SPHERE)
			print_sphere(*(t_sphere *)(shape->shape));
		else if (type == LIGHT)
			print_light(*(t_light *)(shape->shape));
		printf("\n\n");
		lst = lst->next;
	}
	printf("[END]\n\n\n");
}
