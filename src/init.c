/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:20:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/12 18:20:16 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	philo_program_init(t_program *program)
{
	t_philo	philo;

	philo.prog = program;
	return (philo);
}

t_program	*program_init(char **av)
{
	t_program	*program;
	int			i;

	i = 0;
	program = (t_program *)malloc(sizeof(t_program));
	program->n_philo = ft_atoi(av[1]);
	program->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* program->n_philo);
	program->thread = malloc(program->n_philo * sizeof(pthread_t));
	program->forks = malloc(program->n_philo * sizeof(pthread_mutex_t));
	if(!program->forks)
		return (NULL);
	pthread_mutex_init(&program->lock, NULL);
	while (i < program->n_philo)
		pthread_mutex_init(&program->forks[i++], NULL);
	program->t_die = ft_atoi(av[2]) * 1000;
	program->t_eat = ft_atoi(av[3]) * 1000;
	program->t_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		program->max_meals = ft_atoi(av[5]);
	return (program);
}
