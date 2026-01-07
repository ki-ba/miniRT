/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:54:24 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:51:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "parsing.h"

void	test_count_char_in_str(void)
{
	size_t	count;

	count = count_char_in_str("hello,world,this,is,a,test", ',');
	TEST_ASSERT_EQUAL_INT(5, count);
	count = count_char_in_str("no commas here", ',');
	TEST_ASSERT_EQUAL_INT(0, count);
	count = count_char_in_str("", ',');
	TEST_ASSERT_EQUAL_INT(0, count);
	count = count_char_in_str(NULL, ',');
	TEST_ASSERT_EQUAL_INT(0, count);
}

void	test_ft_atoui_8(void)
{
	char	*n;
	uint8_t	value;

	value = ft_atoui_8("255", &n);
	TEST_ASSERT_EQUAL_UINT8(255, value);
	TEST_ASSERT_EQUAL(0, *n);
	value = ft_atoui_8("0", &n);
	TEST_ASSERT_EQUAL_UINT8(0, value);
	TEST_ASSERT_EQUAL(0, *n);
	value = ft_atoui_8("128abc", &n);
	TEST_ASSERT_EQUAL_UINT8(128, value);
	TEST_ASSERT_EQUAL('a', *n);
	value = ft_atoui_8("300", &n);
	TEST_ASSERT_EQUAL_UINT8(255, value);
	TEST_ASSERT_EQUAL('0', *n);
	value = ft_atoui_8("-1", &n);
	TEST_ASSERT_EQUAL_UINT8(0, value);
	TEST_ASSERT_EQUAL('-', *n);
	value = ft_atoui_8(NULL, &n);
	TEST_ASSERT_EQUAL_UINT8(0, value);
}

void	test_ft_strtod(void)
{
	char	*n;
	double	value;

	value = ft_strtod("123.456", &n);
	TEST_ASSERT_EQUAL_DOUBLE(123.456, value);
	TEST_ASSERT_EQUAL_STRING("", n);

	value = ft_strtod("-78.9abc", &n);
	TEST_ASSERT_EQUAL_DOUBLE(-78.9, value);
	TEST_ASSERT_EQUAL_STRING("abc", n);

	value = ft_strtod("+0.00123xyz", &n);
	TEST_ASSERT_EQUAL_DOUBLE(0.00123, value);
	TEST_ASSERT_EQUAL_STRING("xyz", n);

	value = ft_strtod("42", &n);
	TEST_ASSERT_EQUAL_DOUBLE(42.0, value);
	TEST_ASSERT_EQUAL_STRING("", n);

	value = ft_strtod("invalid", &n);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, value);
	TEST_ASSERT_EQUAL_STRING("invalid", n);

	value = ft_strtod(NULL, &n);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, value);
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

void	test_check_extension(void)
{
	TEST_ASSERT_EQUAL_INT(TRUE, check_extension("scene.rt", EXTENSION));
	TEST_ASSERT_EQUAL_INT(TRUE, check_extension("e.rt", EXTENSION));
	TEST_ASSERT_EQUAL_INT(FALSE, check_extension(".rt", EXTENSION));
	TEST_ASSERT_EQUAL_INT(FALSE, check_extension("scene.txt", EXTENSION));
	TEST_ASSERT_EQUAL_INT(FALSE, check_extension("scenert", EXTENSION));
	TEST_ASSERT_EQUAL_INT(FALSE, check_extension("sc.rt.txt", EXTENSION));
	TEST_ASSERT_EQUAL_INT(FALSE, check_extension("sc.rtt", EXTENSION));
}
