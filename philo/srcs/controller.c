/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:55:44 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/30 16:23:35 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_dead_eaten_enough(t_philos *philo, t_control_vars vars, int *eaten)
{
	int		id;
	int		number;
	bool	eating;
	time_t	fasting;

	pthread_mutex_lock(&philo->philo_mutex);
	id = philo->id;
	number = philo->n_eaten;
	eating = philo->is_eating;
	fasting = ft_time(vars.start) - philo->last_eaten;
	pthread_mutex_unlock(&philo->philo_mutex);
	// printf("last_eaten = %li und start = %li\n", philo->last_eaten, vars.start);
	if (!eating && fasting > vars.time_to_die)
	{
		printf("last_eaten = %li und start = %li\n", philo->last_eaten, vars.start);
		ft_log(philo->info, ft_time(vars.start), DIED, id);
		return (1);
	}
	if (number >= vars.n_to_eat && vars.n_to_eat != -1)
		(*eaten)++;
	if ((*eaten) == vars.n_philos)
		return (1);
	return (0);
}

static void	ft_reset_n_sleep(int *n, int *eaten, int number_of_philos)
{
	if ((*n) == number_of_philos)
	{
		(*n) = 0;
		(*eaten) = 0;
		usleep(1000);
	}
}

void	ft_init_vars(t_control_vars *vars, t_philos **philo, void *arg)
{
	(*philo) = (t_philos *)arg;
	pthread_mutex_lock(&(*philo)->info->info_mutex);
	vars->start = (*philo)->info->start_programm;
	vars->n_to_eat = (*philo)->info->n_to_eat;
	vars->n_philos = (*philo)->info->n_philos;
	pthread_mutex_unlock(&(*philo)->info->info_mutex);
}

void	*ft_control(void *arg)
{
	int				n;
	int				eaten;
	t_philos		*philo;
	t_control_vars	vars;

	ft_init_vars(&vars, &philo, arg);
	eaten = 0;
	n = 0;
	while (1)
	{
		if (ft_is_dead_eaten_enough(philo, vars, &eaten))
			break ;
		n++;
		philo = philo->right;
		ft_reset_n_sleep(&n, &eaten, vars.n_philos);
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->info->finished = true;
	return (pthread_mutex_unlock(&philo->info->death_mutex), NULL);
}
