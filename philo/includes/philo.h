/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:44:22 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/15 12:40:27 by jalcausa         ###   ########.fr       */
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
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
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

/* parsing.c */
int		args_ok(int argc, char **argv);
void	help_message(void);

/* utils.c*/
int		ft_atoi(const char *str);
long	get_actual_time(void);
void	ft_usleep(int time);
void	print_status(t_philosopher *philo, char *status);
void	print_death(t_philosopher *philo);

/* init.c */
void	init_table(t_table *table, int argc, char **argv);
void	init_forks(t_table *table);
void	init_mutexes(t_table *table);
void	init_philos(t_table *table);
void	init_data(t_table *table, int argc, char **argv);

/* simulation.c */
void	take_forks(t_philosopher *philo);
void	drop_forks(t_philosopher *philo);
int		simulation_ended(t_table *table);
void	*philosopher_routine(void *arg);
void	update_meal_time(t_philosopher *philo);
void	start_simulation(t_table *table);

/* monitor.c*/
int		check_philosopher_death(t_table *table, int i);
int		check_all_ate_enough(t_table *table);
int		update_all_ate_enough(t_table *table, int all_ate_enough);
void	monitor_philosophers(t_table *table);

/* cleanup.c */
void	cleanup(t_table *table);

#endif