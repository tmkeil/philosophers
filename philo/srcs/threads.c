/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/30 16:42:10 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_one_philo(t_philos *philo, int id, t_philo_vars vars)
{
	if (vars.n_philos == 1)
	{
		ft_log(philo->info, ft_time(vars.start), FORK, id);
		while (1)
		{
			if (ft_death(philo))
				return (1);
		}
	}
	return (0);
}

void	ft_init_philo_vars(t_philo_vars *vars, t_philos **philo, void *arg)
{
	*philo = (t_philos *) arg;
	pthread_mutex_lock(&(*philo)->info->info_mutex);
	vars->n_philos = (*philo)->info->n_philos;
	vars->start = (*philo)->info->start_programm;
	vars->time_to_eat = (*philo)->info->time_to_eat;
	vars->time_to_sleep = (*philo)->info->time_to_sleep;
	pthread_mutex_unlock(&(*philo)->info->info_mutex);
	vars->id = (*philo)->id;
	
}

void	*ft_philo(void *arg)
{
	int				id;
	t_philos		*philo;
	t_philo_vars	vars;

	ft_init_philo_vars(&vars, &philo, arg);
	pthread_mutex_lock(&philo->philo_mutex);
	id = philo->id;
	philo->last_eaten = ft_timestamp();
	pthread_mutex_unlock(&philo->philo_mutex);
	if (ft_one_philo(philo, id, vars))
		return (NULL);
	if (id % 2 == 0)
		usleep(50);
	while (!ft_death(philo))
	{
		ft_think(philo, id, vars.start);
		ft_grab_forks(philo, id, vars.start);
		ft_eat(philo, philo->info, id, vars.start);
		ft_release_forks(philo->fork_l, philo->fork_r);
		ft_nap(philo, id, vars.start);
	}
	return (NULL);
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
