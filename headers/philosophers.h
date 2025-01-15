/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/01/15 19:17:27 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int						id;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					n_to_eat;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}							t_philosopher;

typedef struct s_philo
{
	int						x;
	int						n_philos;
	t_philosopher			*philos;
	pthread_mutex_t			mutex;
}							t_philo;

// numbers.c
long						ft_atol(char *s);
char						*ft_ltoa(long nbr);

// clearing.c
void						ft_clear_philos(t_philosopher **philos, int n);

// init new philos.c
void						ft_create_philos(t_philo *philo, char **argv);
void						ft_parse_parameters(long params[], int size,
								char **argv);
void						ft_init_new_philo(t_philosopher **new,
								long parameters[], int i);
void						ft_append_new_philo(t_philosopher **philos,
								t_philosopher *new);

// logging.c
void						ft_log(t_philo *philo, long time, int action,
								int id);

// strings.c
int							ft_putchar_fd(char c, int fd);
int							ft_putstr_fd(char *s, int fd);
size_t						ft_strlen(const char *s);

#endif
