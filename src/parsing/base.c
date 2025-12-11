/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:17:40 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:12:28 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "get_next_line.h"

int	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (ERROR);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

/*
* min params sphere: 4
* min params plane: 4
* min params cylinder: 6
* min params cone: 6
*
* for textured: min_params +1
* for checkerboard: min_params + 4
*/
int	object_valid_n_params(unsigned int type, unsigned int n_param,
		unsigned int min_params)
{
	if (type == NORMAL && n_param >= min_params
		&& n_param <= min_params + 4)
		return (0);
	if (type == TEXTURED && n_param >= min_params + 1
		&& n_param <= min_params + 5)
		return (0);
	if (type == CHECKERED && n_param >= min_params + 4
		&& n_param <= min_params + 8)
		return (0);
	return (1);
}

int	nbr_parameters(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	putstr_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("!\n", 2);
	return (ERROR);
}
