/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:49:42 by poscenes          #+#    #+#             */
/*   Updated: 2022/04/12 13:07:47 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_threads(t_data *data)
{
	t_philo		*philo;
	int			i;

	i = -1;
	data->phs = malloc(sizeof(t_philo) * data->num_philo);
	data->t_start = get_time();
	while (++i < data->num_philo)
	{
		philo = init_philo(i, data);
		data->phs[i] = philo;
		pthread_create(&data->phs[i]->thd_philo, NULL, philosopher,
			(void *) philo);
	}
	i = -1;
	while (++i < data->num_philo)
		pthread_detach(data->phs[i]->thd_philo);
}

int	check_numeat(t_data *data)
{
	int	i;
	int	sum;

	i = -1;
	sum = 0;
	while (++i < data->num_philo)
		sum += data->phs[i]->t_eat;
	if (sum == 0)
		return (1);
	return (0);
}

void	*check_death(void *_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)_data;
	while (1)
	{
		i = -1;
		while (++i < data->num_philo)
		{
			if (get_time() - data->phs[i]->t_lastmeal >= data->t_to_die)
			{
				pthread_mutex_lock(&data->print);
				printf("%lu %d died\n", get_time() - data->t_start,
					data->phs[i]->id);
				return (NULL);
			}
		}
		if (check_numeat(data))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	death;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_arg(av))
		return (0);
	data = init_data(av);
	if (!data)
		return (0);
	init_threads(data);
	pthread_create(&death, NULL, check_death, (void *)data);
	pthread_join(death, NULL);
	free_ph_arr(data->phs, data->num_philo);
	free_data(data);
	return (0);
}
