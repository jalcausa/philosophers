/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:32:41 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/10 20:06:51 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	valid_atoi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	args_ok(int argc, char **argv)
{
	if (valid_atoi(argv[1]) && valid_atoi(argv[2]) && valid_atoi(argv[3])
		&& valid_atoi(argv[4]))
	{
		if (ft_atoi(argv[1]) == 0)
			return (0);
		if (argc == 6)
		{
			if (valid_atoi(argv[5]))
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

void	help_message(void)
{
	printf("Bad arguments, arguments admitted:\n");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}
