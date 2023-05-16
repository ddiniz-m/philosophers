/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:53:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/16 15:25:37 by ddiniz-m         ###   ########.fr       */
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
}						t_philo;

typedef struct s_program
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		message;
	pthread_t			*thread;
	int					n_philo;
	t_philo				*philosophers;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					time_start;
	int					max_meals;
	int					signal;
}						t_program;

//check.c
int						arg_check(int ac, char **av);
int						die_eat_check(t_program *program);

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
void					ft_free(t_program *program);

#endif