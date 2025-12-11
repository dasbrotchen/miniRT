/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:36:28 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:16:07 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include <errno.h>

static int	element_finder(char *line, t_nbr_element *nbr_element)
{
	if (ft_strncmp(line, "A", 1) == 0)
		nbr_element->ambient_lightning++;
	else if (ft_strncmp(line, "C", 1) == 0)
		nbr_element->camera++;
	else if (ft_strncmp(line, "L", 1) == 0)
		nbr_element->light++;
	else if (ft_strncmp(line, "sp", 2) == 0)
		nbr_element->object++;
	else if (ft_strncmp(line, "pl", 2) == 0)
		nbr_element->object++;
	else if (ft_strncmp(line, "cy", 2) == 0)
		nbr_element->object++;
	else if (ft_strncmp(line, "co", 2) == 0)
		nbr_element->object++;
	else if (!ft_strncmp(line, "//", 2) || !ft_strncmp(line, "\n", 1)
		|| !ft_strncmp(line, " ", 1) || !ft_strncmp(line, "\t", 1))
		return (0);
	else
	{
		nbr_element->error = putstr_error("Unrecognised object");
		return (-1);
	}
	return (0);
}

static void	init_element(t_nbr_element *nbr_element)
{
	nbr_element->ambient_lightning = 0;
	nbr_element->camera = 0;
	nbr_element->light = 0;
	nbr_element->object = 0;
	nbr_element->error = 1;
}

static t_nbr_element	check_nbr_element(t_nbr_element nbr_element)
{
	if (nbr_element.ambient_lightning != 1)
		nbr_element.error = putstr_error("You need to provide \
one ambient light description");
	if (nbr_element.camera != 1)
		nbr_element.error = putstr_error("You need to provide \
one camera description");
	if (nbr_element.light < 1)
		nbr_element.error = putstr_error("You need to provide \
at least one light point description");
	if (nbr_element.object < 1)
		nbr_element.error = putstr_error("You need to provide \
at least one object description");
	return (nbr_element);
}

static t_nbr_element	file_processor(int fd, t_nbr_element nbr_element,
							char *line)
{
	char	**split;

	while (line)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (split_malloc_error(line, fd, nbr_element));
		element_finder(split[0], &nbr_element);
		free_split(split);
		free(line);
		if (nbr_element.error == ERROR)
			return (unrecognised_object(fd, nbr_element));
		line = get_next_line(fd);
		if (errno == ENOMEM)
		{
			nbr_element.error = putstr_error("Malloc error");
			return (nbr_element);
		}
	}
	return (nbr_element);
}

t_nbr_element	element_counter(int fd)
{
	char			*line;
	t_nbr_element	nbr_element;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		nbr_element.error = putstr_error("Empty file");
		return (nbr_element);
	}
	init_element(&nbr_element);
	nbr_element = file_processor(fd, nbr_element, line);
	if (nbr_element.error == ERROR)
	{
		close(fd);
		return (nbr_element);
	}
	nbr_element = check_nbr_element(nbr_element);
	close(fd);
	return (nbr_element);
}
