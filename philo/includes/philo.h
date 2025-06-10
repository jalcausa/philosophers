/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:44:22 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/10 20:15:21 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				simulation_ended;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philosopher	*philosophers;
}	t_table;

/* Parsing.c */
int		args_ok(int argc, char **argv);
void	help_message(void);

/* Utils.c*/
int		ft_atoi(const char *str);

#endif