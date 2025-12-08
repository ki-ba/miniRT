/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:03:01 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 15:13:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "miniRT.h"

# define WHITESPACES " \t\n\v\f\r"

/* PARSING */

// t_list	list_spheres(int fd);
t_list			*parse_shapes_in_file(t_miniRT *miniRT, int fd);
t_list			*create_shape_lst(char **shape_arr);
int				parse_items_in_file(t_miniRT *miniRT, int fd);

/* PARSING UTILS */

double			ft_strtod(char *str);
int				has_correct_extension(char *filename);
int				define_item_type(char *id);
int				is_property_id(char *id);
t_bool			is_normalized(t_vec3 vector);

size_t	arr_len(char **arr);

/* READ PROPERTIES */

int			read_color(t_color *c, char *string);
int			read_point(t_point *p, char *string);
int			read_normalized_vec(t_vec3 *v, char *string);

#endif
