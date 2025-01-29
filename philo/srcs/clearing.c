/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:28:04 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 16:36:58 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clear_data(t_philos **philos, int n)
{
	t_philos	*tmp;
	t_info		*info;

	if (!philos || !*philos)
		return ;
	info = (*philos)->info;
	while (n--)
	{
		tmp = (*philos)->right;
		if ((*philos)->fork_l)
			pthread_mutex_destroy((*philos)->fork_l);
		pthread_mutex_destroy(&(*philos)->philo_mutex);
		free(*philos);
		*philos = tmp;
	}
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->death_mutex);
	free((*philos)->info);
	*philos = NULL;
}
