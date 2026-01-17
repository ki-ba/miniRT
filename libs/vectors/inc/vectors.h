/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:01:31 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/09 13:02:51 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_vector	t_vector;

struct					s_vector
{
	void				*array;
	size_t				datatype_size;
	size_t				capacity;
	size_t				nb_elements;
	size_t				occupied_bytes;
	void				(*clear_array)(t_vector *vec);
};

t_vector				*create_vector(size_t capacity, size_t datatype_size,
							void (*clear_array)(t_vector *));
bool					grow_vector(t_vector *vec, size_t new_elements);
bool					add_element(t_vector *vec, void *element);
void					clear_vector(t_vector **vec);

#endif
