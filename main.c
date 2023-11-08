/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:12:27 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/08 20:03:54 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_all_info	arg;
	t_philo		*philo;

	if (ac != 5 && ac != 6)
		return (print_error("Invalid arguments!!"));
	memset(&arg, 0, sizeof(t_all_info));
	if (init_arg(&arg, ac, av));
		return (print_error("FAIL argument init!!"));
	if (init_philo(&arg, &philo))
		return (print_error("FAIL philo init!!"));
	if (philosophers_start(&arg, philo))
		return (print_error("FAIL philosophers eat!!"));
	//philosophers_finish(&arg, philo))
	
	return (0);
}