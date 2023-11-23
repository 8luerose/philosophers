typedef struct s_arg
{
	int				philo_num; // 철학자 수
	int				life_time; // 철학자 생명 시간
	int				eat_time; // 식사 소요 시간
	int				sleep_time; // 수면 소요 시간
	int				eat_num; // 식사 횟수
	/* pthread_mutex_t	 무더기들 중략 */
	int				monitor; // 종료 flag
}	t_arg;

typedef struct s_philo
{
	int			id; // 철학자 넘버
	int			eat_count; // 철학자 식사 횟수
	int			left; // 왼쪽 포크 넘버
	int			right; // 오른쪽 포크 넘버
	long		last_eat; // 마지막 식사 시간
	long		last_time; // 쓰레드의 시작시간 (작명센스 ㅈㅅ)
	pthread_t	thread; // 쓰레드 ID
	t_arg		*arg; // 입력 인자 값
}	t_philo;


int	init_argv(t_arg *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->life_time = ft_atoi(argv[2]);
	arg->eat_time = ft_atoi(argv[3]);
	arg->sleep_time = ft_atoi(argv[4]);
	arg->monitor = 0;
	if (arg->philo_num <= 0 || arg->life_time < 0 || \
		arg->eat_time < 0 || arg->sleep_time < 0)
		return (1);
	if (argc == 6)
	{
		arg->eat_num = ft_atoi(argv[5]);
		if (arg->eat_num <= 0)
			return (1);
	}
	else
		arg->eat_num = 0;
	return (0);
}


int	init_philo(t_philo **philo, t_arg *arg)
{
	int		i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!philo)
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->philo_num;
		(*philo)[i].last_eat = 0;
		(*philo)[i].last_time = 0;
		(*philo)[i].arg = arg;
		i++;
	}
	return (0);
}

arg->fork = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!arg->fork)
		return (1);
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->fork[i]), NULL) == -1)
			return (1);
		i++;
	}


while (i < arg->philo_num)
	{
		pthread_mutex_lock(&philo->arg->mutex_last_eat);
		philo[i].last_eat = get_time();
		pthread_mutex_unlock(&philo->arg->mutex_last_eat);
		philo[i].last_time = get_time();
		if (pthread_create(&(philo[i].thread), NULL, thread_f, &philo[i]))
			return (1);
		i++;
	}




	void	*thread_f(void *data)
{
	t_philo		*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!checking(philo->arg)) // 죽었는지 살았는지 체크
	{
		if (get_fork(philo)) //포크 잡다 죽었으면 종료
			break ;
		if (checking(philo->arg))
		{
			pthread_mutex_unlock(&(philo->arg->fork[philo->left]));
			pthread_mutex_unlock(&(philo->arg->fork[philo->right]));
			break ;
		}
		philo_eating(philo); // 식사
		if (checking(philo->arg)) // 다 먹었는데 누구 죽었음 종료
			break ;
		philo_printf(philo, philo->id, "is sleeping");
		ft_usleep(philo->arg->sleep_time);
		if (checking(philo->arg)) // 자고 일났는데 누구 죽었음 종료
			break ;
		philo_printf(philo, philo->id, "is thinking");
	}
	return (0);
}



int	get_fork(t_philo *philo)
{
	if (philo->arg->philo_num == 1) //한명일 때 예외처리
	{
		pthread_mutex_lock(&(philo->arg->fork[philo->left]));
		philo_printf(philo, philo->id, "has taken a fork");
		pthread_mutex_unlock(&(philo->arg->fork[philo->left]));
		return (1);
	}
	pthread_mutex_lock(&(philo->arg->fork[philo->left]));
	philo_printf(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->arg->fork[philo->right]));
	philo_printf(philo, philo->id, "has taken a fork");
	return (0);
}


void	philo_eating(t_philo *philo)
{
	philo_printf(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->arg->mutex_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->arg->mutex_last_eat);
	ft_usleep(philo->arg->eat_time);
	pthread_mutex_lock(&philo->arg->mutex_eat_cnt);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->arg->mutex_eat_cnt);
	pthread_mutex_unlock(&(philo->arg->fork[philo->left]));
	pthread_mutex_unlock(&(philo->arg->fork[philo->right]));
}


# include <sys/time.h>

struct timeval
{
    long tv_sec;       // 초
    long tv_usec;      // 마이크로초
}


long	get_time(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}

void	ft_usleep(long sleep_time)
{
	long	start;

	start = get_time();
	while (start + (sleep_time * 1) > get_time())
		usleep(100);
}

void	monitoring(t_philo *philo, t_arg *arg)
{
	int		i;
	long	now_time;

	while (!checking(arg))
	{
		if (arg->eat_num != 0 && check_eat_cnt(philo, arg) == arg->eat_num)
		{
			change_monitor(arg);
			break ;
		}
		i = 0;
		while (i < arg->philo_num)
		{
			now_time = get_time();
			if ((now_time - last_eat(&philo[i])) > arg->life_time)
			{
				philo_printf(&philo[i], philo[i].id, "died");
				change_monitor(arg);
				break ;
			}
			i++;
		}
		usleep(10);
	}
}


int	checking(t_arg *arg)
{
	pthread_mutex_lock(&arg->mutex_monitor);
	if (arg->monitor == 1)
	{
		pthread_mutex_unlock(&arg->mutex_monitor);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&arg->mutex_monitor);
		return (0);
	}
}



