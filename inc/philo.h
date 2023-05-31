/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:53:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/31 16:59:00 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_program	*prog;
	int					id;
	int					last_meal;
	int					n_eat;
	int					r_fork;
	int					l_fork;
}						t_philo;

typedef struct s_program
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		eating;
	pthread_mutex_t		exit;
	pthread_t			*thread;
	pthread_t			monitoring;
	int					n_philo;
	int					philo_died;
	int					all_fed;
	t_philo				*philosophers;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					time_start;
	int					max_meals;
}						t_program;

int						join_threads(t_program *program);

//check.c
int						arg_check(int ac, char **av);
int						eat_check(t_philo *philo);
int						die_check(t_philo *philo);
int						exit_check(t_philo *philo);

//init.c
t_program				*program_init(char **av);
void					mutex_init(t_program *program);
t_philo					philo_program_init(t_program *program);

//routine.c
void					*routine(void *arg);

//utils.c
int						ft_atoi(const char *str);
int						get_time(void);
int						time_elapse(t_philo *philo);
void					stop_threads(t_program *program);
void					ft_free(t_program *program);

#endif