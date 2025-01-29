/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/29 22:42:42 by tkeil            ###   ########.fr       */
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

# define FAIL EXIT_FAILURE
# define SUCCESS EXIT_SUCCESS

typedef enum s_actions
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}					t_actions;

typedef struct s_info
{
	int				n_philos;
	int				n_to_eat;
	bool			finished;
	time_t			start_programm;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	info_mutex;
}					t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		id_t;
	int				n_eaten;
	time_t			start_philo;
	time_t			last_eaten;
	bool			is_eating;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	struct s_philo	*left;
	struct s_philo	*right;
	t_info			*info;
}					t_philos;

// numbers.c
long				ft_atol(char *s);

// clearing.c
void				ft_clear_data(t_philos **philos, int n);
void				ft_clear_philos(t_philos **philos, int n);

// init.c
int					ft_init_data(t_philos **philos, char **argv);
int					ft_parse_parameters(int params[], int size, char **argv);

// logging.c
void				ft_log(t_info *info, time_t time, int act, int id);

// strings.c
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *s);

// threads
void				ft_run_threads(t_philos *philos);

// gettime
void				ft_sleep(time_t msec, t_philos *philo);
long				ft_time(t_philos *philo);
time_t				ft_timestamp(void);

// observer
void				*ft_control(void *arg);

// states
void				ft_eat(t_philos *philo, t_info *info, int id);
void				ft_nap(t_philos *philo, int id);
void				ft_think(t_philos *philo, int id);

// thread_utils
bool				ft_death(t_philos *philo);
void				ft_grab_forks(t_philos *philo, int id);
void				ft_release_forks(pthread_mutex_t *left,
						pthread_mutex_t *right);

#endif
