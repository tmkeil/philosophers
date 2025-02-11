/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:06:43 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/02 14:09:59 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philos *philo, t_info *info, int id, t_philo_vars vars)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = ft_time(vars.start);
	philo->n_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_log(info, vars.start, EATING, id);
	ft_sleep(vars.time_to_eat, philo);
}

void	ft_nap(t_philos *philo, int id, t_philo_vars vars)
{
	ft_log(philo->info, vars.start, SLEEPING, id);
	ft_sleep(vars.time_to_sleep, philo);
}

void	ft_think(t_philos *philo, int id, time_t start)
{
	ft_log(philo->info, start, THINKING, id);
}
