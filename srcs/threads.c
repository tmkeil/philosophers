/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:56 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/16 20:36:01 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_threads(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	return (NULL);	
}

void	ft_create_threads(t_info *info)
{
	int			i;
	pthread_t	threads[info->n_philos];

	i = 0;
	while (i < info->n_philos)
	{
		pthread_create(&threads[i], NULL, &ft_threads, (void *)info);
		i++;
	}
}
