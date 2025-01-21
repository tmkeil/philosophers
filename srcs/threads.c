/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/21 02:48:33 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_wait_for_forks(t_philo *philo, t_info *info)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_trylock(philo->fork_l) == 0)
			printf("fork %p was locked at philo %p\n", philo->fork_l, philo);
		else
			printf("fork %p could not get locked at philo %p\n", philo->fork_l, philo);
		ft_log(info, ft_gettime(), FORK, philo->id);
		if (pthread_mutex_trylock(philo->fork_r) == 0)
			printf("fork %p was locked at philo %p\n", philo->fork_r, philo);
		else
			printf("fork %p was locked at philo %p\n", philo->fork_r, philo);
		ft_log(info, ft_gettime(), FORK, philo->id);
	}
	else
	{
		if (pthread_mutex_trylock(philo->fork_r) == 0)
			printf("fork %p was locked at philo %p\n", philo->fork_r, philo);
		else
			printf("fork %p could not get locked at philo %p\n", philo->fork_r, philo);
		ft_log(info, ft_gettime(), FORK, philo->id);
		if (pthread_mutex_trylock(philo->fork_l) == 0)
			printf("fork %p was locked at philo %p\n", philo->fork_l, philo);
		else
			printf("fork %p could not get locked at philo %p\n", philo->fork_l, philo);
		ft_log(info, ft_gettime(), FORK, philo->id);
	}
}

void	ft_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	ft_check_death(t_philo *philo, t_info *info)
{
	return (info->time_to_die <= ft_gettime() - philo->last_eaten);
}

void	*ft_philo(void *arg)
{
	void	**args;
	t_info	*info;
	t_philo	*philo;

	args = (void **)arg;
	info = (t_info *)args[0];
	philo = (t_philo *)args[1];
	// printf("info->start = %li\n", info->start);
	// printf("info->n_pilos = %i\n", info->n_philos);
	// printf("info->time_to_die = %li\n", info->time_to_die);
	// printf("info->time_to_eat = %li\n", info->time_to_eat);
	// printf("info->time_to_sleep = %li\n", info->time_to_sleep);
	// printf("info->n_to_eat = %i\n\n", info->n_to_eat);
	while (!ft_check_death(philo, info))
	{
		ft_wait_for_forks(philo, info);
		ft_log(info, ft_gettime(), EATING, philo->id);
		usleep(info->time_to_eat * 1000);
		philo->last_eaten = ft_gettime();
		ft_unlock_forks(philo);
		ft_log(info, ft_gettime(), SLEEPING, philo->id);
		usleep(info->time_to_sleep * 1000);
		ft_log(info, ft_gettime(), THINKING, philo->id);
	}
	return (NULL);
}

void	ft_run_threads(t_info **info)
{
	int			i;
	void		*args[2];
	t_philo		*philo;

	i = 0;
	philo = (*info)->philos;
	while (i < (*info)->n_philos)
	{
		args[0] = (*info);
		args[1] = philo;
		if (pthread_create(&(philo->id_t), NULL, &ft_philo, args) != 0)
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
