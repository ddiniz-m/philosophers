/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/30 19:09:20 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if (die_check(philo) != 0)
			break ;
		if (eat_check(philo) != 0)
			break ;
	}
	return (NULL);
}

int	create_thread(t_program *program)
{
	int	i;

	i = 0;
	pthread_create(&program->monitoring, NULL, monitoring, program->philosophers);
	while (i < program->n_philo)
	{
		pthread_create(&program->thread[i], NULL, routine, &program->philosophers[i]);
		i++;
	}
	return (0);
}

int	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		printf("test\n");
		if (pthread_join(program->thread[i], NULL) != 0)
			perror("Thread Join Error\n");
		i++;
	}
	if (pthread_join(program->monitoring, NULL) != 0)
			perror("Thread Join Error\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_program	*program;

	if (ac < 5 || ac > 6)
		return (printf("Incorrect amount of args\n"));
	if (arg_check(ac, av))
		return (printf("Invalid arguments\n"));
	program = program_init(av);
	if (!program)
		return (1);
	mutex_init(program);
	program->time_start = get_time();
	if (create_thread(program))
		return (1);
	if (join_threads(program))
		return (1);
	ft_free(program);
	return (0);
}
