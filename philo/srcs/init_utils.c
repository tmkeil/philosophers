/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:56:12 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/02 19:18:22 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *s)
{
	size_t	i;
	int		p;
	long	val;
	bool	valid;

	i = 0;
	p = 1;
	val = 0;
	valid = false;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			p = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		valid = true;
		val = val * 10 + (s[i++] - '0');
	}
	if (!valid || s[i] != '\0')
		return (LONG_MIN);
	return (val * p);
}

int	ft_is_invalid(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_params(int params[], int size, char **argv)
{
	int	i;

	i = 0;
	while (i < 5)
		params[i++] = -1;
	i = 0;
	while (i < size && argv[i + 1])
	{
		if (ft_is_invalid(argv[i + 1]))
			return (printf(INVALID_INPUT), FAIL);
		params[i] = ft_atol(argv[i + 1]);
		if (params[i] <= 0 || params[i] > INT_MAX)
		{
			printf(INVALID_VALUE);
			return (FAIL);
		}
		i++;
	}
	if (params[0] > MAX_PHILOS)
	{
		printf(INVALID_PHILOS);
		return (FAIL);
	}
	return (SUCCESS);
}

void	ft_assign_values(t_info **info, int params[], time_t time)
{
	(*info)->start_programm = time;
	(*info)->finished = false;
	(*info)->n_philos = params[0];
	(*info)->n_to_eat = params[4];
	(*info)->time_to_die = (time_t)params[1];
	(*info)->time_to_eat = (time_t)params[2];
	(*info)->time_to_sleep = (time_t)params[3];
}

void	ft_destroy_mtx(t_info **info, int n)
{
	if (n == 1)
		pthread_mutex_destroy(&(*info)->print_mutex);
	else if (n == 2)
	{
		pthread_mutex_destroy(&(*info)->print_mutex);
		pthread_mutex_destroy(&(*info)->death_mutex);
	}
	else if (n == 3)
	{
		pthread_mutex_destroy(&(*info)->print_mutex);
		pthread_mutex_destroy(&(*info)->death_mutex);
		pthread_mutex_destroy(&(*info)->info_mutex);
	}
}
