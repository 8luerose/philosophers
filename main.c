/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:12:27 by taehkwon          #+#    #+#             */
/*   Updated: 2023/10/30 21:26:49 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_arg	arg;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (print_error("Invalid arguments"));
	memset(&arg, 0, sizeof(t_arg));
	if 
}