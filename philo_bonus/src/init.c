/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:13:03 by poscenes          #+#    #+#             */
/*   Updated: 2022/04/13 16:21:35 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_sem(t_data *data)
{
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	sem_unlink("eat");
	sem_unlink("stop_sim");
	data->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (data->print_sem == SEM_FAILED)
		return (1);
	data->fork_sem = sem_open("fork_sem", O_CREAT | O_EXCL, S_IRWXU,
			data->num_philo);
	if (data->fork_sem == SEM_FAILED)
		return (1);
	data->stop_sim = sem_open("stop_sim", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (data->stop_sim == SEM_FAILED)
		return (1);
	data->eat = sem_open("eat", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (data->eat == SEM_FAILED)
		return (1);
	return (0);
}

int	init_checkeat(t_data *data)
{
	if (data->eat_cnt)
	{
		if (pthread_create(&data->check_eat, NULL, &eatcheck, data))
		{
			printf("Threading issues");
			return (1);
		}
		pthread_detach(data->check_eat);
	}
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->num_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_cnt = ft_atoi(av[5]);
	if (ac == 6 && data->eat_cnt < 1)
		return (1);
	if (ac == 5)
		data->eat_cnt = -1;
	data->philos_pid = malloc(sizeof(pid_t) * data->num_philo);
	if (!data->philos_pid)
		return (1);
	memset(data->philos_pid, 0, sizeof(pid_t) * data->num_philo);
	if (init_sem(data))
		return (1);
	if (init_checkeat(data))
		return (1);
	return (0);
}

void	init_deathcheck(t_data *data)
{
	data->philo.t_lastmeal = get_time();
	if (pthread_create(&data->death, NULL, &deathcheck, data))
	{
		printf("Threading issues");
		sem_post(data->stop_sim);
	}
	pthread_detach(data->death);
}
