/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:45:25 by poscenes          #+#    #+#             */
/*   Updated: 2022/04/23 19:25:45 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ph_eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->meallock);
	philo->t_lastmeal = get_time();
	pthread_mutex_unlock(&philo->meallock);
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is eating\n", philo->t_lastmeal - philo->data->t_start,
		philo->id);
	pthread_mutex_unlock(&philo->data->print);
	my_usleep(philo->data->t_to_eat);
	pthread_mutex_lock(&philo->meallock);
	if (philo->t_eat > 0)
		philo->t_eat--;
	pthread_mutex_unlock(&philo->meallock);
}

static void	ph_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is sleeping\n", get_time() - philo->data->t_start,
		philo->id);
	pthread_mutex_unlock(&philo->data->print);
	put_forks(philo);
	my_usleep(philo->data->t_to_sleep);
}

static void	ph_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is thinking\n", get_time() - philo->data->t_start,
		philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	*philosopher(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->meallock);
	philo->t_lastmeal = get_time();
	pthread_mutex_unlock(&philo->meallock);
	if (philo->id % 2 == 0)
		usleep(10);
	while (philo->t_eat != 0)
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
		usleep(10);
	}
	return (NULL);
}
