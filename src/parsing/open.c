/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:14 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 18:42:31 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "parsing.h"

static int	find_rt(const char *path)
{
	int	len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}

int	open_file(const char *path)
{
	int	fd;

	fd = -1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (putstr_error("Error while opening the scene"));
	if (!find_rt(path))
	{
		close(fd);
		return (putstr_error("Not .rt file"));
	}
	return (fd);
}
