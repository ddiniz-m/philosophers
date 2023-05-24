/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:18:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/24 18:13:48 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->prog->message);
	printf("%-10d Philo %i %s\n", time_elapse(philo), philo->id, str);
	pthread_mutex_unlock(&philo->prog->message);
}

void	lock_forks(t_philo *philo)
{
	philo->r_fork = ((philo->id + 1) % philo->prog->n_philo);
	philo->l_fork = philo->id;
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->prog->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->r_fork]);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->prog->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->l_fork]);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->lock);
	philo->last_meal = time_elapse(philo);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->prog->lock);
	usleep(philo->prog->t_eat);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prog->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->prog->forks[philo->r_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		lock_forks(philo);
		message(philo, "has taken a fork");
		message(philo, "has taken a fork");
		message(philo, "is \033[0;32meating\033[0m");
		eat(philo);
		unlock_forks(philo);
		if (philo->prog->max_meals > 0 && philo->n_eat
			== philo->prog->max_meals)
			/* pthread_detach(philo->prog->thread[philo->id]); */
			while (1)
				;
		message(philo, "is sleeping");
		usleep(philo->prog->t_sleep);
		message(philo, "is thinking");
	}
	return (NULL);
}
