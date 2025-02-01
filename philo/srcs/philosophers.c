/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:05:38 by tkeil             #+#    #+#             */
/*   Updated: 2025/02/01 22:26:01 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (!(argc >= 5 && argc <= 6) || !*argv[0])
		return (printf("too less or too many args\n"), FAIL);
	if (ft_init_data(&philos, argv) != SUCCESS)
		return (FAIL);
	ft_run_threads(philos);
	ft_clear_data(&philos);
	return (SUCCESS);
}

// void	ft_test_philos(t_info *info, t_philos *philos)
// {
// 	int i = 0;

// 	if (!philos)
// 		return ;
// 	printf("info->n_pilos = %i\n", info->n_philos);
// 	printf("info->time_to_die = %li\n", info->time_to_die);
// 	printf("info->time_to_eat = %li\n", info->time_to_eat);
// 	printf("info->time_to_sleep = %li\n", info->time_to_sleep);
// 	printf("info->n_to_eat = %i\n", info->n_to_eat);
// 	printf("info->died = %i\n\n", (info->finished));
// 	while (i < info->n_philos)
// 	{
// 		printf("philos->id = %i\n", philos[i].id);
// 		printf("philos->n_eaten = %i\n", philos[i].n_eaten);
// 		printf("philos->info = %p\n", philos[i].info);
// 		printf("philos->fork_l = %p, philos->fork_r = %p\n", philos[i].fork_l,
// 			philos[i].fork_r);
// 		printf("\n\n");
// 		i++;
// 	}
// }
