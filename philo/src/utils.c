/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:56:36 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/15 12:31:40 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sn;
	int	num;

	i = 0;
	sn = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sn *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - 48) + (num * 10);
		i++;
	}
	num *= sn;
	return (num);
}

long	get_actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	if (time <= 0)
		usleep(0);
	else
		usleep(time * 1000);
}

void	print_status(t_philosopher *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->death_mutex);
	if (!philo->table->simulation_ended)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		timestamp = get_actual_time() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
}

void	print_death(t_philosopher *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_mutex);
	timestamp = get_actual_time() - philo->table->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
