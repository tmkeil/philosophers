/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:00:32 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/25 16:36:55 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(time_t msec, t_philos *philo)
{
    struct timeval	start;
	struct timeval	current;
    gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		if (ft_death(philo))
			return (0);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000 >= msec)
			break ;
	}
	return (1);
}

time_t	ft_gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}
