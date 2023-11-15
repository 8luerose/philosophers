#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_arg
{
	int philo_num;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	long long start_time;
	int eat_times;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	int finish;
	int finished_eat;
} t_arg;

typedef struct s_philo
{
	int id;
	int left;
	int right;
	long long last_eat_time;
	int eat_count;
	pthread_t thread;
	t_arg *arg;
} t_philo;

void	ft_philo_check_finish(t_arg *arg, t_philo *philo);

long long ft_get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}


int print_error(char *msg, int ret)
{
    printf("%s\n", msg);
    return (ret);
}


void ft_free_thread(t_arg *arg, t_philo *philo)
{
    int i = 0;

    pthread_mutex_destroy(&arg->print);
    while (i < arg->philo_num)
    {
        pthread_mutex_destroy(&arg->forks[i]);
        i++;
    }
    free(arg->forks);
    free(philo);
}



//////////////////////




int	ft_arg_init_mutex(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (1);
	i = 0;
// 철학자의 현재 상태 표시를 섞이게 나오면 안되므로 출력 권한에 뮤텍스 부여
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_arg_init(t_arg *arg, int argc, char *argv[])
{
	arg->philo_num = atoi(argv[1]);
	arg->time_to_die = atoi(argv[2]);
	arg->time_to_eat = atoi(argv[3]);
	arg->time_to_sleep = atoi(argv[4]);
	arg->start_time = ft_get_time();
	if (arg->philo_num <= 0 || arg->time_to_die < 0 || arg->time_to_eat < 0
		|| arg->time_to_sleep < 0)
	{
		return (5);
	}
	if (argc == 6)
	{
		arg->eat_times = atoi(argv[5]);
		if (arg->eat_times <= 0)
			return (6);
	}
	if (ft_arg_init_mutex(arg))
		return (1);
	return (0);
}

int	ft_philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!(philo))
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->philo_num;
// 원형 테이블이므로 오른쪽 포크는 이렇게 처리.
		(*philo)[i].last_eat_time = ft_get_time();
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

void	ft_pass_time(long long wait_time, t_arg *arg)
{
	long long	start;
	long long	now;

	start = ft_get_time();
	while (!(arg->finish))
	{
		now = ft_get_time();
		if ((now - start) >= wait_time)
			break ;
		usleep(10);
	}
}

int	ft_philo_printf(t_arg *arg, int id, char *msg)
{
	long long	now;

	now = ft_get_time();
	if (now == -1)
	{
		return (-1);
	}
	pthread_mutex_lock(&(arg->print));
	if (!(arg->finish))
	{
		printf("%lld %d %s \n", now - arg->start_time, id + 1, msg);
	}
	pthread_mutex_unlock(&(arg->print));
	return (0);
}

int	ft_philo_action(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&(arg->forks[philo->left]));
	ft_philo_printf(arg, philo->id, "has taken a fork");
	if (arg->philo_num != 1)
	{
		pthread_mutex_lock(&(arg->forks[philo->right]));
		ft_philo_printf(arg, philo->id, "has taken a fork");
		ft_philo_printf(arg, philo->id, "is eating");
		philo->last_eat_time = ft_get_time();
		philo->eat_count = philo->eat_count + 1;
		ft_pass_time((long long)arg->time_to_eat, arg);
		pthread_mutex_unlock(&(arg->forks[philo->right]));
	}
	pthread_mutex_unlock(&(arg->forks[philo->left]));
	return (0);
}


void	*ft_thread(void *argv)
{
	t_arg		*arg;
	t_philo		*philo;

	philo = argv;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(1000);
	while (!arg->finish)
	{
		ft_philo_action(arg, philo);
		if (arg->eat_times == philo->eat_count)
		{
			printf("eat_count : %d %d\n", philo->eat_count, arg->eat_times);
			arg->finished_eat++;
			break ;
		}
		ft_philo_printf(arg, philo->id, "is sleeping");
		ft_pass_time((long long)arg->time_to_sleep, arg);
		ft_philo_printf(arg, philo->id, "is thinking");
	}
	return (0);
}

// 깃헙 코드 버전
// void	*ph_thread(void *argv)
// {
// 	t_arg		*arg;
// 	t_philo		*philo;

// 	philo = argv;
// 	arg = philo->arg;
// 	if (philo->id % 2 == 0)
// 		sleep_until_even_eat(arg);
// 	while (!arg->finish)
// 	{
// 		if (arg->philo_num - 1 == philo->id && philo->eat_count == 0)
// 			usleep(1);
// 		ph_action(arg, philo);
// 		if (arg->philo_num == 1)
// 			spend_time((long long)arg->time_to_sleep, arg);
// 		if (arg->eat_times == philo->eat_count)
// 		{
// 			arg->finished_eat++;
// 			break ;
// 		}
// 		ph_stat_printf(arg, philo->id, "is sleeping");
// 		spend_time((long long)arg->time_to_sleep, arg);
// 		ph_stat_printf(arg, philo->id, "is thinking");
// 	}
// 	return (0);
// }

int	ft_philo_start(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{	
		philo[i].last_eat_time = ft_get_time();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (1);
		i++;
	}
	ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->philo_num)
		pthread_join(philo[i++].thread, NULL);
// 조인을 안하면 프로그램이 먼저 종료되서 쓰레드가 진행되지 않는다.
	ft_free_thread(arg, philo);
	return (0);
}

void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
	int			i;
	long long	now;

	while (!arg->finish)
	{
		if ((arg->eat_times != 0) && (arg->philo_num == arg->finished_eat))
		{
			arg->finish = 1;
			break ;
		}
		i = 0;
		while (i < arg->philo_num)
		{
			now = ft_get_time();
			if ((now - philo[i].last_eat_time) >= arg->time_to_die)
			{
				ft_philo_printf(arg, i, "died");
				arg->finish = 1;
				break ;
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;
	int		errno;

	if (argc != 5 && argc != 6)
		return (print_error("error argc", 3));
// argc는 무조건 5개 아니면 6개이므로 에러 처리

	memset(&arg, 0, sizeof(t_arg));
	errno = ft_arg_init(&arg, argc, argv);
	if (errno)
		return (print_error("error arg init", errno));
// argv를 구조체에 저장하고 필요한 변수들을 할당하고 초기화해준다
	
	errno = ft_philo_init(&philo, &arg);
	if (errno)
		return (print_error("error philo init", errno));
// 철학자별로 들어갈 변수들을 초기화한다.

	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (print_error("error philo start", errno));
// 철학자를 시작하고 종료될때까지 동작한다
	return (0);
}