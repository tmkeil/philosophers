/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:15:11 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/16 19:31:08 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_write_log(time_t time, int action, int id, int fd)
{
	char	*s_id;
	char	*s_time;

	s_id = ft_ltoa((long)id);
	s_time = ft_ltoa(time);
	ft_putstr_fd(s_time, fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(s_id, fd);
	if (action == 0)
		ft_putstr_fd(" has taken a fork\n", fd);
	else if (action == 1)
		ft_putstr_fd(" is eating\n", fd);
	else if (action == 2)
		ft_putstr_fd(" is sleeping\n", fd);
	else if (action == 3)
		ft_putstr_fd(" is thinking\n", fd);
	else if (action == 4)
		ft_putstr_fd(" died\n", fd);
	free(s_id);
	free(s_time);
}

void	ft_log(t_info *info, time_t time, int act, int id)
{
	int	fd;

	fd = open("logs.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open logs.txt");
		ft_clear_philos(&(info->philos), info->n_philos);
		exit(EXIT_FAILURE);
	}
	ft_write_log(time, act, id, fd);
	close(fd);
}
