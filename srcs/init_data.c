/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/25 16:26:48 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_init_new_philo(t_info *info, t_philos **new, int i)
{
	*new = malloc(sizeof(t_philos));
	if (!*new)
		return ;
	(*new)->id = i;
	(*new)->left = NULL;
	(*new)->right = NULL;
	(*new)->n_eaten = 0;
	(*new)->info = info;
	pthread_mutex_init(&(*new)->philo_mutex, NULL);
}

static void	ft_append_new_philo(t_philos **philos, t_philos *new, bool is_last)
{
	t_philos	*tmp;

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
	int		params[5];

	*info = malloc(sizeof(t_info));
	if (!*info)
		exit(EXIT_FAILURE);
	ft_parse_parameters(params, sizeof(params) / sizeof(params[0]), argv);
	(*info)->died = false;
	(*info)->n_philos = params[0];
	(*info)->n_to_eat = params[4];
	(*info)->time_to_die = (time_t)params[1];
	(*info)->time_to_eat = (time_t)params[2];
	(*info)->time_to_sleep = (time_t)params[3];
	pthread_mutex_init(&(*info)->print_mutex, NULL);
	pthread_mutex_init(&(*info)->death_mutex, NULL);
}

static void	ft_assign_forks_to_philos(t_philos **philos, t_info *info)
{
	int			i;
	t_philos	*philo;

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

void	ft_init_data(t_philos **philos, char **argv)
{
	int			i;
	t_info		*info;
	t_philos	*new;

	i = 0;
	new = NULL;
	*philos = NULL;
	printf("a33\n");
	ft_init_info(&info, argv);
	printf("a4\n");
	while (i < info->n_philos)
	{
		ft_init_new_philo(info, &new, i);
		ft_append_new_philo(philos, new, i == info->n_philos - 1);
		i++;
	}
	printf("a5\n");
	ft_assign_forks_to_philos(philos, info);
}
