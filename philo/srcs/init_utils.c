/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:56:12 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 20:14:33 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	ft_parse_parameters(int params[], int size, char **argv)
{
	int	i;

	i = 0;
	while (i < 5)
		params[i++] = -1;
	i = 0;
	while (i < size && argv[i + 1])
	{
		params[i] = ft_atol(argv[i + 1]);
		if (params[i] <= 0)
		{
			printf("invalid parameter\n");
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}
