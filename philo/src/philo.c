/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:46:30 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/11 10:05:18 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_dead(t_philo *philo, t_var *var)
{
	int				i;
	struct timeval	check;

	while (var->is_alive)
	{
		i = 0;
		while (i < var->n_philo)
		{
			gettimeofday(&var->curr, NULL);
			pthread_mutex_lock(&var->death_check);
			if (!var->av_philo)
				return ;
			if (ft_time(philo[i].last_meal_time, var->curr) > var->t_die)
				return (var->is_alive = 0, gettimeofday(&check, NULL),
					(void)printf("%5d %d has died\n", ft_time(philo->start, check),
						philo[i].id));
			pthread_mutex_unlock(&var->death_check);
			if (!var->is_alive)
				return ;
			i++;
		}
	}
	return ;
}

int	initializer(t_var *var, t_philo **philo, pthread_mutex_t **f)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * var->n_philo);
	if (!*philo)
		return (1);
	*f = malloc(sizeof(**f) * var->n_philo);
	if (!*f)
		return (1);
	var->ph = malloc(sizeof(pthread_t) * var->n_philo);
	if (!var->ph)
		return (1);
	while (i < var->n_philo)
	{
		(*philo)[i].eat_n = 0;
		(*philo)[i].var = var;
		(*philo)[i].id = i + 1;
		(*philo)[i].fork = *f;
		i++;
	}
	var->av_philo = var->n_philo;
	var->is_alive = 1;
	return (0);
}

void	*to_do(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2)
		usleep(1500);
	while (philo->var->av_philo)
	{
		ft_eat(philo);
		if (philo->var->n_eat != -1)
			philo->eat_n++;
		if (philo->eat_n == philo->var->n_eat)
		{
			pthread_mutex_lock(&(philo->var->eat));
			philo->var->av_philo--;
			pthread_mutex_unlock(&(philo->var->eat));
			return (0);
		}
		sleepnthink(philo);
	}
	return (0);
}

int	manager(t_var *var)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*f;

	i = 0;
	philo = 0;
	f = 0;
	if (initializer(var, &philo, &f))
		return (1);
	make_mutex(&f, &var, &philo);
	while (i < var->n_philo)
	{
		pthread_create(&var->ph[i], NULL, to_do, &philo[i]);
		pthread_detach(var->ph[i++]);
	}
	is_dead(philo, var);
	destroy_mutex(&var, &philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_var	var;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid arguments");
		return (1);
	}
	if (is_valid(av))
		return (2);
	var.n_eat = -1;
	var.n_philo = ft_atoi(av[1]);
	var.t_die = ft_atoi(av[2]);
	var.t_eat = ft_atoi(av[3]);
	var.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var.n_eat = ft_atoi(av[5]);
	if (var.n_philo <= 0 || var.t_die <= 0 || var.t_eat <= 0
		|| var.t_sleep <= 0)
		return (3);
	if (manager(&var))
		return (4);
	return (0);
}
