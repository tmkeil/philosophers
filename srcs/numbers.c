/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:22:15 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/15 19:02:22 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_length(long nbr)
{
	size_t	i;

	i = 0;
	if (!nbr)
		return (1);
	if (nbr < 0)
	{
		i++;
		nbr = -nbr;
	}
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long nbr)
{
	size_t	size;
	char	*s_nbr;
	int		was_neg;

	was_neg = 0;
	size = ft_length(nbr);
	s_nbr = malloc(sizeof(char) * (size + 1));
	s_nbr[size] = '\0';
	if (nbr < 0)
	{
		s_nbr[0] = '-';
		was_neg = 1;
		nbr = -nbr;
	}
	while ((size--) - was_neg)
	{
		s_nbr[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (s_nbr);
}

long	ft_atol(char *s)
{
	size_t	i;
	int		p;
	long	val;
	bool	valid;

	i = 0;
	p = 1;
	val = 0;
	valid = false;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			p = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		valid = true;
		val = val * 10 + (s[i++] - '0');
	}
	if (!valid || s[i] != '\0')
		return (LONG_MIN);
	return (val * p);
}
