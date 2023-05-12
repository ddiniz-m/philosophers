/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/12 18:17:21 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

void	terminate_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
		pthread_detach(program->thread[i++]);
	exit (0);
}

void	create_thread(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		program->philosophers[i] = philo_program_init(program);
		program->philosophers[i].id = i + 1;
		program->philosophers[i].last_meal = 0;
		program->philosophers[i].n_eat = 0;
		if (pthread_create(&program->thread[i], NULL, routine,
				&program->philosophers[i]) != 0)
			return (perror("Thread Create"));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_program	*program;

	if (ac == 1 || ac > 6)
		return (printf("Incorrect amount of args\n"));
	if (arg_check(ac, av))
		return (printf("Invalid arguments\n"));
	program = program_init(av);
	if (!program)
		return (1);
	program->time_start = get_time();
	create_thread(program);
	while (1)
	{
		if (die_eat_check(program))
			break ;
	}
	ft_free(program);
	return (0);
}
