/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/17 13:55:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

int	create_thread(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		program->philosophers[i] = philo_program_init(program);
		program->philosophers[i].id = i;
		program->philosophers[i].last_meal = 0;
		program->philosophers[i].n_eat = 0;
		if (pthread_create(&program->thread[i], NULL, routine,
				&program->philosophers[i]) != 0)
			return (printf("Thread Create Error\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_program	*program;

	if (ac == 1 || ac > 6)
		return (printf("Incorrect amount of args\n"));
	if (arg_check(ac, av))
		return (printf("Invalid arguments\n"));
	program = program_init(av);
	mutex_init(program);
	if (!program)
		return (1);
	program->time_start = get_time();
	if (create_thread(program))
		return (1);
	while (1)
	{
		if (die_eat_check(program))
		{
			ft_free(program);
			break ;
		}
	}
	return (0);
}
