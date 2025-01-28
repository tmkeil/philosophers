/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:56:12 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/28 14:22:21 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
