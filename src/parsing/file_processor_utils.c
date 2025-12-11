/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_processor_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:12:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 17:37:00 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_nbr_element	unrecognised_object(int fd, t_nbr_element nbr_element)
{
	free_gnl(fd);
	return (nbr_element);
}

t_nbr_element	split_malloc_error(char *line, int fd,
					t_nbr_element nbr_element)
{
	free(line);
	free_gnl(fd);
	nbr_element.error = putstr_error("Malloc error");
	return (nbr_element);
}

void	*putstr_malloc_error(void)
{
	putstr_error("Malloc error");
	return (NULL);
}

int	split_scene_malloc_error(char *line, int fd,
		t_memory_scene mscene, t_scene *scene)
{
	free(line);
	putstr_error("Malloc error");
	origin_scene(mscene, scene);
	free_gnl(fd);
	return (ERROR);
}
