/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:08:42 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 14:37:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

// PARSING

void	test_has_correct_extension(void);
void	test_ft_strtod(void);

// READ PROPERTIES

void	test_read_color(void);
void	test_read_point(void);
void	test_read_normalized_vec(void);

// OBJECTS

void	test_create_light(void);
void	test_create_plane(void);
void	test_create_cylinder(void);
void	test_create_sphere(void);

// DEBUG

void	debug_test_function(void);
void	debug_utils_test_function(void);

#endif
