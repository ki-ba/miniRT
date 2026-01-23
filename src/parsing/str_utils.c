/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:51:25 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:44:33 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdint.h"
#include <math.h>
#include "miniRT.h"
#include "parsing.h"

size_t	count_char_in_str(char *str, char c)
{
	size_t	i;
	size_t	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return (count);
}

uint8_t	ft_atoui_8(const char *nptr, char **n)
{
	uint8_t	number;
	size_t	i;

	if (nptr == NULL)
		return (0);
	i = (nptr[0] == '+');
	number = 0;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		if (number > 25 || (number == 25 && nptr[i] > '5'))
		{
			number = 255;
			break ;
		}
		number = (number * 10) + (nptr[i] - '0');
		++i;
	}
	*n = (char *)&nptr[i];
	return (number);
}

/**
* @brief Convert a string to a double-precision floating-point number.
* @details This function handles one optional '+' or '-' at the start.
* @param n A pointer to a string pointer that will be updated to point to the
*         character following the last processed character in the input string.
* @param str The string to convert.
* @return The converted double value.
*/

double	ft_strtod(char *str, char **n)
{
	double	d;
	int		decimal;
	int		i;
	int		sign;

	if (!str || !n)
		return (0.0);
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	decimal = ft_strlen_c(str, '.');
	i = (-1) + (str[0] == '+' || str[0] == '-');
	d = 0;
	while (str[++i])
	{
		if (i == decimal)
			continue ;
		else if (ft_isdigit(str[i]) == FALSE)
			break ;
		d += ((str[i] - '0')) / pow(10, i - decimal + (i < decimal));
	}
	*n = &str[i];
	return (sign * d);
}

/**
* @brief Check if the given filename has the correct extension.
* @param filename The name of the file to check.
* @return TRUE if the filename ends with the correct extension, FALSE otherwise.
*/
int	check_extension(char *filename, char *extension)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(&filename[len - 3], extension, 4))
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Format a line by trimming whitespace and splitting into tokens.
 * @param arr Pointer to store the resulting array of strings.
 * @param line The input line to format.
 * @return 0 on success, or an error code on failure.
 */
int	format_line(char ***arr, char *line)
{
	char	*trimmed_line;

	*arr = NULL;
	trimmed_line = ft_strtrim(line, WHITESPACES);
	if (!trimmed_line)
	{
		free(trimmed_line);
		return (MALLOC_ERR);
	}
	if (trimmed_line[0] == '#' || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (COMMENT_OR_EMPTY_LINE);
	}
	*arr = ft_split(line, WHITESPACES);
	if (!arr)
	{
		free(trimmed_line);
		return (MALLOC_ERR);
	}
	free(trimmed_line);
	return (0);
}
