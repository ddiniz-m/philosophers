/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:19:42 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/05 14:09:04 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	exit_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->exit);
	if (philo->prog->philo_died || philo->prog->all_fed)
	{
		pthread_mutex_unlock(&philo->prog->exit);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->exit);
	return (0);
}

int	die_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->prog->n_philo)
	{
		pthread_mutex_lock(&philo->prog->eating);
		if (time_elapse(philo) > philo[i].last_meal
			+ (philo->prog->t_die / 1000))
		{
			pthread_mutex_lock(&philo->prog->exit);
			philo->prog->philo_died = 1;
			pthread_mutex_unlock(&philo->prog->exit);
			printf("%-10d %i \033[0;31mdied\033[0m\n", time_elapse(philo),
				philo[i].id + 1);
			pthread_mutex_unlock(&philo->prog->eating);
			return (1);
		}
		pthread_mutex_unlock(&philo->prog->eating);
		i++;
	}
	return (0);
}

int	eat_check(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->prog->n_philo)
	{
		pthread_mutex_lock(&philo->prog->eating);
		j += philo[i].n_eat;
		if (philo->prog->max_meals && j == (philo->prog->max_meals
				* philo->prog->n_philo))
		{
			pthread_mutex_lock(&philo->prog->exit);
			philo->prog->all_fed = 1;
			pthread_mutex_unlock(&philo->prog->exit);
			pthread_mutex_unlock(&philo->prog->eating);
			return (1);
		}
		pthread_mutex_unlock(&philo->prog->eating);
		i++;
	}
	return (0);
}

int	arg_check(int ac, char **av)
{	
	int	i;

	i = 1;
	if (ft_atoi(av[i]) > 200)
		return (1);
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		if ((i >= 2 && i <= 4) && ft_atoi(av[i]) < 60)
			return (1);
		i++;
	}
	return (0);
}
