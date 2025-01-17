/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/17 14:06:07 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_init_new_philo(t_philo **new, time_t start, int i)
{
	int	i;

	i = 0;
	*new = malloc(sizeof(t_philo));
	if (!*new)
		return ;
	(*new)->id = i;
	(*new)->id_t = -1;
	(*new)->left = NULL;
	(*new)->right = NULL;
	(*new)->n_eaten = 0;
	(*new)->is_dead = false;
	(*new)->last_eaten = start;
}

static void	ft_append_new_philo(t_philo **philos, t_philo *new, bool is_last)
{
	t_philo	*tmp;

	if (!philos || !new)
		return ;
	if (!*philos)
	{
		*philos = new;
		return ;
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
}

static void	ft_init_info(t_info **info, char **argv)
{
	
	int				params[5];

	ft_parse_parameters(params, sizeof(params) / sizeof(params[0]), argv);
	(*info)->start = ft_gettime();
	(*info)->n_philos = params[0];
	(*info)->n_to_eat = params[4];
	(*info)->time_to_die = (time_t)params[1];
	(*info)->time_to_eat = (time_t)params[2];
	(*info)->time_to_sleep = (time_t)params[3];
}

static void	ft_assign_forks_to_philos(t_philo **philos, t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = *philos;
	while (i < info->n_philos)
	{
		philo->fork_l = malloc(sizeof(pthread_mutex_t));
		if (!philo->fork_l)
		{
			perror("pthread_mutex_t");
			exit(EXIT_FAILURE);
		}
		pthread_mutex_init(philo->fork_l, NULL);
		philo = philo->right;
		i++;
	}
	while (i--)
	{
		philo->fork_r = philo->right->fork_l;
		philo = philo->right;
	}
}

void	ft_init_data(t_info *info, char **argv)
{
	int		i;
	t_philo	*new;

	i = 0;
	new = NULL;
	ft_init_info(&info, argv);
	while (i < info->n_philos)
	{
		ft_init_new_philo(&new, info->start, i);
		ft_append_new_philo(&(info->philos), new, i == info->n_philos - 1);
		i++;
	}
	ft_assign_forks_to_philos(&(info->philos), info);
}
