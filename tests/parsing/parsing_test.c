/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:17:35 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/24 15:31:51 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "parsing.h"

void	test_has_correct_extension(void)
{
	TEST_ASSERT_EQUAL_INT(TRUE, has_correct_extension("scene.rt"));
	TEST_ASSERT_EQUAL_INT(TRUE, has_correct_extension("e.rt"));
	TEST_ASSERT_EQUAL_INT(FALSE, has_correct_extension(".rt"));
	TEST_ASSERT_EQUAL_INT(FALSE, has_correct_extension("scene.txt"));
	TEST_ASSERT_EQUAL_INT(FALSE, has_correct_extension("scenert"));
	TEST_ASSERT_EQUAL_INT(FALSE, has_correct_extension("sc.rt.txt"));
	TEST_ASSERT_EQUAL_INT(FALSE, has_correct_extension("sc.rtt"));
}
