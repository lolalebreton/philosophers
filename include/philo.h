/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 14:15:02 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define ARG_ERROR		"Wrong arguments"
# define MALLOC_ERROR	"Malloc failed"

# define CREAT_LOG		"has been created"
# define FORK_LOG		"has taken a fork"
# define EAT_LOG		"is eating"
# define SLEEP_LOG		"is sleeping"
# define THINK_LOG		"is thinking"
# define DEATH_LOG		"died"

# define NC				"\e[0m"
# define WHITE			"\e[37m"
# define BLACK			"\e[30m"
# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"

typedef struct s_shared_mutex {
	pthread_mutex_t	*forks;
	pthread_mutex_t	*printf_mutex;
}	t_shared_mutex;

typedef struct s_param{
	int				number_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_eat;
	long			start;
}	t_param;

typedef struct s_philo{
	int				id;
	t_shared_mutex	*shared_mutex;
	t_param			param;
	int				end;
	pthread_mutex_t	*end_mutex;
	int				number_of_times_he_ate;
	long			last_time_he_ate;
	pthread_mutex_t	*he_ate_mutex;
}	t_philo;

typedef struct s_data{
	t_shared_mutex	*shared_mutex;
	t_philo			*philo;
	t_param			param;
	pthread_mutex_t	*global_end_mutex;
	int				global_end;
}	t_data;

/* ************************************************************************** */
/*                                  thread.c                                  */
/* ************************************************************************** */

void			print_log(t_philo *philo, char *log, char *color);
void			eat_routine(t_philo *philo);
void			*thread_routine(t_philo *philo);
int				death_check(t_data *data, t_philo *philo);
void			*death_thread(t_data *data);

/* ************************************************************************** */
/*                                   init.c                                   */
/* ************************************************************************** */

t_param			init_param(int ac, char **av);
t_shared_mutex	*init_shared_mutex(int nb);
t_philo			*init_philo(t_philo *philosophers, t_data *data,
					pthread_mutex_t *end_mutex, pthread_mutex_t *he_ate_mutex);
t_philo			*init_philosophers(t_data *data);
t_data			*init_data(t_param param);

/* ************************************************************************** */
/*                                   util.c                                   */
/* ************************************************************************** */

long			time_ms(struct timeval tv, long *start);
int				number_of_times_he_ate(t_philo *philo);
long			last_eat_time(t_philo *philo);
void			ft_usleep(long time_to_sleep);
int				fork_id(t_philo *philo, int first);

/* ************************************************************************** */
/*                                    end.c                                   */
/* ************************************************************************** */

int				is_end(t_philo *philo);
void			global_end(t_data *data, t_philo *philo);
int				check_global_end(t_data *data);

/* ************************************************************************** */
/*                                    lib.c                                   */
/* ************************************************************************** */

int				ft_error(char *error);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
int				ft_strdigit(char *str);
int				ft_atoi(char *str);
void			*ft_calloc(size_t nmemb, size_t size);

/* ************************************************************************** */
/*                                   free.c                                   */
/* ************************************************************************** */

void			free_mutex(pthread_mutex_t *mut, int nb);
void			free_shared_mutex(t_shared_mutex *shared_mutex, int n);
void			free_data(t_data *data);
void			free_all(t_data *data);
void			free_if(void *to_free);

#endif