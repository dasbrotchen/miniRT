/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:39:26 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/10/26 19:42:39 by rgrangeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <sys/types.h>

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}	t_line;

typedef struct s_line_surplus
{
	int						fd;
	ssize_t					start;
	struct s_line			*memory;
	struct s_line_surplus	*previous;
	struct s_line_surplus	*next;
}	t_line_surp;

char	*get_next_line(int fd);
char	*free_chain(t_line **line, t_line_surp **line_surp);
char	*last_chain(t_line *line, t_line_surp *line_surp, char *final_line);
t_line	*new_readings(t_line *line, int fd, ssize_t *read_size);
char	*checker(t_line_surp **line_surp, t_line *line,
			ssize_t read_size, int fd);
char	*line_assemblers(t_line_surp **line_surp, t_line **line, ssize_t size);

#endif // !GET_NEXT_LINE_H
