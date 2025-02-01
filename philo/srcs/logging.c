/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:15:11 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 22:02:12 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_write_log(time_t time, int action, int id, t_info *info)
{
	(void) info;
	if (action == FORK)
		printf("%li %i has taken a fork\n", time, id);
	else if (action == EATING)
		printf("%li %i is eating\n", time, id);
	else if (action == SLEEPING)
		printf("%li %i is sleeping\n", time, id);
	else if (action == THINKING)
		printf("%li %i is thinking\n", time, id);
	else if (action == DIED)
		printf("%li %i died\n", time, id);
}

void	ft_log(t_info *info, time_t time, int act, int id)
{
	bool	finished;

	pthread_mutex_lock(&info->info_mutex);
	finished = info->finished;
	pthread_mutex_unlock(&info->info_mutex);
	if (finished)
		return ;
	ft_write_log(time, act, id, info);
}
