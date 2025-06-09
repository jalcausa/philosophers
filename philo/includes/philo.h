/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:44:22 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/09 23:55:44 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

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

/* Main functions */
int		init_data(t_data *data, char **argv);
void	start_simulation(t_data *data);
void	cleanup(t_data *data);

/* Philosopher routines */
void	*philosopher_routine(void *arg);
void	eat(t_philosopher *philo);
void	sleep_philo(t_philosopher *philo);
void	think(t_philosopher *philo);

/* Monitor */
void	*monitor_routine(void *arg);

/* Utils */
long	get_current_time(void);
long	get_timestamp(t_data *data);
void	print_status(t_philosopher *philo, char *status);
void	ft_usleep(int milliseconds);

/* Parsing & Validation */
int		parse_arguments(int argc, char **argv);
int		is_valid_number(char *str);

/* Error handling */
void	error_exit(char *message);

#endif