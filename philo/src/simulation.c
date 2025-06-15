/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:26:27 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/15 12:40:53 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Caso especial: un solo filósofo no puede comer (solo tiene un tenedor)
El último filósofo toma los tenedores en orden inverso al resto para evitar
deadlocks
*/
void	take_forks(t_philosopher *philo)
{
	if (philo->table->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		while (!simulation_ended(philo->table))
			usleep(1000);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (philo->id == philo->table->num_philosophers)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philosopher *philo)
{
	if (philo->id == philo->table->num_philosophers)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int	simulation_ended(t_table *table)
{
	int	ended;

	pthread_mutex_lock(&table->death_mutex);
	ended = table->simulation_ended;
	pthread_mutex_unlock(&table->death_mutex);
	return (ended);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_actual_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	while (!simulation_ended(philo->table))
	{
		take_forks(philo);
		if (simulation_ended(philo->table))
		{
			drop_forks(philo);
			break ;
		}
		print_status(philo, "is eating");
		update_meal_time(philo);
		ft_usleep(philo->table->time_to_eat);
		drop_forks(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_actual_time();
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL,
			philosopher_routine, &table->philosophers[i]);
		i++;
	}
	monitor_philosophers(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}
