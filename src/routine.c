/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:18:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/12 18:46:04 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo, int i)
{
	if (philo->id == 1)
		pthread_mutex_lock(&philo->prog->forks[philo->prog->n_philo - 1]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->id - 2]);
	pthread_mutex_lock(&philo->prog->forks[philo->id - 1]);
	printf("%-10d Philo %i has taken a fork\n", time_elapse(philo), i);
	printf("%-10d Philo %i is \033[0;32meating\033[0m\n", time_elapse(philo), i);
	philo->last_meal = time_elapse(philo);
	philo->n_eat++;
	usleep(philo->prog->t_eat);
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
	while (1)
	{
		if (!philo->prog->max_meals || philo->n_eat != philo->prog->max_meals)
			eat(philo, philo->id);
		/* pthread_mutex_lock(&philo->prog->lock); */
		printf("%-10d Philo %i is sleeping\n", time_elapse(philo), philo->id);
		/* pthread_mutex_unlock(&philo->prog->lock); */
		usleep(philo->prog->t_sleep);
		pthread_mutex_lock(&philo->prog->lock);
		printf("%-10d Philo %i is thinking\n", time_elapse(philo), philo->id);
		pthread_mutex_unlock(&philo->prog->lock);
	}
	return (NULL);
}
