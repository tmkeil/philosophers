/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:08:41 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 20:04:59 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_death(t_philos *philo)
{
	bool	finished;

	pthread_mutex_lock(&philo->info->death_mutex);
	finished = philo->info->finished;
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (finished);
}

void	ft_grab_forks(t_philos *philo, int id)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		ft_log(philo->info, ft_time(philo), FORK, id);
		pthread_mutex_lock(philo->fork_r);
		ft_log(philo->info, ft_time(philo), FORK, id);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		ft_log(philo->info, ft_time(philo), FORK, id);
		pthread_mutex_lock(philo->fork_l);
		ft_log(philo->info, ft_time(philo), FORK, id);
	}
}

void	ft_release_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
}
