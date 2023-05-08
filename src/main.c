/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/08 18:50:26 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

void	eat(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->prog->lock);
	philo->prog->forks[i - 1] = 1;
	if (i == 1)
		philo->prog->forks[philo->prog->n_philo - 1] = 1;
	else
		philo->prog->forks[i - 2] = 1;
	printf("%-10d Philo %i is eating\n", get_time() - philo->prog->time_start, i);
	usleep(philo->prog->t_eat);
	philo->last_meal = get_time() - philo->prog->time_start;
	printf("%-10d Philo %i finnished eating\n", get_time() - philo->prog->time_start, i);
	philo->prog->forks[i - 1] = 0;
	if (i == 1)
		philo->prog->forks[philo->prog->n_philo - 1] = 0;
	else
		philo->prog->forks[i - 2] = 0;
	pthread_mutex_unlock(&philo->prog->lock);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	philo = (t_philo *)arg;

	philo->prog->time_start = get_time();
	while(1)
	{
		eat(philo, philo->id);
		printf("%-10d Philo %i is sleeping\n", get_time() - philo->prog->time_start, philo->id);
		usleep(philo->prog->t_sleep);
		/* pthread_mutex_lock(&philo->prog->lock); */
		printf("gettime - start = %i\nlast = %i\n _die = %i\n", get_time() - philo->prog->time_start, philo->last_meal, philo->prog->t_die / 1000);
		if (get_time() - philo->prog->time_start - philo->last_meal > philo->prog->t_die / 1000)
		{
			printf("%-10d Philo %i died\n", get_time() - philo->prog->time_start, philo->id);
			exit (0);
		}
		/* pthread_mutex_unlock(&philo->prog->lock); */
		/* usleep(1000); */
	}
	return (NULL);
}

t_philo	philo_init(t_program *program)
{
	t_philo	philo;

	philo.prog = program;
	philo.last_meal = 0;
	/* philo.n_eat = 0; */

	return (philo);
}

void	create_thread(t_program *program, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		program->philosophers[i] = philo_init(program);
		program->philosophers[i].id = i + 1;
		if (pthread_create(&program->thread[i], NULL, routine, &program->philosophers[i])
			!= 0)
			return(perror("Thread Create"));
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_join(program->thread[i], NULL) != 0)
			return(perror("Thread Join"));
		i++;
	}
	free(program->thread);
	//TODO: free philosophers[i];
	return ;
}

t_program	*program_init(char **av)
{
	t_program	*program;
	int	i;

	i = 0;
	//structs
	program = (t_program *)malloc(sizeof(t_program));
	program->n_philo = ft_atoi(av[1]);
	program->philosophers = (t_philo *)malloc(sizeof(t_philo) * program->n_philo);

	//threads && mutex
	program->thread = malloc(program->n_philo * sizeof(pthread_t));
	program->forks = malloc(program->n_philo * sizeof(int));
	while (i < program->n_philo)
		program->forks[i++] = 0;
	
	//variables
	program->t_die = ft_atoi(av[2]) * 1000;
	program->t_eat = ft_atoi(av[3]) * 1000;
	program->t_sleep = ft_atoi(av[4]) * 1000;

	return (program);
}

int	main(int ac, char **av)
{
	t_program	*program;
	if (ac == 1)
		return (printf("Not enough arguments\n"));

	program = program_init(av);

	pthread_mutex_init(&program->lock, NULL);
	create_thread(program, program->n_philo);
	pthread_mutex_destroy(&program->lock);
	return (0);
}
