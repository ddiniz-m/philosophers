/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:20:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/24 19:10:33 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

void	*routine(void *input)
{
	int index = *((int *) input);
	if (index % 2 == 0)
		usleep(1);
	printf("index = %i\n", index);
	return (NULL);
}

void	create_thread(int n)
{
	int		i;
	t_philo	philo;

	i = 0;
	philo.id = malloc(n * sizeof(int));
	philo.thread = malloc(n * sizeof(pthread_t));
	while (i < n)
	{
		philo.id[i] = i + 1;
		if (pthread_create(&philo.thread[i], NULL, routine, &philo.id[i])
			!= 0)
			return(perror("Thread Create"));
		i++;
	}
	return ;
}

void	join_thread(int n)
{
	int		i;
	t_philo	philo;

	i = 0;
	while (i < n)
	{
		if (pthread_join(philo.thread[i], NULL) != 0)
			return(perror("Thread Join"));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;
	if (ac == 1)
		return (printf("Not enough arguments\n"));
	philo.thread = malloc(5 * sizeof(pthread_t));
	create_thread(ft_atoi(av[1]));
	join_thread(ft_atoi(av[1]));
	free(philo.id);
	free(philo.thread);
	return (0);
}