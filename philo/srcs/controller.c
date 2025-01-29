/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:55:44 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 16:13:01 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_dead(t_philos *philo)
{
	bool	eating;
	time_t	fasting;
	time_t	last_meal;

	pthread_mutex_lock(&philo->philo_mutex);
	fasting = ft_time() - philo->last_eaten;
	last_meal = philo->last_eaten;
	eating = philo->is_eating;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (last_meal && !eating && fasting >= philo->info->time_to_die)
	{
		ft_log(philo->info, ft_time(), DIED, philo->id);
		return (1);
	}
	return (0);
}

static int	ft_eaten_enough(t_philos *philo)
{
	int	number;

	number = 0;
	pthread_mutex_lock(&philo->philo_mutex);
	number = philo->n_eaten;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (number >= philo->info->n_to_eat && philo->info->n_to_eat != -1)
		return (1);
	return (0);
}

void	*ft_control(void *arg)
{
	int			n;
	int			eaten;
	t_philos	*philo;

	philo = (t_philos *)arg;
	n = philo->info->n_philos;
	eaten = 0;
	while (1)
	{
		if (n-- == 0)
			usleep(1000);
		if (ft_is_dead(philo))
			break ;
		if (ft_eaten_enough(philo))
			eaten++;
		if (eaten == philo->info->n_philos)
			break ;
		philo = philo->right;
		eaten = eaten * (n != 0);
		n = philo->info->n_philos * (n == 0) + n * (n != 0);
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->info->finished = true;
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (NULL);
}
