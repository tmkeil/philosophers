/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:06:43 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/30 15:13:01 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philos *philo, t_info *info, int id, time_t start)
{
	time_t	eating_time;

	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->info->info_mutex);
	eating_time = philo->info->time_to_eat;
	pthread_mutex_unlock(&philo->info->info_mutex);
	ft_log(info, ft_time(start), EATING, id);
	ft_sleep(eating_time, philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = ft_timestamp();
	philo->n_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	ft_nap(t_philos *philo, int id, time_t start)
{
	time_t	sleeping_time;

	pthread_mutex_lock(&philo->info->info_mutex);
	sleeping_time = philo->info->time_to_sleep;
	pthread_mutex_unlock(&philo->info->info_mutex);
	ft_log(philo->info, ft_time(start), SLEEPING, id);
	ft_sleep(sleeping_time, philo);
}

void	ft_think(t_philos *philo, int id, time_t start)
{
	ft_log(philo->info, ft_time(start), THINKING, id);
}
