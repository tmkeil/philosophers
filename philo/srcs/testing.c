/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:13:57 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 14:12:44 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"

// // int	main(int argc, char **argv)
// // {
// // 	// if (!(argc >= 4 && argc <= 5) || !*argv[0])
// // 	// 	return (1);
// // 	return (0);
// // }
// // threads
// void	*r1(void *data)
// {
// 	int		local;
// 	t_info	*info;

// 	info = (t_info *)data;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&info->mutex);
// 		if (info->x >= 1000000)
// 		{
// 			local = info->x;
// 			printf("thread1 x = %i\n", local);
// 			pthread_mutex_unlock(&info->mutex);
// 			break ;
// 		}
// 		info->x++;
// 		pthread_mutex_unlock(&info->mutex);
// 	}
// 	return (NULL);
// }

// void	*r2(void *data)
// {
// 	t_info	*info;

// 	info = (t_info *)data;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&info->mutex);
// 		if (info->x >= 2000000)
// 		{
// 			printf("thread2 x = %i\n", info->x);
// 			pthread_mutex_unlock(&info->mutex);
// 			break ;
// 		}
// 		info->x++;
// 		pthread_mutex_unlock(&info->mutex);
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t	t1;
// 	pthread_t	t2;
// 	t_info		info;

// 	pthread_mutex_init(&info.mutex, NULL);
// 	info.x = 0;
// 	if (pthread_create(&t1, NULL, &r1, &info))
// 		return (1);
// 	if (pthread_create(&t2, NULL, &r2, &info))
// 		return (3);
// 	if (pthread_join(t1, NULL))
// 		return (2);
// 	if (pthread_join(t2, NULL))
// 		return (4);
// 	pthread_mutex_destroy(&info.mutex);
// 	return (0);
// }

// // example of retrieving the time
// int	main(void)
// {
// 	time_t			ds;
// 	suseconds_t		milli_day;
// 	int				dm;
// 	int				dh;
// 	int				m;
// 	int				s;
// 	int				ms;
// 	struct timeval	tp;
// 	struct timezone	tz;
// 	time_t			current_milli_since_1970;

// 	gettimeofday(&tp, &tz);
// 	current_milli_since_1970 = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
// 	// tp.tv_sec = number of seconds since 01.01.1970
// 	// number of seconds since day start at 0 o'clock
// 	printf("current millis: %li\n", current_milli_since_1970);
// 	ds = tp.tv_sec % 86400;
// 	// Millisekunden since day start
// 	milli_day = ds * 1000 + tp.tv_usec / 1000;
// 	// number of minutes since day start
// 	dm = ds / 60;
// 	// number of hours since day start
// 	dh = ds / 3600 - tz.tz_minuteswest / 60;
// 	// current minutes
// 	m = dm % 60;
// 	// current seconds
// 	s = ds % 60;
// 	// Millisekunden in current second
// 	ms = tp.tv_usec / 1000;
// 	printf("hour: %i, minute: %i, seconds: %i, milliseconds: %i\n", dh, m, s,
		// ms);
// 	return (0);
// }
