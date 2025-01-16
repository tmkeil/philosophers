/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/16 20:36:25 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				id_t;
	int				n_eaten;
	bool			is_dead;
	bool			is_thinking;
	bool			is_sleeping;
	time_t			last_eaten;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	struct s_philo	*left;
	struct s_philo	*right;
}					t_philo;

typedef struct s_info
{
	int				x;
	pthread_mutex_t	mutex;
	time_t			start;
	t_philo			*philos;
	int				n_philos;
	int				n_to_eat;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
}					t_info;

// numbers.c
long				ft_atol(char *s);
char				*ft_ltoa(long nbr);

// clearing.c
void				ft_clear_philos(t_philo **philos, int n);

// init.c
void				ft_init_data(t_info *info, char **argv);

// logging.c
void				ft_log(t_info *philo, time_t time, int act, int id);

// strings.c
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *s);

// threads
void				ft_create_threads(t_info *info);
void				*ft_threads(void *data);
#endif
