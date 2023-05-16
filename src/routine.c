/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:18:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/16 17:58:32 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id == 1)
		pthread_mutex_lock(&philo->prog->forks[philo->prog->n_philo - 1]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->id - 2]);
	pthread_mutex_lock(&philo->prog->forks[philo->id - 1]);
}

void	message(t_philo *philo, char *str)
{
	printf("%-10d Philo %i %s\n", time_elapse(philo), philo->id, str);
}

void	eat(t_philo *philo)
{
	philo->last_meal = time_elapse(philo);
	philo->n_eat++;
	usleep(philo->prog->t_eat);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prog->forks[philo->id - 1]);
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->prog->forks[philo->prog->n_philo - 1]);
	else
		pthread_mutex_unlock(&philo->prog->forks[philo->id - 2]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		lock_forks(philo);
		message(philo, "has taken two forks");
		message(philo, "is \033[0;32meating\033[0m");
		eat(philo);
		unlock_forks(philo);
		if (philo->prog->max_meals > 0 && philo->n_eat == philo->prog->max_meals)
			while(1);
		message(philo, "is sleeping");
		usleep(philo->prog->t_sleep);
		message(philo, "is thinking");
	}
	return (NULL);
}
