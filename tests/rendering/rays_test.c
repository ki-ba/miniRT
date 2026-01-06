/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/23 11:16:34 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "rendering.h"

void	test_rays(void)
{
	TEST_ASSERT_EQUAL(1, find_intersections(NULL, NULL));
}

