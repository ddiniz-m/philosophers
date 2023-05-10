/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/10 17:10:20 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

void		dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->lock);
	if (time_elapse(philo) - philo->last_meal > philo->prog->t_die / 1000)
		{
			printf("%-10d Philo %i died\n", time_elapse(philo), philo->id);
			exit (0);
		}
	pthread_mutex_unlock(&philo->prog->lock);
	return ;
}

void	eat(t_philo *philo, int i)
{
	
	if (philo->id == 1)
			pthread_mutex_lock(&philo->prog->forks[philo->prog->n_philo - 1]);
	else
			pthread_mutex_lock(&philo->prog->forks[philo->id - 2]);
	pthread_mutex_lock(&philo->prog->forks[philo->id - 1]);

	printf("%-10d Philo %i has taken a fork\n", time_elapse(philo), i);
	printf("%-10d Philo %i is eating\n", time_elapse(philo), i);
	usleep(philo->prog->t_eat);
	
	philo->last_meal = time_elapse(philo);
	
	/* printf("time elapsed = %i\nphilo %i\n, time_elapse(philo), philo->id) */
	dead_check(philo);

	if (philo->id == 1)
		pthread_mutex_unlock(&philo->prog->forks[philo->prog->n_philo - 1]);
	else
		pthread_mutex_unlock(&philo->prog->forks[philo->id - 2]);
	pthread_mutex_unlock(&philo->prog->forks[philo->id - 1]);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	philo = (t_philo *)arg;

	philo->prog->time_start = get_time();
	while(1)
	{
		dead_check(philo);
		
		eat(philo, philo->id);
		
		printf("%-10d Philo %i is sleeping\n", time_elapse(philo), philo->id);
		usleep(philo->prog->t_sleep);

		pthread_mutex_lock(&philo->prog->lock);
		printf("%-10d Philo %i is thinking\n", time_elapse(philo), philo->id);
		pthread_mutex_unlock(&philo->prog->lock);

	}
	return (NULL);
}

t_philo	philo_init(t_program *program)
{
	t_philo	philo;

	philo.prog = program;

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
		program->philosophers[i].last_meal = 0;
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
	program->forks = malloc(program->n_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&program->lock, NULL);
	while(i < program->n_philo)
		pthread_mutex_init(&program->forks[i++], NULL);
	
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
	
	create_thread(program, program->n_philo);

	/* pthread_mutex_destroy(&program->left);
	pthread_mutex_destroy(&program->right); */
	int i = 0;
	while(i < program->n_philo)
		pthread_mutex_destroy(&program->forks[i++]);
	return (0);
}
