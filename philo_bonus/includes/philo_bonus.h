/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:51 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/11 10:52:55 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	struct s_var	*var;
	sem_t			*fork_pile;
	struct timeval	last_meal_time;
	struct timeval	curr;
}					t_philo;

typedef struct s_var
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				is_alive;
	int				av_philo;
	int				*ph_id;
	struct timeval	start;
}					t_var;

int					ft_atoi(const char *str);
int					is_valid(char **av);
#endif
