/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/17 14:20:06 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void *arg)
{
	void	**args;
	t_info	*info;
	t_philo	*philo;

	info = (t_info *)args[0];
	philo = (t_philo *)args[1];
	return (NULL);
}

void	ft_run_threads(t_info *info)
{
	int			i;
	void		*args[2];
	t_philo		*philo;

	i = 0;
	philo = info->philos;
	while (i < info->n_philos)
	{
		args[0] = info;
		args[1] = philo;
		if (pthread_create(&(philo->id_t), NULL, &ft_philo, args) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		philo = philo->right;
		i++;
	}
	while (i--)
	{
		pthread_join(philo->id_t, NULL);
		philo = philo->right;
	}
}
