/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:03:01 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:50:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "miniRT.h"

# define WHITESPACES " \t\n\v\f\r"

# define EXTENSION ".rt"

# define PLANE_ID "pl"
# define CYLINDER_ID "cy"
# define SPHERE_ID "sp"
# define AMBIENT_ID "A"
# define LIGHT_ID "L"
# define CAMERA_ID "C"

# define USAGE_ERR_MSG "usage : ./miniRT filename.rt\n"
# define FILE_ERR_MSG "Error while reading file\n"
# define MISSING_PROPERTY_MSG "Error: Missing required property (A or C)\n"
# define TOO_MUCH_ELEMENTS_MSG "Error: More than 1 [C]amera, [L]ight, or \
[A]mbiant light\n"
# define VECTOR_NOT_NORMALIZED "Error: The vector is not normalized\n"

/* PARSING */

t_list			*parse_shapes_in_file(t_mini_rt *mini_rt, int fd);
t_list			*create_shape_lst(char **shape_arr);
int				parse_items_in_file(t_mini_rt *mini_rt, int fd);
size_t			arr_len(char **arr);

/* PARSING UTILS */

int				define_item_type(char *id);
int				is_property_id(char *id);
t_bool			is_normalized(t_vec3 vector);

/* STR UTILS */

uint8_t			ft_atoui_8(const char *nptr, char **n);
double			ft_strtod(char *str, char **n);
int				check_extension(char *filename, char *extension);
size_t			count_char_in_str(char *str, char c);

/* READ PROPERTIES */

int				read_color(t_color *c, char *string);
int				read_point(t_point *p, char *string);
int				read_normalized_vec(t_vec3 *v, char *string);

#endif
