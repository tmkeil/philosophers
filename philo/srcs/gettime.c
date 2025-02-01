/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:00:32 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 18:58:59 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(time_t msec, t_philos *philo)
{
	struct timeval	start_philo;
	struct timeval	current;

	gettimeofday(&start_philo, NULL);
	while (!ft_death(philo))
	{
		usleep(500);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start_philo.tv_sec) * 1000 + (current.tv_usec
				- start_philo.tv_usec) / 1000 > msec)
			break ;
	}
}

time_t	ft_time(time_t start)
{
	time_t			current;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	current = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (current - start);
}

time_t	ft_timestamp(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}
