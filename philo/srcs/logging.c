/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:15:11 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 15:37:41 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_write_log(time_t time, int action, int id, t_info *info)
{
	char	*s_id;
	char	*s_time;

	s_id = ft_ltoa((long)id);
	s_time = ft_ltoa(time);
	pthread_mutex_lock(&info->print_mutex);
	ft_putstr_fd(s_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(s_id, 1);
	if (action == 0)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (action == 1)
		ft_putstr_fd(" is eating\n", 1);
	else if (action == 2)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (action == 3)
		ft_putstr_fd(" is thinking\n", 1);
	else if (action == 4)
		ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(&info->print_mutex);
	free(s_id);
	free(s_time);
}

void	ft_log(t_info *info, time_t time, int act, int id)
{
	ft_write_log(time, act, id, info);
}
