/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:15:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/14 13:16:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->simulation_ended = 0;
	table->start_time = 0;
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->num_philosophers);
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->num_philosophers);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	init_mutexes(t_table *table)
{
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = 0;
		pthread_mutex_init(&table->philosophers[i].meal_mutex, NULL);
		table->philosophers[i].table = table;
		table->philosophers[i].left_fork = &table->forks[i];
		if (i == table->num_philosophers - 1)
			table->philosophers[i].right_fork = &table->forks[0];
		else
			table->philosophers[i].right_fork = &table->forks[i + 1];
		i++;
	}
}

void	init_data(t_table *table, int argc, char **argv)
{
	init_table(table, argc, argv);
	init_forks(table);
	init_mutexes(table);
	init_philos(table);
}
