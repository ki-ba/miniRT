/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:35:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/11 12:00:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "objects.h"
#include "vectors.h"

t_object	*get_ith_element(t_vector *vector, size_t index)
{
	t_object	*array;

	if (index >= vector->nb_elements)
		return (NULL);
	array = (t_object *)(vector->array);
	return (&(array[index]));
}

void	print_cylinder(t_object cy)
{
	printf("CYLINDER\n");
	printf("height :	%.2f\n", cy.height);
	printf("diameter :	%.2f\n", cy.diameter);
	print_vector("normal", cy.normal);
	print_vec3("center", cy.center);
	print_color("color", cy.color);
}

void	print_plane(t_object pl)
{
	printf("PLANE\n");
	print_vector("normal", pl.normal);
	print_vec3("point", pl.point);
	print_color("color", pl.color);
}

void	print_sphere(t_object sp)
{
	printf("SPHERE\n");
	printf("diameter :	%.2f\n", sp.diameter);
	print_vec3("center", sp.center);
	print_color("color", sp.color);
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
	printf("Height :	%.2f\n", obj.height);
	printf("Diameter :	%.2f\n", obj.diameter);
	print_vector("normal", obj.normal);
	print_vec3("center", obj.center);
	print_vec3("point", obj.point);
	print_color("color", obj.color);
}

void	print_light(t_light l)
{

	printf("LIGHT\n");
	print_vec3("origin", l.origin);
	print_color("color", l.color);
	printf("brightness :	%.2f\n", l.intensity);
}

void	print_item_lst(t_vector *objects)
{
	size_t		i;
	t_object	*obj;

	i = 0;
	printf("[START]\n");
	while (i < objects->nb_elements && i < 2)
	{
		obj = get_ith_element(objects, i);
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

void print_lights(t_vector *lights)
{
	size_t	i;
	t_light	*light;

	i = 0;
	printf("----- LIGHTS LIST -----\n");
	while (i < lights->nb_elements)
	{
		light = (t_light *)get_ith_element(lights, i);
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
