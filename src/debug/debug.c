/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:35:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/14 16:37:21 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "objects.h"
#include "vectors.h"
#include "core.h"

void	print_cylinder(t_object cy)
{
	printf("CYLINDER\n");
	printf("height :	%.2f\n", cy.h);
	printf("diameter :	%.2f\n", cy.diam);
	print_vector("normal", cy.n);
	print_vec3("center", cy.center);
	print_color("color", cy.c);
}

void	print_plane(t_object pl)
{
	printf("PLANE\n");
	print_vector("normal", pl.n);
	print_vec3("point", pl.p);
	print_color("color", pl.c);
}

void	print_sphere(t_object sp)
{
	printf("SPHERE\n");
	printf("diameter :	%.2f\n", sp.diam);
	print_vec3("center", sp.center);
	print_color("color", sp.c);
}

void	print_obj(t_object obj)
{
	if (obj.type == CYLINDER)
		printf("Type : Cylinder\n");
	else if (obj.type == PLANE)
		printf("Type : Plane\n");
	else if (obj.type == SPHERE)
		printf("Type : Sphere\n");
	else if (obj.type == LIGHT)
		printf("Type : Light\n");
	else
		printf("[unknown object]\n");
	printf("Height :	%.2f\n", obj.h);
	printf("Diameter :	%.2f\n", obj.diam);
	print_vector("normal", obj.n);
	print_vec3("center", obj.center);
	print_vec3("point", obj.p);
	print_color("color", obj.c);
}

void	print_light(t_light l)
{
	printf("LIGHT\n");
	print_vec3("origin", l.ori);
	print_color("color", l.c);
	printf("brightness :	%.2f\n", l.i);
}

void	print_item_lst(t_vector *objects)
{
	size_t		i;
	t_object	*obj;

	i = 0;
	printf("[START]\n");
	while (i < objects->nb_elements)
	{
		obj = get_ith_obj(objects, i);
		if (!obj)
		{
			printf("Error retrieving object at index %zu\n", i);
			return ;
		}
		print_obj(*obj);
		printf("\n\n");
		++i;
	}
	printf("[END]\n\n\n");
}

void	print_lights(t_vector *lights)
{
	size_t	i;
	t_light	*light;

	i = 0;
	printf("----- LIGHTS LIST -----\n");
	while (i < lights->nb_elements)
	{
		light = (t_light *)get_ith_light(lights, i);
		if (!light)
		{
			printf("Error retrieving light at index %zu\n", i);
			return ;
		}
		print_light(*light);
		printf("\n");
		++i;
	}
	printf("----- END OF LIGHTS LIST -----\n\n");
}
