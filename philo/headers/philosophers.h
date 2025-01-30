/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/30 18:22:25 by tkeil            ###   ########.fr       */
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
# define MAX_PHILOS 200

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
	time_t			last_eaten;
	bool			is_eating;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	struct s_philo	*left;
	struct s_philo	*right;
	t_info			*info;
}					t_philos;

typedef struct s_control_vars
{
	int				n_philos;
	int				n_to_eat;
	time_t			time_to_die;
	time_t			start;
}				t_control_vars;

typedef struct s_philo_vars
{
	time_t			time_to_sleep;
	time_t			time_to_eat;
	time_t			start;
	int				n_philos;
	int				id;
}				t_philo_vars;

typedef struct	s_garbage
{
	void			*ptr;
	pthread_mutex_t	*mutex;
	
}				t_garbage;

// numbers.c
long				ft_atol(char *s);

// clearing.c
void				ft_clear_data(t_philos **philos, int n);
void				ft_clear_philos(t_philos **philos, int n);
void				ft_destroy_forks(t_info *info, pthread_mutex_t *forks);

// init.c
int					ft_init_data(t_philos **philos, char **argv);
int					ft_get_params(int params[], int size, char **argv);
void				ft_destroy_mutexes(t_info **info, int n);
void 				ft_assign_values(t_info **info, int params[], time_t time);

// logging.c
void				ft_log(t_info *info, time_t time, int act, int id);

// strings.c
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *s);

// threads
void				ft_run_threads(t_philos *philos);
void				*ft_philo(void *arg);

// gettime
void				ft_sleep(time_t msec, t_philos *philo);
long				ft_time(time_t start);
time_t				ft_timestamp(void);

// observer
void				*ft_control(void *arg);

// states
void				ft_eat(t_philos *philo, t_info *info, int id, time_t start);
void				ft_nap(t_philos *philo, int id, time_t start);
void				ft_think(t_philos *philo, int id, time_t start);

// thread_utils
bool				ft_death(t_philos *philo);
void				ft_grab_forks(t_philos *philo, int id, time_t start);
void				ft_release_forks(pthread_mutex_t *left,
						pthread_mutex_t *right);
int					ft_join_threads(t_philos *philo, int number_of_philos,
						pthread_t controller);
int					ft_start_threads(t_philos *philo, int *number_of_philos);

#endif
