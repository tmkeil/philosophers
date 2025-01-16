/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/16 19:43:40 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_init_new_philo(t_philo **new, time_t start, int i)
{
	*new = malloc(sizeof(t_philo));
	if (!*new)
		return ;
	(*new)->id = i;
	(*new)->id_t = -1;
	(*new)->left = NULL;
	(*new)->right = NULL;
	(*new)->fork_l = NULL;
	(*new)->fork_r = NULL;
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

static void	ft_parse_parameters(int params[], int size, char **argv)
{
	int	i;

	i = 0;
	while (i < 5)
		params[i++] = -1;
	i = 0;
	while (i < size && argv[i + 1])
	{
		params[i] = ft_atol(argv[i + 1]);
		if (params[i] == -1 || params[i] < 0)
		{
			printf("invalid parameter\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	ft_init_info(t_info **info, char **argv)
{
	struct timeval	tp;
	int				params[5];

	gettimeofday(&tp, NULL);
	(*info)->start = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	(*info)->philos = NULL;
	ft_parse_parameters(params, sizeof(params) / sizeof(params[0]), argv);
	(*info)->n_philos = params[0];
	(*info)->n_to_eat = params[4];
	(*info)->time_to_die = (time_t)params[1];
	(*info)->time_to_eat = (time_t)params[2];
	(*info)->time_to_sleep = (time_t)params[3];
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
		ft_append_new_philo(&info->philos, new, i == info->n_philos - 1);
		i++;
	}
}
