/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:56:18 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/12 10:58:37 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union u_color		t_color;
union u_color
{
	uint32_t	trgb;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	};
};

t_color	scale_color(t_color color, double scale);
t_color	mul_color(t_color c1, t_color c2);
t_color	add_color(t_color c1, t_color c2);

#endif
