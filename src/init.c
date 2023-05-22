/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:20:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/22 14:13:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	philo_program_init(t_program *program)
{
	t_philo	philo;

	philo.prog = program;
	return (philo);
}

void	mutex_init(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_init(&program->lock, NULL);
	while (i < program->n_philo)
	{
		pthread_mutex_init(&program->forks[i], NULL);
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
	program->thread = malloc(program->n_philo * sizeof(pthread_t));
	if (!program->thread)
		return (NULL);
	program->forks = malloc(program->n_philo * sizeof(pthread_mutex_t));
	if (!program->forks)
		return (NULL);
	program->t_die = ft_atoi(av[2]) * 1000;
	program->t_eat = ft_atoi(av[3]) * 1000;
	program->t_sleep = ft_atoi(av[4]) * 1000;
	program->signal = 0;
	if (av[5])
		program->max_meals = ft_atoi(av[5]);
	else
		program->max_meals = -1;
	return (program);
}
