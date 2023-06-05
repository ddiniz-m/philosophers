/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:18:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/05 14:11:06 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->prog->exit);
	if (philo->prog->all_fed == 0 && philo->prog->philo_died == 0)
		printf("%-10d %i %s\n", time_elapse(philo), philo->id + 1, str);
	pthread_mutex_unlock(&philo->prog->exit);
}

int	lock_forks(t_philo *philo)
{
	philo->r_fork = ((philo->id + 1) % philo->prog->n_philo);
	philo->l_fork = philo->id;
	if (philo->prog->n_philo == 1)
	{
		message(philo, "takes a fork");
		return (1);
	}
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->prog->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->r_fork]);
	message(philo, "takes a fork");
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->prog->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->prog->forks[philo->l_fork]);
	message(philo, "takes a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->eating);
	philo->last_meal = time_elapse(philo);
	pthread_mutex_unlock(&philo->prog->eating);
	ft_usleep(philo->prog->t_eat);
	pthread_mutex_lock(&philo->prog->eating);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->prog->eating);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prog->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->prog->forks[philo->l_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (lock_forks(philo))
			break ;
		message(philo, "is \033[0;32meating\033[0m");
		eat(philo);
		if (exit_check(philo))
		{
			unlock_forks(philo);
			break ;
		}
		unlock_forks(philo);
		message(philo, "is sleeping");
		ft_usleep(philo->prog->t_sleep);
		message(philo, "is thinking");
	}
	return (NULL);
}
