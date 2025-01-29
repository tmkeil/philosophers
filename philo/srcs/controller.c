/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:55:44 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 22:41:39 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_dead(t_philos *philo)
{
	int		id;
	bool	eating;
	time_t	fasting;
	time_t	last_meal;
	time_t	time_to_die;

	pthread_mutex_lock(&philo->philo_mutex);
	id = philo->id;
	fasting = ft_time(philo) - philo->last_eaten;
	last_meal = philo->last_eaten;
	eating = philo->is_eating;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->info->info_mutex);
	time_to_die = philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->info_mutex);
	if (last_meal && !eating && fasting >= time_to_die)
		return (ft_log(philo->info, ft_time(philo), DIED, id), 1);
	return (0);
}

int	ft_reset_n_sleep(int *n, int *eaten, t_philos *philo)
{
	int	number_of_philos;

	pthread_mutex_lock(&philo->info->info_mutex);
	number_of_philos = philo->info->n_philos;
	pthread_mutex_unlock(&philo->info->info_mutex);
	if (*eaten == number_of_philos)
		return (1);
	if (*n == number_of_philos)
	{
		*n = 0;
		*eaten = 0;
		usleep(1000);
	}
	return (0);
}

static int	ft_eaten_enough(t_philos *philo)
{
	int	number;
	int	n_to_eat;

	pthread_mutex_lock(&philo->philo_mutex);
	number = philo->n_eaten;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->info->info_mutex);
	n_to_eat = philo->info->n_to_eat;
	pthread_mutex_unlock(&philo->info->info_mutex);
	if (number >= n_to_eat && n_to_eat != -1)
		return (1);
	return (0);
}

void	*ft_eaten_a_lot(t_philos *philo, int *eaten)
{
	if (ft_eaten_enough(philo))
		(*eaten)++;
	return (NULL);
}

void	*ft_control(void *arg)
{
	int			n;
	int			eaten;
	t_philos	*philo;

	philo = (t_philos *)arg;
	eaten = 0;
	n = 0;
	while (1)
	{
		if (ft_is_dead(philo) || ft_eaten_a_lot(philo, &eaten))
			break ;
		n++;
		philo = philo->right;
		if (ft_reset_n_sleep(&n, &eaten, philo))
			break ;
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->info->finished = true;
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (NULL);
}
