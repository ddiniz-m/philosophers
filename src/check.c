/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:19:42 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/05/22 14:13:00 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	die_eat_check(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < program->n_philo)
	{
		if (program->philosophers[i].last_meal + (program->t_die / 1000)
			+ 10 < (get_time() - program->time_start))
		{
			printf("%-10d Philo %i \033[0;31mdied\033[0m\n", (get_time()
					- program->time_start) - 10, program->philosophers[i].id);
			return (1);
		}
		j += program->philosophers[i].n_eat;
		if (program->max_meals && j == (program->max_meals * program->n_philo))
			return (1);
		i++;
	}
	return (0);
}

int	arg_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 0 || ft_atoi(av[1]) > 200)
			return (1);
		i++;
	}
	return (0);
}
