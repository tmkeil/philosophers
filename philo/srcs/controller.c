/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:55:44 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 22:04:35 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_dead_eaten_enough(t_philos *philo, t_control_vars vars,
		int *eaten)
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
	if (!eating && fasting > vars.time_to_die)
	{
		ft_log(philo->info, ft_time(vars.start), DIED, id);
		return (1);
	}
	if (number >= vars.n_to_eat && vars.n_to_eat != -1)
		(*eaten)++;
	if ((*eaten) == vars.n_philos)
		return (1);
	return (0);
}

void	ft_init_vars(t_control_vars *vars, t_philos **philo, void *arg)
{
	(*philo) = (t_philos *)arg;
	pthread_mutex_lock(&(*philo)[0].info->info_mutex);
	vars->start = (*philo)[0].info->start_programm;
	vars->n_to_eat = (*philo)[0].info->n_to_eat;
	vars->n_philos = (*philo)[0].info->n_philos;
	vars->time_to_die = (*philo)[0].info->time_to_die;
	pthread_mutex_unlock(&(*philo)[0].info->info_mutex);
}

void	*ft_control(void *arg)
{
	int				i;
	int				eaten;
	t_philos		*philo;
	t_control_vars	vars;

	ft_init_vars(&vars, &philo, arg);
	eaten = 0;
	i = 0;
	while (1)
	{
		if (ft_is_dead_eaten_enough(&philo[i], vars, &eaten))
			break ;
		i++;
		if (i == vars.n_philos)
		{
			i = 0;
			eaten = 0;
		}
	}
	pthread_mutex_lock(&philo->info->info_mutex);
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->info->finished = true;
	pthread_mutex_unlock(&philo->info->death_mutex);
	pthread_mutex_unlock(&philo->info->info_mutex);
	return (NULL);
}
