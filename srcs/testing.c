/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:13:57 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/15 16:14:24 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	main(int argc, char **argv)
// {
// 	// if (!(argc >= 4 && argc <= 5) || !*argv[0])
// 	// 	return (1);
// 	return (0);
// }

// threads
void	*r1(void *data)
{
	int		local;
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->x >= 1000000)
		{
			local = philo->x;
			printf("thread1 x = %i\n", local);
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		philo->x++;
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

void	*r2(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->x >= 2000000)
		{
			printf("thread2 x = %i\n", philo->x);
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		philo->x++;
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	t_philo		philo;

	pthread_mutex_init(&philo.mutex, NULL);
	philo.x = 0;
	if (pthread_create(&t1, NULL, &r1, &philo))
		return (1);
	if (pthread_create(&t2, NULL, &r2, &philo))
		return (3);
	if (pthread_join(t1, NULL))
		return (2);
	if (pthread_join(t2, NULL))
		return (4);
	pthread_mutex_destroy(&philo.mutex);
	return (0);
}











// example of retrieving the time
// int	main(void)
// {
// 	long			ds;
// 	int				dm;
// 	int				dh;
// 	int				m;
// 	int				s;
// 	struct timeval	tp;
// 	struct timezone	tz;

// 	gettimeofday(&tp, &tz);
// 	// tp.tv_sec = number of seconds since 01.01.1970
// 	// number of seconds since day start at 0 o'clock
// 	ds = tp.tv_sec % 86400;
// 	// number of minutes since day start
// 	dm = ds / 60;
// 	// number of hours since day start
// 	dh = ds / 3600 - tz.tz_minuteswest / 60;
// 	// current minutes
// 	m = dm % 60;
// 	// current seconds
// 	s = ds % 60;
// 	printf("hour: %i, minute: %i, seconds: %i\n", dh, m, s);
// 	return (0);
// }
