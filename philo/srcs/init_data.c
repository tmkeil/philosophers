/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 22:42:23 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_new_philo(t_info *info, t_philos **new, int i)
{
	*new = malloc(sizeof(t_philos));
	if (!*new)
		return (FAIL);
	(*new)->id = i;
	(*new)->left = NULL;
	(*new)->right = NULL;
	(*new)->n_eaten = 0;
	(*new)->info = info;
	(*new)->is_eating = false;
	(*new)->last_eaten = 0;
	(*new)->fork_l = NULL;
	(*new)->fork_r = NULL;
	pthread_mutex_init(&(*new)->philo_mutex, NULL);
	return (SUCCESS);
}

static int	ft_append_new_philo(t_philos **philos, t_philos *new, bool is_last)
{
	t_philos	*tmp;

	if (!philos || !new)
		return (FAIL);
	if (!*philos)
	{
		*philos = new;
		return (SUCCESS);
	}
	tmp = *philos;
	while (tmp->right)
		tmp = tmp->right;
	if (!is_last)
	{
		new->left = tmp;
		tmp->right = new;
	}
	else
	{
		new->left = tmp;
		new->right = *philos;
		(*philos)->left = new;
		tmp->right = new;
	}
	return (SUCCESS);
}

static int	ft_init_info(t_info **info, char **argv)
{
	int	params[5];

	*info = malloc(sizeof(t_info));
	if (!*info)
		return (FAIL);
	if (ft_parse_parameters(params, sizeof(params) / sizeof(params[0]),
			argv) != SUCCESS)
		return (FAIL);
	(*info)->start_programm = ft_timestamp();
	(*info)->finished = false;
	(*info)->n_philos = params[0];
	(*info)->n_to_eat = params[4];
	(*info)->time_to_die = (time_t)params[1];
	(*info)->time_to_eat = (time_t)params[2];
	(*info)->time_to_sleep = (time_t)params[3];
	pthread_mutex_init(&(*info)->print_mutex, NULL);
	pthread_mutex_init(&(*info)->death_mutex, NULL);
	pthread_mutex_init(&(*info)->info_mutex, NULL);
	return (SUCCESS);
}

static int	ft_assign_forks_to_philos(t_philos **philos, t_info *info)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = *philos;
	while (i < info->n_philos)
	{
		philo->fork_l = malloc(sizeof(pthread_mutex_t));
		if (!philo->fork_l)
			return (FAIL);
		pthread_mutex_init(philo->fork_l, NULL);
		if (info->n_philos == 1)
		{
			philo->fork_r = philo->fork_l;
			return (SUCCESS);
		}
		philo = philo->right;
		i++;
	}
	while (i--)
	{
		philo->fork_r = philo->right->fork_l;
		philo = philo->right;
	}
	return (SUCCESS);
}

int	ft_init_data(t_philos **philos, char **argv)
{
	int			i;
	t_info		*info;
	t_philos	*new;

	i = 0;
	new = NULL;
	*philos = NULL;
	if (ft_init_info(&info, argv) != SUCCESS)
		return (FAIL);
	while (i < info->n_philos)
	{
		if (ft_init_new_philo(info, &new, i) != SUCCESS)
			return (ft_clear_philos(philos, (*philos)->info->n_philos), FAIL);
		if (ft_append_new_philo(philos, new, i == info->n_philos
				- 1) != SUCCESS)
			return (ft_clear_philos(philos, (*philos)->info->n_philos), FAIL);
		i++;
	}
	if (ft_assign_forks_to_philos(philos, info) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
