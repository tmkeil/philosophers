/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/02 14:08:23 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_info(t_info **info, char **argv)
{
	int		params[5];
	time_t	time;

	*info = malloc(sizeof(t_info));
	if (!*info)
		return (printf("error malloc\n"), FAIL);
	if (ft_get_params(params, sizeof(params) / sizeof(params[0]),
			argv) != SUCCESS)
		return (FAIL);
	time = ft_timestamp();
	if (time == -1)
		return (printf("error getting time\n"), FAIL);
	ft_assign_values(info, params, time);
	if (pthread_mutex_init(&(*info)->print_mutex, NULL) != SUCCESS)
		return (printf("error init mutex\n"), FAIL);
	if (pthread_mutex_init(&(*info)->death_mutex, NULL) != SUCCESS)
		return (printf("error init mutex\n"), ft_destroy_mutexes(info, 1),
			FAIL);
	if (pthread_mutex_init(&(*info)->info_mutex, NULL) != SUCCESS)
		return (printf("error init mutex\n"), ft_destroy_mutexes(info, 2),
			FAIL);
	return (SUCCESS);
}

static int	ft_init_philos(t_info *info, t_philos **philos,
		pthread_mutex_t *forks)
{
	int	i;

	(*philos) = malloc(sizeof(t_philos) * info->n_philos);
	if (!(*philos))
		return (printf("error malloc\n"), FAIL);
	i = 0;
	while (i < info->n_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].info = info;
		(*philos)[i].n_eaten = 0;
		(*philos)[i].last_eaten = 0;
		(*philos)[i].fork_l = &forks[i];
		(*philos)[i].fork_r = &forks[(i + 1) % info->n_philos];
		if (pthread_mutex_init(&(*philos)[i].philo_mutex, NULL) != SUCCESS)
		{
			while (i--)
				pthread_mutex_destroy(&(*philos)[i].philo_mutex);
			return (printf("error init mutex\n"), FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_init_forks(t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != SUCCESS)
		{
			while (i--)
				pthread_mutex_destroy(&forks[i]);
			return (printf("error init mutex\n"), FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_init_data(t_philos **philos, char **argv)
{
	t_info	*info;

	info = NULL;
	*philos = NULL;
	if (ft_init_info(&info, argv) != SUCCESS)
		return (free(info), info = NULL, FAIL);
	if (ft_init_forks(info, info->forks) != SUCCESS)
	{
		ft_destroy_mutexes(&info, 3);
		return (free(info), info = NULL, FAIL);
	}
	if (ft_init_philos(info, philos, info->forks) != SUCCESS)
	{
		ft_destroy_mutexes(&info, 3);
		ft_destroy_forks(info, info->forks);
		free(*philos);
		philos = NULL;
		return (free(info), info = NULL, FAIL);
	}
	return (SUCCESS);
}
