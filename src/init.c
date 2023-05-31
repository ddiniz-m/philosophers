/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:20:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/31 18:12:33 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mutex_init(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_init(&program->eating, NULL);
	pthread_mutex_init(&program->exit, NULL);
	while (i < program->n_philo)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
}

t_philo	philo_program_init(t_program *program)
{
	t_philo	philo;

	philo.prog = program;
	return (philo);
}

void	var_init(t_program *program, char **av)
{
	int	i;

	i = 0;
	program->philo_died = 0;
	program->all_fed = 0;
	program->t_die = ft_atoi(av[2]) * 1000;
	program->t_eat = ft_atoi(av[3]) * 1000;
	program->t_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		program->max_meals = ft_atoi(av[5]);
	else
		program->max_meals = -1;
	while (i < program->n_philo)
	{
		program->philosophers[i] = philo_program_init(program);
		program->philosophers[i].id = i;
		program->philosophers[i].last_meal = 0;
		program->philosophers[i].n_eat = 0;
		i++;
	}
}

t_program	*program_init(char **av)
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	if (!program)
		return (NULL);
	program->n_philo = ft_atoi(av[1]);
	program->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* program->n_philo);
	if (!program->philosophers)
		return (NULL);
	var_init(program, av);
	program->thread = malloc(program->n_philo * sizeof(pthread_t));
	if (!program->thread)
		return (NULL);
	program->forks = malloc(program->n_philo * sizeof(pthread_mutex_t));
	if (!program->forks)
		return (NULL);
	return (program);
}
