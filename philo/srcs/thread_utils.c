/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:08:41 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 16:09:37 by tkeil            ###   ########.fr       */
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

void	ft_grab_forks(t_philos *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->fork_l;
		second = philo->fork_r;
	}
	else
	{
		first = philo->fork_r;
		second = philo->fork_l;
	}
	pthread_mutex_lock(first);
	ft_log(philo->info, ft_time(), FORK, philo->id);
	pthread_mutex_lock(second);
	ft_log(philo->info, ft_time(), FORK, philo->id);
}

void	ft_release_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
}
