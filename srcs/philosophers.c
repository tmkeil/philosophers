/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:05:38 by tkeil             #+#    #+#             */
/*   Updated: 2024/12/12 19:07:11 by tkeil            ###   ########.fr       */
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
void	r1(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *) data;
	while (i < 1000000)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->x++;
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
	printf("thread1 x = %i\n", philo->x);
}

void	r2(void *data)
{
	t_philo	*philo;
	int	i;

	i = 0;
	philo = (t_philo *) data;
	while (i < 1000000)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->x++;
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
	printf("thread2 x = %i\n", philo->x);
}

int	main(void)
{
	pthread_t		t1;
	pthread_t		t2;
	t_philo			philo;

	pthread_mutex_init(&philo.mutex, NULL);
	philo.x = 0;
	if (pthread_create(&t1, NULL, &r1, &philo))
		return (1);
	if (pthread_create(&t2, NULL, &r2, &philo))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
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
