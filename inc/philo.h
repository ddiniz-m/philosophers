/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:53:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/08 17:46:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_philo
{
	struct s_program	*prog;
	int					id;
	int					last_meal;
	/* int					n_eat; */
}				t_philo;

typedef struct s_program
{
	pthread_mutex_t	lock;
	pthread_t		*thread;
	int				n_philo;
	t_philo			*philosophers;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				*forks;
	int				time_start;
}				t_program;

int	ft_atoi(const char *str);
int	ft_is_prime(int nb);
int	get_time(void);
void	terminate_threads(t_program *program);

#endif