/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/24 15:42:16 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

/**
* @brief Check if the given filename has the correct extension.
* @param filename The name of the file to check.
* @return TRUE if the filename ends with the correct extension, FALSE otherwise.
*/
int	has_correct_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(&filename[len - 3], EXTENSION, 4))
		return (FALSE);
	return (TRUE);
}
