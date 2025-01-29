/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 16:08:25 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->philo_mutex);
	philo->start_time = ft_time();
	philo->last_eaten = philo->start_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	while (!ft_death(philo))
	{
		if (philo->info->n_philos == 1)
		{
			ft_log(philo->info, ft_time(), FORK, philo->id);
			ft_sleep(philo->info->time_to_die);
			return (NULL);
		}
		ft_grab_forks(philo);
		ft_eat(philo, philo->info);
		ft_release_forks(philo->fork_l, philo->fork_r);
		ft_nap(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_run_threads(t_philos **philos)
{
	int			i;
	t_philos	*philo;
	pthread_t	controller;

	i = 0;
	philo = *philos;
	if (pthread_create(&controller, NULL, &ft_control, philo) != SUCCESS)
		return ;
	while (i++ < (*philos)->info->n_philos)
	{
		if (pthread_create(&philo->id_t, NULL, &ft_philo, philo) != SUCCESS)
			return ;
		if ((*philos)->info->n_philos > 1)
			philo = philo->right;
	}
	if (pthread_join(philo->id_t, NULL) != SUCCESS)
		return ;
	while (i--)
	{
		if (pthread_join(philo->id_t, NULL) != SUCCESS)
			return ;
		if ((*philos)->info->n_philos > 1)
			philo = philo->right;
	}
}
