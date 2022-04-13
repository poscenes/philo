/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:07:33 by poscenes          #+#    #+#             */
/*   Updated: 2022/04/13 16:01:10 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <sys/stat.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	t_lastmeal;
	int				t_eat;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				eat_cnt;
	unsigned long	t_start;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	pid_t			*philos_pid;
	sem_t			*print_sem;
	sem_t			*fork_sem;
	sem_t			*eat;
	sem_t			*stop_sim;
	pthread_t		death;
	pthread_t		check_eat;
	t_philo			philo;
}	t_data;

void				my_usleep(long long ms);
long				get_time(void);
int					check_arg(char **av);
int					ft_atoi(const char *str);
void				init_deathcheck(t_data *data);
int					init_data(int ac, char **av, t_data *data);
void				stop_simulation(t_data *data);
void				*deathcheck(void *_data);
void				*eatcheck(void *_data);
void				lifecycle(t_data *data);

#endif
