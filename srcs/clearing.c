/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:28:04 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/16 18:07:17 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clear_philos(t_philo **philos, int n)
{
	t_philo	*tmp;

	while (n--)
	{
		tmp = (*philos)->right;
		free(*philos);
		*philos = tmp;
	}
	*philos = NULL;
}
