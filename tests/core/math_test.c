/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:27:29 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/18 13:33:51 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "unity.h"

// Test case 1: Two distinct real roots
// Test case 2: One real root (double root)
// Test case 3: No real roots
void	test_resolve_eq2(void)
{
	t_roots	*roots;

	roots = resolve_eq2(1, -3, 2);
	TEST_ASSERT_NOT_NULL(roots);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, roots->root1);
	TEST_ASSERT_EQUAL_DOUBLE(2.0, roots->root2);
	TEST_ASSERT_GREATER_THAN(0, roots->delta);
	free(roots);
	roots = resolve_eq2(1, -2, 1);
	TEST_ASSERT_NOT_NULL(roots);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, roots->root1);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, roots->root2);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, roots->delta);
	free(roots);
	roots = resolve_eq2(1, 0, 1);
	TEST_ASSERT_NOT_NULL(roots);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, roots->root1);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, roots->root2);
	TEST_ASSERT_LESS_THAN(0, roots->delta);
	free(roots);
}
