/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:05:38 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/27 17:15:07 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	ft_test_philos(t_info *info, t_philos *philos, int n)
// {
// 	if (!philos)
// 		return ;
// 	printf("info->n_pilos = %i\n", info->n_philos);
// 	printf("info->time_to_die = %li\n", info->time_to_die);
// 	printf("info->time_to_eat = %li\n", info->time_to_eat);
// 	printf("info->time_to_sleep = %li\n", info->time_to_sleep);
// 	printf("info->n_to_eat = %i\n", info->n_to_eat);
// 	printf("info->died = %i\n\n", (info->finished));
// 	while (n--)
// 	{
// 		printf("philos->id = %i\n", philos->id);
// 		printf("philos->id_t = %lu\n", (unsigned long)philos->id_t);
// 		printf("philos->n_eaten = %i\n", philos->n_eaten);
// 		printf("philos->info = %p\n", philos->info);
// 		printf("philos->fork_l = %p, philos->fork_r = %p\n", philos->fork_l, philos->fork_r);
// 		printf("current = %p, left = %p, right = %p\n", philos, philos->left, philos->right);
// 		printf("\n\n");
// 		philos = philos->right;
// 	}
// }

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (!(argc >= 5 && argc <= 6) || !*argv[0])
		return (1);
	ft_init_data(&philos, argv);
	ft_run_threads(&philos);
	// ft_clear_data(&(info->philos), info->n_philos);
	return (0);
}
