/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:02:52 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/04 14:25:35 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "test.h"

void	setUp(void)
{
}

void	tearDown(void)
{
}

int	main(void)
{
	// PARSING TESTS
	RUN_TEST(test_has_correct_extension);
	RUN_TEST(test_ft_strtod);



	// OBJECTS TESTS
	RUN_TEST(test_create_light_success);
	return (0);
}
