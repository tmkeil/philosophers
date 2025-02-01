/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:28:04 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 18:57:26 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_destroy_forks(t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
		pthread_mutex_destroy(&forks[i++]);
}

void	ft_clear_data(t_philos **philos)
{
	int			i;
	t_info		*info;

	if (!philos || !*philos)
		return ;
	i = 0;
	info = (*philos)[0].info;
	while (i < (*philos)->info->n_philos)
	{
		pthread_mutex_destroy(&(*philos)[i].philo_mutex);
		i++;
	}
	ft_destroy_forks(info, info->forks);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->death_mutex);
	pthread_mutex_destroy(&info->info_mutex);
	free(info);
	info = NULL;
	free(*philos);
	*philos = NULL;
}
