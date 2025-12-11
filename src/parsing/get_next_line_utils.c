/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:39:29 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/10/26 19:00:46 by rgrangeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../../includes/get_next_line.h"

char	*free_chain(t_line **line, t_line_surp **line_surp)
{
	t_line		*temp;
	t_line_surp	*temp_surp;

	while (*line != NULL)
	{
		free((*line)->line);
		temp = (*line)->next;
		free(*line);
		(*line) = temp;
	}
	if ((*line_surp)->previous == NULL)
	{
		temp_surp = (*line_surp)->next;
		free(*line_surp);
		(*line_surp) = temp_surp;
		if (*line_surp)
			return ((*line_surp)->previous = NULL, NULL);
		return (NULL);
	}
	temp_surp = *line_surp;
	(*line_surp)->previous->next = (*line_surp)->next;
	*line_surp = (*line_surp)->previous;
	free(temp_surp);
	return (NULL);
}

char	*last_chain(t_line *line, t_line_surp *line_surp, char *final_line)
{
	ssize_t	i;
	ssize_t	ti;

	i = -1;
	ti = line_surp->start;
	while (line->next != NULL)
	{
		while (line->line[++ti])
			final_line[++i] = line->line[ti];
		line = line->next;
		ti = -1;
	}
	while (line->line[++ti] != '\0' && line->line[ti] != '\n')
		final_line[++i] = line->line[ti];
	final_line[++i] = line->line[ti];
	if (final_line[i] != '\0')
	{
		final_line[++i] = '\0';
		if (line->line[ti + 1] == '\0')
			return (line_surp->start = -1, final_line);
		line_surp->start = ti;
		return (line_surp->memory = line, final_line);
	}
	return (line_surp->start = -1, final_line);
}

t_line	*new_readings(t_line *line, int fd, ssize_t	*read_size)
{
	line = malloc(sizeof(t_line));
	if (line == NULL)
		return (NULL);
	line->line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (line->line == NULL)
	{
		free(line);
		return (NULL);
	}
	line->next = NULL;
	*read_size = read(fd, line->line, BUFFER_SIZE);
	if (*read_size <= 0)
	{
		free(line->line);
		free(line);
		return (NULL);
	}
	line->line[*read_size] = '\0';
	return (line);
}

char	*checker(t_line_surp **line_surp, t_line *line,
		ssize_t read_size, int fd)
{
	t_line	*start_line;
	ssize_t	i;
	ssize_t	size;

	size = 0;
	i = (*line_surp)->start;
	start_line = line;
	while (read_size == BUFFER_SIZE)
	{
		while (line->line[++i])
		{
			if (i[line->line] == '\n')
				return (line_assemblers(line_surp, &start_line, (size + i + 1)
						- (*line_surp)->start));
		}
		size += i;
		line->next = new_readings(line, fd, &read_size);
		if (read_size == 0)
			break ;
		if ((read_size <= -1) || (line->next == NULL))
			return (free_chain(&start_line, line_surp));
		line = line->next;
		i = -1;
	}
	return (line_assemblers(line_surp, &start_line, size + read_size + 1));
}
