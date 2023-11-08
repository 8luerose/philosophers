/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/08 20:02:41 by taehkwon         ###   ########.fr       */
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

# define	SUCCESS	0
# define	FAIL	1

typedef struct s_all_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat_num;
	// long		start_time;
	// int				finish;
	// int				finished_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t mutex_for_print;
} t_all_info;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			eat_cnt;
	long		last_eat_clock;
	t_all_info	*p_arg;
	pthread_t	thread_id;
} t_philo;

int		print_error(char *msg);
int 	init_arg(t_all_info *arg, int ac, char **av);
int		init_mutex(t_all_info *arg);
long	get_time(void);
int		init_philo(t_all_info *arg, t_philo **philo);
int		philosophers_start(t_all_info *arg, t_philo *philo);

#endif