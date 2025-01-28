/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/27 19:01:38 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_death(t_philos *philo)
{
	bool	dead;

	pthread_mutex_lock(&philo->info->death_mutex);
	dead = philo->info->finished;
	pthread_mutex_unlock(&info->death_mutex);
	return (dead);
}

static void	ft_grab_forks(t_philos *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->fork_l * (philo->id % 2 == 0) + philo->fork_r * (philo->id % 2 != 0);
	second = philo->fork_r * (philo->id % 2 == 0) + philo->fork_l * (philo->id % 2 != 0)
	pthread_mutex_lock(first);
	ft_log(philo->info, ft_time(), FORK, philo->id);
	pthread_mutex_lock(second);
	ft_log(philo->info, ft_time(), FORK, philo->id);
}

static void	ft_eat(t_philos *philo, t_info *info)
{
	ft_grab_forks(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	// philo->is_eating = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_log(info, ft_time(), EATING, philo->id);
	ft_sleep(info->time_to_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = ft_time();
	philo->n_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

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
		// printf("philo id %i before eating\n", philo->id);
		ft_eat(philo, philo->info);
		// printf("philo id: %i after eaten check: last eaten: %li nbr eaten: %i\n", philo->id, philo->last_eaten, philo->n_eaten);
		ft_log(philo->info, ft_time(), SLEEPING, philo->id);
		ft_sleep(philo->info->time_to_sleep);
		ft_log(philo->info, ft_time(), THINKING, philo->id);
	}
	return (NULL);
}

void	ft_run_threads(t_philos **philos)
{
	int			i;
	t_philos	*philo;
	pthread_t	observer;

	i = 0;
	philo = *philos;
	if (pthread_create(&observer, NULL, &ft_observer, philo) != SUCCESS)
		return ;
	while (i < (*philos)->info->n_philos)
	{
		if (pthread_create(&philo->id_t, NULL, &ft_philo, philo) != SUCCESS)
			return ;
		philo = philo->right;
		i++;
	}
	if (pthread_join(philo->id_t, NULL) != SUCCESS)
		return ;
	while (i--)
	{
		if (pthread_join(philo->id_t, NULL) != SUCCESS)
			return ;
		philo = philo->right;
	}
}
