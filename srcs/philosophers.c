/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:05:38 by tkeil             #+#    #+#             */
/*   Updated: 2024/12/12 17:56:14 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


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
