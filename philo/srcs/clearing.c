/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:28:04 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/28 12:32:22 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clear_data(t_philos **philos, int n)
{
	t_philos	*tmp;

	pthread_mutex_destroy(&(*philos)->info->print_mutex);
	pthread_mutex_destroy(&(*philos)->info->death_mutex);
	free((*philos)->info);
	while (n--)
	{
		tmp = (*philos)->right;
		pthread_mutex_destroy((*philos)->fork_l);
		pthread_mutex_destroy(&(*philos)->philo_mutex);
		free(*philos);
		*philos = tmp;
	}
	*philos = NULL;
}
