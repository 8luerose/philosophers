/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/10/30 21:22:23 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

#define	SUCCESS	0
#define	FAIL	1

typedef struct s_arg
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_num;
	long long		start_time;
	int				finish;
	int				finished_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
} t_arg;

typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	long long	last_eat_time;
	int			eat_count;
	t_arg		*arg;
	pthread_t	thread_id;
} t_philo;

int	print_error(char *msg);

#endif