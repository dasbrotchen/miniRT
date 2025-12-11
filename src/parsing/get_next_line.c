/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:39:24 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/10/26 19:00:34 by rgrangeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../../includes/get_next_line.h"

char	*line_assemblers(t_line_surp **line_surp, t_line **line, ssize_t size)
{
	char	*final_line;
	t_line	*temp;

	final_line = malloc(sizeof(char) * size);
	if (final_line == NULL)
		return (free_chain(line, line_surp));
	final_line = last_chain(*line, *line_surp, final_line);
	while ((*line)->next != NULL)
	{
		free((*line)->line);
		temp = (*line)->next;
		free(*line);
		*line = temp;
	}
	if ((*line_surp)->start == -1)
	{
		free((*line)->line);
		free(*line);
	}
	return (final_line);
}

char	*line_reader(t_line_surp **line_surp, int fd)
{
	t_line	*line;
	ssize_t	read_size;

	line = NULL;
	read_size = BUFFER_SIZE;
	if ((*line_surp)->start <= -1)
	{
		line = new_readings(line, fd, &read_size);
		if ((line == NULL) || (read_size <= 0))
			return (free_chain(&line, line_surp));
	}
	else
		line = (*line_surp)->memory;
	return (checker(line_surp, line, read_size, fd));
}

t_line_surp	*chain_creators(t_line_surp *line_surp, int fd)
{
	while (line_surp->fd != fd)
	{
		if (line_surp->next == NULL)
		{
			line_surp->next = malloc(sizeof(t_line_surp));
			if (line_surp->next == NULL)
				return (NULL);
			line_surp->next->previous = line_surp;
			line_surp = line_surp->next;
			line_surp->next = NULL;
			line_surp->fd = fd;
			line_surp->start = -1;
			return (line_surp);
		}
		line_surp = line_surp->next;
	}
	return (line_surp);
}

t_line_surp	*surplus_line_creation(t_line_surp **line_surp_m, int fd)
{
	t_line_surp			*line_surp;

	line_surp = *line_surp_m;
	if (line_surp == NULL)
	{
		line_surp = malloc(sizeof(t_line_surp));
		if (line_surp == NULL)
			return (NULL);
		line_surp->next = NULL;
		line_surp->fd = fd;
		line_surp->start = -1;
		line_surp->previous = NULL;
		*line_surp_m = line_surp;
	}
	return (chain_creators(line_surp, fd));
}

char	*get_next_line(int fd)
{
	static t_line_surp	*line_surp_m;
	t_line_surp			*line_surp;
	char				*line;

	line_surp = surplus_line_creation(&line_surp_m, fd);
	if (line_surp == NULL)
		return (NULL);
	line = line_reader(&line_surp, fd);
	if (!line_surp || (!line_surp->previous && (line_surp_m != line_surp)))
		line_surp_m = line_surp;
	return (line);
}
