/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:00:32 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/28 14:39:11 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(time_t msec)
{
    struct timeval	start;
	struct timeval	current;

    gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000 >= msec)
			break ;
	}
}

time_t	ft_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}
