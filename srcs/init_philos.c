/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:53:26 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/15 17:50:41 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_new_philo(t_philosopher **new, long parameters[], int i)
{
	*new = malloc(sizeof(t_philosopher));
	if (!*new)
		return ;
	(*new)->id = i;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	(*new)->n_to_eat = parameters[4];
	(*new)->time_to_die = parameters[1];
	(*new)->time_to_eat = parameters[2];
	(*new)->time_to_sleep = parameters[3];	
}

void	ft_append_new_philo(t_philosopher **philos, t_philosopher *new)
{
	t_philosopher	*tmp;
	
	if (!philos || !new)
		return ;
	if (!*philos)
	{
		*philos = new;
		return ;
	}
	tmp = *philos;
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

void	ft_parse_parameters(long params[], int size, char **argv)
{
	int	i;

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

void	ft_create_philos(t_philo *philo, char **argv)
{
	int				i;
	long			params[5];
	t_philosopher	*new;

	i = 0;
	new = NULL;
	while (i < 5)
		params[i++] = -1;
	ft_parse_parameters(params, sizeof(params) / sizeof(params[0]), argv);
	i = 0;
	philo->n_philos = params[0];
	while ((params[0])--)
	{
		ft_init_new_philo(&new, params, i++);
		ft_append_new_philo(&philo->philos, new);
	}
}
