/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:55:44 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/27 19:01:59 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_starved(t_philos *philo, t_info *info)
{
	time_t	fasting;

	pthread_mutex_lock(&philo->philo_mutex);
	;
	fasting = ft_time() - philo->last_eaten;
	// printf("philo %i is fasting %li\n", philo->id, fasting);
	if (philo->last_eaten && !philo->is_eating && fasting >= info->time_to_die)
	{
		ft_log(info, ft_time(), DIED, philo->id);
		return (pthread_mutex_unlock(&philo->philo_mutex), 1);
	}
	return (pthread_mutex_unlock(&philo->philo_mutex), 0);
}

static int	ft_is_finished(t_philos *philo, int n)
{
	int		i;
	int		count;
	t_info	*info;

	i = 0;
	count = 0;
	info = philo->info;
	while (i++ < n)
	{
		if (ft_starved(philo, info))
			return (1);
		pthread_mutex_lock(&philo->philo_mutex);
		;
		if (philo->n_eaten >= info->n_to_eat && info->n_to_eat > 0)
			count++;
		pthread_mutex_unlock(&philo->philo_mutex);
		philo = philo->right;
	}
	if (count == n)
		return (1);
	return (0);
}

void	*ft_observer(void *arg)
{
	int			n_philos;
	t_philos	*philos;

	philos = (t_philos *)arg;
	n_philos = philos->info->n_philos;
	while (1)
	{
		// // test
		// ft_log(philos->info, ft_time(), 6, philos->id);
		// // test
		if (ft_is_finished(philos, n_philos))
		{
			// ft_log(philos->info, ft_time(), 8, philos->id);
			pthread_mutex_lock(&philos->info->death_mutex);
			;
			philos->info->finished = true;
			pthread_mutex_unlock(&philos->info->death_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
