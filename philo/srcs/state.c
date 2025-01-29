/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:06:43 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 16:07:54 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philos *philo, t_info *info)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_log(info, ft_time(), EATING, philo->id);
	ft_sleep(info->time_to_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = ft_time();
	philo->n_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	ft_nap(t_philos *philo)
{
	ft_log(philo->info, ft_time(), SLEEPING, philo->id);
	ft_sleep(philo->info->time_to_sleep);
}

void	ft_think(t_philos *philo)
{
	time_t	think_time;

	think_time = (philo->info->time_to_die - (philo->info->time_to_eat
				+ philo->info->time_to_sleep)) / philo->info->n_philos;
	ft_log(philo->info, ft_time(), THINKING, philo->id);
	ft_sleep(think_time);
}
