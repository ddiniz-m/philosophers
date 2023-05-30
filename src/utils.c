/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:57:50 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/30 16:54:36 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free(t_program *program)
{
	pthread_mutex_destroy(&program->exit);
	pthread_mutex_destroy(&program->eating);
	free(program->philosophers);
	free(program->forks);
	free(program->thread);
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
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (*str)
	{	
		num = (*str - '0') + (num * 10);
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	if ((num * sign > 2147483647) || (num * sign < -2147483648))
		return (-1);
	return (num * sign);
}
