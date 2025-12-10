/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:46:39 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 13:13:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// tests for ft_strtod function
// should convert a string to its double equivalent
// ie. "42.42" -> 42.42

#include "unity.h"
#include "parsing.h"

void	test_ft_strtod(void)
{
	char	*n;

	TEST_ASSERT_EQUAL_DOUBLE(42.0, ft_strtod("42", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(-42.0, ft_strtod("-42", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, ft_strtod("0", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(3.14, ft_strtod("3.14", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(-0.001, ft_strtod("-0.001", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(123456.789, ft_strtod("123456.789", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(-98765.4321, ft_strtod("-98765.4321", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, ft_strtod("1.", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(INT_MAX, ft_strtod("2147483647", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	TEST_ASSERT_EQUAL_DOUBLE(INT_MIN, ft_strtod("-2147483648", &n));
	TEST_ASSERT_EQUAL('\0', *n);
	ft_strtod("invalid123", &n);
	TEST_ASSERT_EQUAL_CHAR('i', *n);
	ft_strtod("123invalid", &n);
	TEST_ASSERT_EQUAL_CHAR('i', *n);
	ft_strtod("12.34.56", &n);
	TEST_ASSERT_EQUAL_CHAR('.', *n);
}
