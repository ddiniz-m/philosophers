/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:57:50 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/12 18:33:48 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philo)
	{
		pthread_mutex_destroy(&program->forks[i]);
		pthread_detach(program->thread[i]);
		i++;
	}
	pthread_mutex_destroy(&program->lock);
	free(program->forks);
	free(program->thread);
	free(program->philosophers);
	free(program);
}

int	time_elapse(t_philo *philo)
{
	return (get_time() - philo->prog->time_start);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (((str[i] >= 9) && (str[i] <= 13))
		|| (str[i] == 32))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{	
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	if ((num * sign > 2147483647) || (num * sign < -2147483648))
		return (-1);
	return (num * sign);
}
