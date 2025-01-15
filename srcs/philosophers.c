/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:05:38 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/15 19:20:31 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_test_philos(t_philosopher *philos, int n)
{
	if (!philos)
		return ;
	while (n--)
	{
		printf("philos->id = %i\n", philos->id);
		printf("philos->time_to_die = %li\n", philos->time_to_die);
		printf("philos->time_to_eat = %li\n", philos->time_to_eat);
		printf("philos->time_to_sleep = %li\n", philos->time_to_sleep);
		printf("philos->n_to_eat = %li\n", philos->n_to_eat);
		printf("\n\n");
		philos = philos->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_philo	philo;

	(void)envp;
	if (!(argc >= 5 && argc <= 6) || !*argv[0])
		return (printf("not enough or too many args\n"), 1);
	philo.philos = NULL;
	ft_create_philos(&philo, argv);
	ft_test_philos(philo.philos, philo.n_philos);
	ft_clear_philos(&(philo.philos), philo.n_philos);
	return (0);
}
