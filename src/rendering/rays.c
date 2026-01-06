/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:47:25 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/23 11:16:22 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void		*clear_inters_vector(t_inter *inters)
{
	(void)inters;
	return (NULL);
}

t_vector	*find_intersections(t_point const *pos, t_vec3 const *dir, t_mini_rt const *mini_rt, const t_item_type mode)
{
	const t_list 	*lights = mini_rt->lights;
	const t_list 	*objs = mini_rt->objs;
	t_vector		*inters;

	inters = create_vector(4, sizeof(t_inter), clear_inters_vector);
	if (!inters)
		return (NULL);
	(void)pos;
	(void)dir;
	(void)objs;
	(void)lights;
	(void)type;
	return (inters);
}

t_ray		*trace_rays(t_point const *src, t_viewport const *vp, t_mini_rt const *mini_rt, const t_item_type mode)
{
	t_ray	*rays;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	rays = ft_calloc(vp->x * vp->y, sizeof(t_ray));
	if (!rays)
		return (NULL);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rays[k++] = (t_ray) {find_intersections(), tmp_dir, pos, type}
			++j;
		}
		++i;
	}
	return (rays);
}

// int			trace_rays_from_camera(t_mini_rt *mini_rt)
// {
// 	t_vec3	tmp_direction;
// 	int		i;
// 	int 	j;
// 	int		k;
//
// 	i = 0;
// 	k = 0;
// 	mini_rt->rays = malloc(0);
// 	if (!mini_rt->rays)
// 		return (1);
// 	while (i < HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WIDTH)
// 		{
// 			tmp_direction = (t_vec3) {};
// 			mini_rt->rays[k] = (t_ray)
// 			{	&mini_rt->camera,
// 				find_intersection(&mini_rt->camera.origin, &tmp_direction, mini_rt->objects),
// 				tmp_direction,
// 				mini_rt->camera.origin,
// 				CAMERA	};
// 			++j;
// 		}
// 		++i;
// 	}
// 	return (0);
// }
//
