/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:29 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:17:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	find_sign(const char *string, float *sign)
{
	int		i;

	i = 0;
	while ((string[i] >= '\t' && string[i] <= '\r') || string[i] == ' ')
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static float	translator(const char *nptr, int *error)
{
	float	nbr;

	nbr = 0;
	if (*nptr < '0' || *nptr > '9')
		return (*error = -2);
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		nbr = (*nptr) - 48 + nbr;
		if (nbr > COORD_MAX)
			return (*error = -1);
		nbr *= 10.0f;
		nptr++;
	}
	nbr = (nbr * 0.1f);
	return (nbr);
}

float	str_float(const char *string, int *error)
{
	float	nbr;
	float	nbr_dec;
	float	sign;

	nbr_dec = 0;
	sign = 1;
	string += find_sign(string, &sign);
	nbr = translator(string, error);
	if (*error != 2)
		return (nbr);
	while (*string && *string != '.')
		++string;
	if (*string == '.')
		nbr_dec = translator(string + 1, error);
	if (*error != 2)
		return (nbr);
	while (*string++ && (*string >= '0' && *string <= '9'))
		nbr_dec *= 0.1f;
	nbr += nbr_dec;
	return (nbr * sign);
}

int	str_colour(const char *nptr, int *error)
{
	int		nbr;

	nbr = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (0);
		nptr++;
	}
	if (*nptr < '0' || *nptr > '9')
		return (*error = -2);
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		nbr = ((*nptr) - 48 + nbr);
		if (nbr > 255)
			return (255);
		nbr *= 10;
		nptr++;
	}
	nbr = (nbr * 0.1f);
	return (nbr);
}

int	str_fov(const char *nptr, int *error)
{
	int		nbr;

	nbr = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (0);
		nptr++;
	}
	if (*nptr < '0' || *nptr > '9')
		return (*error = -2);
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		nbr = ((*nptr) - 48 + nbr);
		if (nbr > 180)
			return (180);
		nbr *= 10;
		nptr++;
	}
	nbr = (nbr * 0.1f);
	return (nbr);
}
