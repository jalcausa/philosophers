/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:29:51 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/15 12:56:04 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_table *table, int i)
{
	long	current_time;
	long	last_meal;

	current_time = get_actual_time();
	pthread_mutex_lock(&table->philosophers[i].meal_mutex);
	last_meal = table->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&table->philosophers[i].meal_mutex);
	if (current_time - last_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (!table->simulation_ended)
		{
			table->simulation_ended = 1;
			pthread_mutex_unlock(&table->death_mutex);
			print_death(&table->philosophers[i]);
			return (1);
		}
		pthread_mutex_unlock(&table->death_mutex);
	}
	return (0);
}

int	check_all_ate_enough(t_table *table)
{
	int	i;
	int	all_ate_enough;

	i = 0;
	while (i < table->num_philosophers)
	{
		if (check_philosopher_death(table, i))
			return (1);
		i++;
	}
	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	all_ate_enough = 1;
	while (i < table->num_philosophers)
	{
		pthread_mutex_lock(&table->philosophers[i].meal_mutex);
		if (table->philosophers[i].meals_eaten < table->must_eat_count)
			all_ate_enough = 0;
		pthread_mutex_unlock(&table->philosophers[i].meal_mutex);
		i++;
	}
	return (update_all_ate_enough(table, all_ate_enough));
}

int	update_all_ate_enough(t_table *table, int all_ate_enough)
{
	if (all_ate_enough)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->simulation_ended = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

void	monitor_philosophers(t_table *table)
{
	usleep(100);
	while (1)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (table->simulation_ended)
		{
			pthread_mutex_unlock(&table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->death_mutex);
		if (check_all_ate_enough(table))
			break ;
		usleep(100);
	}
}
