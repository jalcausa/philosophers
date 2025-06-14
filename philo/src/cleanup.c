/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:32:45 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/14 13:16:29 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	free(table->forks);
	free(table->philosophers);
}