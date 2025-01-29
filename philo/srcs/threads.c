/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 22:38:06 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_one_philo(t_philos *philo, int id)
{
	int		number;
	time_t	dying_time;

	pthread_mutex_lock(&philo->info->info_mutex);
	number = philo->info->n_philos;
	dying_time = philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->info_mutex);
	if (number == 1)
	{
		ft_log(philo->info, ft_time(philo), FORK, id);
		ft_sleep(dying_time, philo);
		return (1);
	}
	return (0);
}

static void	*ft_philo(void *arg)
{
	int			id;
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->philo_mutex);
	id = philo->id;
	philo->start_philo = ft_time(philo);
	philo->last_eaten = ft_time(philo);
	pthread_mutex_unlock(&philo->philo_mutex);
	if (ft_one_philo(philo, id))
		return (NULL);
	if (id % 2 == 0)
		usleep(500);
	while (!ft_death(philo))
	{
		ft_think(philo, id);
		ft_grab_forks(philo, id);
		ft_eat(philo, philo->info, id);
		ft_release_forks(philo->fork_l, philo->fork_r);
		ft_nap(philo, id);
	}
	return (NULL);
}

static int	ft_start_threads(t_philos *philo, int *number_of_philos)
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

static int	ft_join_threads(t_philos *philo, int number_of_philos,
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

void	ft_run_threads(t_philos *philo)
{
	int			number_of_philos;
	pthread_t	controller;

	if (pthread_create(&controller, NULL, &ft_control, philo) != SUCCESS)
		return ;
	if (ft_start_threads(philo, &number_of_philos) != SUCCESS)
		return ;
	if (ft_join_threads(philo, number_of_philos, controller) != SUCCESS)
		return ;
}
