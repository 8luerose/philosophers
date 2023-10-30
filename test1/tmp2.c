#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    long long last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int time_to_die;
    pthread_t check_thread;
} t_philosopher;

long long current_time_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void log_status(int id, char *status) {
    printf("%lld %d %s\n", current_time_in_ms(), id, status);
}

void *check_life(void *arg) {
    t_philosopher *phil = (t_philosopher *)arg;

    while (1) {
        usleep(1000); // Check every millisecond
        if (current_time_in_ms() - phil->last_meal > phil->time_to_die) {
            log_status(phil->id, "has died");
            exit(0);
        }
    }
    return NULL;
}

void *philosopher_life(void *arg) {
    t_philosopher *phil = (t_philosopher *)arg;
    pthread_create(&phil->check_thread, NULL, check_life, phil);

    while (1) {
        pthread_mutex_lock(phil->left_fork);
        log_status(phil->id, "has taken a fork");
        
        pthread_mutex_lock(phil->right_fork);
        log_status(phil->id, "has taken a fork");

        log_status(phil->id, "is eating");
        phil->last_meal = current_time_in_ms();
        usleep(100 * 1000);

        pthread_mutex_unlock(phil->left_fork);
        pthread_mutex_unlock(phil->right_fork);

        log_status(phil->id, "is sleeping");
        usleep(100 * 1000);

        log_status(phil->id, "is thinking");
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Error: arguments missing\n");
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);

    pthread_mutex_t forks[num_philosophers];
    pthread_t philosophers[num_philosophers];
    t_philosopher phil_data[num_philosophers];

    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++) {
        phil_data[i].id = i + 1;
        phil_data[i].left_fork = &forks[i];
        phil_data[i].right_fork = &forks[(i + 1) % num_philosophers];
        phil_data[i].last_meal = current_time_in_ms();
        phil_data[i].time_to_die = time_to_die;
        pthread_create(&philosophers[i], NULL, philosopher_life, &phil_data[i]);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
