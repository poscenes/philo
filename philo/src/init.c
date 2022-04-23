/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:32:27 by poscenes          #+#    #+#             */
/*   Updated: 2022/04/23 16:23:44 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->forks = forks_init(data->num_philo);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	pthread_mutex_init(&data->print, NULL);
	if (av[5])
		data->eat_cnt = ft_atoi(av[5]);
	else
		data->eat_cnt = -1;
	return (data);
}

t_philo	*init_philo(int i, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->data = data;
	philo->t_eat = data->eat_cnt;
	philo->rfork = i;
	philo->lfork = (i + data->num_philo - 1) % data->num_philo;
	pthread_mutex_init(&philo->meallock, NULL);
	return (philo);
}

void	free_ph(t_philo *philo)
{
	pthread_mutex_destroy(&philo->meallock);
	free(philo);
}

void	free_ph_arr(t_philo **phs, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&phs[i]->meallock);
		free(phs[i]);
		i++;
	}
	free(phs);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	free_for_forks(data->forks, data->num_philo);
	free(data);
}
