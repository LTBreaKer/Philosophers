/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:35:13 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/12 12:49:10 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	j;

	i = 0;
	s = 1;
	j = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + str[i++] - '0';
		if (j > 9223372036854775807 && s == 1)
			return (-1);
		if (j > 9223372036854775807 && s == -1)
			return (0);
	}
	return (j * s);
}

int	ft_time(struct timeval start, struct timeval curr)
{
	int	sum;

	sum = (((curr.tv_sec * 1000) + (curr.tv_usec / 1000)) - ((start.tv_sec
					* 1000) + (start.tv_usec / 1000)));
	return (sum);
}

void	ft_wait(int wait_time)
{
	struct timeval	t0;
	struct timeval	t1;

	gettimeofday(&t0, NULL);
	gettimeofday(&t1, NULL);
	while (ft_time(t0, t1) < wait_time)
	{
		usleep(400);
		gettimeofday(&t1, NULL);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->id - 1]);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->start, philo->curr),
		philo->id);
	pthread_mutex_lock(&philo->fork[philo->id % philo->var->n_philo]);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->start, philo->curr),
		philo->id);
	pthread_mutex_lock(&philo->var->death_check);
	gettimeofday(&(philo->last_meal_time), NULL);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is eating\n", ft_time(philo->start, philo->curr), philo->id);
	pthread_mutex_unlock(&philo->var->death_check);
	ft_wait(philo->var->t_eat);
	if (!philo->var->is_alive)
		return ;
	pthread_mutex_unlock(&philo->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->fork[philo->id % philo->var->n_philo]);
}

int	make_mutex(pthread_mutex_t **f, t_var **var, t_philo **philo)
{
	int	i;

	i = 0;
	gettimeofday(&(*var)->tmp, NULL);
	while (i < (*var)->n_philo)
	{
		if (pthread_mutex_init((*f + i), NULL) == -1)
			return (1);
		gettimeofday(&(*philo)[i].start, NULL);
		(*philo)[i].last_meal_time = (*var)->tmp;
		i++;
	}
	if (pthread_mutex_init(&(*var)->eat, NULL) == -1)
		return (1);
	if (pthread_mutex_init(&(*var)->death_check, NULL) == -1)
		return (1);
	return (0);
}
