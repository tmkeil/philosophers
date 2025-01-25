/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/25 22:20:19 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->died)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	philo->info->died = (philo->info->time_to_die <= ft_gettime() - philo->last_eaten);
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (philo->info->died);
}

void	ft_release_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	ft_grab_forks(t_philos **philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if ((*philo)->id % 2 == 0)
	{
		first_fork = (*philo)->fork_l;
		second_fork = (*philo)->fork_r;
	}
	else
	{
		first_fork = (*philo)->fork_r;
		second_fork = (*philo)->fork_l;
	}
	pthread_mutex_lock(first_fork);
	ft_log((*philo)->info, ft_gettime(), FORK, (*philo)->id);
	if (ft_death(*philo))
		return (0);
	pthread_mutex_lock(second_fork);
	ft_log((*philo)->info, ft_gettime(), FORK, (*philo)->id);
	if (ft_death(*philo))
		return (0);
	return (1);
}

int	ft_eat(t_philos **philo, t_info *info)
{
	if (!ft_grab_forks(philo))
		return (ft_release_forks(*philo), 0);
	ft_log(info, ft_gettime(), EATING, (*philo)->id);
	pthread_mutex_lock(&(*philo)->philo_mutex);
	(*philo)->last_eaten = ft_gettime();
	(*philo)->n_eaten++;
	pthread_mutex_unlock(&(*philo)->philo_mutex);
	if (!ft_sleep(info->time_to_eat, *philo))
		return (ft_release_forks(*philo), 0);
	printf("time nach dem essen: %li\n", ft_gettime());
	if (ft_death(*philo))
		return (ft_release_forks(*philo), 0);
	ft_release_forks(*philo);
	if (ft_death(*philo))
		return (0);
	return (1);
}

void	*ft_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *) arg;
	pthread_mutex_lock(&philo->philo_mutex);
	philo->start_time = ft_gettime();
	philo->last_eaten = philo->start_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	// printf("philo nbr: %i\n", philo->id);
	while (!ft_death(philo))
	{
		// printf("philo nbr: %i schleife\n", philo->id);
		if (!ft_eat(&philo, philo->info))
			return (NULL);
		ft_log(philo->info, ft_gettime(), SLEEPING, philo->id);
		ft_sleep(philo->info->time_to_sleep, philo);
		ft_log(philo->info, ft_gettime(), THINKING, philo->id);
	}
	return (NULL);
}

void	ft_run_threads(t_philos **philos)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = *philos;
	while (i < (*philos)->info->n_philos)
	{
		if (pthread_create(&(philo->id_t), NULL, &ft_philo, philo) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		philo = philo->right;
		i++;
	}
	while (i--)
	{
		pthread_join(philo->id_t, NULL);
		philo = philo->right;
	}
}
