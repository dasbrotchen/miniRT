/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:42 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 15:40:55 by rgrangeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	percentage(int progress, char *str)
{
	str[52] = ' ';
	if (progress < 10)
	{
		str[53] = ' ';
		str[54] = ' ';
		str[55] = '0' + progress;
	}
	else if (progress < 100)
	{
		str[53] = ' ';
		str[54] = '0' + (progress / 10);
		str[55] = '0' + (progress % 10);
	}
	else
	{
		str[53] = '1';
		str[54] = '0';
		str[55] = '0';
	}
	str[56] = '%';
}

void	progress_bar(int start, int max)
{
	char	str[59];
	int		progress;
	int		i;

	i = 0;
	str[0] = '[';
	str[51] = ']';
	progress = (start * 50) / max;
	while (++i < progress + 1)
		str[i] = '#';
	while (i < 51)
	{
		str[i] = ' ';
		i++;
	}
	progress = (start * 100) / max;
	percentage(progress, str);
	str[57] = '\r';
	write(1, str, 58);
}
