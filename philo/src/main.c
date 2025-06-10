/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:40:21 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/10 20:34:58 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	(void)table;
	if (argc == 5 || argc == 6)
	{
		if (!args_ok(argc, argv))
		{
			help_message();
			return (0);
		}
		init_data(&table, argc, argv);
	}
	else
		help_message();
	return (0);
}
