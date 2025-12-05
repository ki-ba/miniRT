/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:46:39 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/05 12:48:59 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// tests for ft_strtod function
// should convert a string to its double equivalent
// ie. "42.42" -> 42.42
//

#include "unity.h"
#include "parsing.h"
#include <limits.h>
#include <stddef.h>

void	test_ft_strtod(void)
{
	TEST_ASSERT_EQUAL_DOUBLE(42.0, ft_strtod("42"));
	TEST_ASSERT_EQUAL_DOUBLE(0.0, ft_strtod("0"));
	TEST_ASSERT_EQUAL_DOUBLE(-7.5, ft_strtod("-7.5"));
	TEST_ASSERT_EQUAL_DOUBLE(-0.0, ft_strtod("-0.0"));
	TEST_ASSERT_EQUAL_DOUBLE(-0.0, ft_strtod("-0.0"));
	TEST_ASSERT_EQUAL_DOUBLE(3.1415926535, ft_strtod("3.1415926535"));
	TEST_ASSERT_EQUAL_DOUBLE(123456.789, ft_strtod("123456.789"));
	TEST_ASSERT_EQUAL_DOUBLE(INT_MAX, ft_strtod("2147483647"));
	TEST_ASSERT_EQUAL_DOUBLE(INT_MIN, ft_strtod("-2147483648"));
}
