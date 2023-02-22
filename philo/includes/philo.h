/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 23:13:00 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/22 15:02:21 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				eat_n;
	int				id;
	struct s_var	*var;
	pthread_mutex_t	*fork;
	struct timeval	start;
	struct timeval	last_meal_time;
	struct timeval	curr;
}					t_philo;

typedef struct s_var
{
	pthread_mutex_t	eat;
	pthread_mutex_t	death_check;
	pthread_mutex_t	print_l;
	int				is_alive;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				av_philo;
	struct timeval	tmp;
	struct timeval	curr;
	pthread_t		*ph;
}					t_var;

int					ft_atoi(const char *str);
int					ft_time(struct timeval start, struct timeval curr);
void				ft_wait(int wait_time);
void				ft_eat(t_philo *philo);
int					make_mutex(pthread_mutex_t **f, t_var **var,
						t_philo **philo);
void				sleepnthink(t_philo *philo);
int					is_valid(char **av);
void				destroy_mutex(t_var **var, t_philo **philo);
#endif
