/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/21 18:51:27 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo **philo, t_info *info)
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
	ft_log(info, ft_gettime(), FORK, (*philo)->id);
	pthread_mutex_lock(second_fork);
	ft_log(info, ft_gettime(), FORK, (*philo)->id);
	ft_log(info, ft_gettime(), EATING, (*philo)->id);
	ft_sleep(info->time_to_eat * 1000);
	pthread_mutex_lock(&(*philo)->eat_mutex);
	(*philo)->last_eaten = ft_gettime();
	pthread_mutex_unlock(&(*philo)->eat_mutex);
}

void	ft_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	ft_check_death(t_philo *philo, t_info *info)
{
	bool	dead;
	pthread_mutex_lock(&info->death_mutex);
	dead = (info->time_to_die <= ft_gettime() - philo->last_eaten);
	pthread_mutex_unlock(&info->death_mutex);
	return (dead);
}

void	*ft_philo(void *arg)
{
	void	**args;
	t_info	*info;
	t_philo	*philo;

	args = (void **)arg;
	info = (t_info *)args[0];
	philo = (t_philo *)args[1];
	pthread_mutex_lock(&philo->eat_mutex);
	printf("philo id = %i\n", philo->id);
	pthread_mutex_unlock(&philo->eat_mutex);
	philo->start_time = ft_gettime();
	philo->last_eaten = philo->start_time;
	while (!ft_check_death(philo, info))
	{
		ft_eat(&philo, info);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->n_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
		ft_unlock_forks(philo);
		ft_log(info, ft_gettime(), SLEEPING, philo->id);
		ft_sleep(info->time_to_sleep * 1000);
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
