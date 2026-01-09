/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_create_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/06 19:12:48 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_create(void)
{
	t_point	o;
	t_point d;
	t_vec3 	res;

	o = (t_point){0, 0, 0};
    d = (t_point){1, -2, 3};
    res = vec3_create(o, d);

    TEST_ASSERT_EQUAL_DOUBLE(1.0,  res.x);
    TEST_ASSERT_EQUAL_DOUBLE(-2.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(3.0,  res.z);
	
	o = (t_point){10, 20, 30};
    d = (t_point){-1.5, 2.5, 0.0};
    res = vec3_create(o, d);

    TEST_ASSERT_EQUAL_DOUBLE(-11.5, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(-17.5, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(-30.0, res.z);

    o = (t_point){5, -7, 9};
    d = (t_point){0.0, 0.0, 0.0};
    res = vec3_create(o, d);
    TEST_ASSERT_EQUAL_DOUBLE(-5.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(7.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(-9.0, res.z);
}
