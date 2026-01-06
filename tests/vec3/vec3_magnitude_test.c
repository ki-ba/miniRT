/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_magnitude_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:17:32 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:28:54 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "unity.h"
#include "vec3.h"

void	test_vec3_magnitude(void)
{
    t_vec3 v;
	double res;

	v = (t_vec3) {0.0, 0.0, 0.0};
    res = vec3_magnitude(&v);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res);

	v = (t_vec3) {0.0, 1.0, 0.0};
    res = vec3_magnitude(&v);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, res);
	
	v = (t_vec3) {3.0, 4.0, 12.0};
    res = vec3_magnitude(&v);
    TEST_ASSERT_EQUAL_DOUBLE(sqrt(3.0*3.0 + 4.0*4.0 + 12.0*12.0), res);

	v = (t_vec3) {-3.0, -4.0, -12.0};
    res = vec3_magnitude(&v);
    TEST_ASSERT_EQUAL_DOUBLE(sqrt(3.0*3.0 + 4.0*4.0 + 12.0*12.0), res);
}

