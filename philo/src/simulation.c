/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:26:27 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/14 13:49:32 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	// Caso especial: un solo filósofo no puede comer (solo tiene un tenedor)
	if (philo->table->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		while (!simulation_ended(philo->table))
			usleep(1000); // 1ms cada iteración
		pthread_mutex_unlock(philo->left_fork);
		return;
	}

	// SOLUCIÓN CORRECTA: Solo el último filósofo toma en orden inverso
	if (philo->id == philo->table->num_philosophers)
	{
		// El último filósofo toma primero el derecho, luego el izquierdo
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		// Todos los demás toman primero el izquierdo, luego el derecho
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philosopher *philo)
{
	// Liberar en orden inverso al que se tomaron
	if (philo->id == philo->table->num_philosophers)
	{
		// El último filósofo tomó: derecho → izquierdo
		// Debe liberar: izquierdo → derecho
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		// Los demás tomaron: izquierdo → derecho  
		// Deben liberar: derecho → izquierdo
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int		simulation_ended(t_table *table)
{
	int	ended;

	pthread_mutex_lock(&table->death_mutex);
	ended = table->simulation_ended;
	pthread_mutex_unlock(&table->death_mutex);
	return (ended);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;
	
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_actual_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	
	while (!simulation_ended(philo->table))
	{
		take_forks(philo);
		if (simulation_ended(philo->table))
		{
			drop_forks(philo);
			break;
		}
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_actual_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
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