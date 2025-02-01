/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:06:43 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 22:01:56 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philos *philo, t_info *info, int id, t_philo_vars vars)
{
	// pthread_mutex_lock(&philo->philo_mutex);
	// philo->is_eating = true;
	// pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = ft_time(vars.start);
	philo->n_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&info->print_mutex);
	ft_log(info, ft_time(vars.start), EATING, id);
	pthread_mutex_unlock(&info->print_mutex);
	ft_sleep(vars.time_to_eat, philo);
}

void	ft_nap(t_philos *philo, int id, t_philo_vars vars)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	ft_log(philo->info, ft_time(vars.start), SLEEPING, id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	ft_sleep(vars.time_to_sleep, philo);
}

void	ft_think(t_philos *philo, int id, time_t start)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	ft_log(philo->info, ft_time(start), THINKING, id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
