/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:08:41 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/30 14:18:56 by tkeil            ###   ########.fr       */
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

void	ft_grab_forks(t_philos *philo, int id, time_t start)
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
	ft_log(philo->info, ft_time(start), FORK, id);
	pthread_mutex_lock(second);
	ft_log(philo->info, ft_time(start), FORK, id);
}

void	ft_release_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
}

int	ft_start_threads(t_philos *philo, int *number_of_philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->info->info_mutex);
	*number_of_philos = philo->info->n_philos;
	pthread_mutex_unlock(&philo->info->info_mutex);
	while (i++ < *number_of_philos)
	{
		if (pthread_create(&philo->id_t, NULL, &ft_philo, philo) != SUCCESS)
			return (FAIL);
		if (*number_of_philos > 1)
			philo = philo->right;
	}
	return (SUCCESS);
}

int	ft_join_threads(t_philos *philo, int number_of_philos,
		pthread_t controller)
{
	int	n;

	n = number_of_philos;
	if (pthread_join(controller, NULL) != SUCCESS)
		return (FAIL);
	while (n--)
	{
		if (pthread_join(philo->id_t, NULL) != SUCCESS)
			return (FAIL);
		if (number_of_philos > 1)
			philo = philo->right;
	}
	return (SUCCESS);
}
