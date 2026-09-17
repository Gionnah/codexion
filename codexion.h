/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 22:47:27 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 22:38:32 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_data
{
	long	number_of_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	long	time_of_compiles_required;
	long	dongle_cooldown;
	char	*scheduler;
}	t_data;

struct						s_simulation;
typedef struct s_queues		t_queues;
typedef struct s_coder		t_coder;

typedef struct s_dongle
{
	int				is_available;
	long			availability_time;
	t_queues		*queue;
	int				queue_size;	
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int					id;
	long				last_compile_start;
	int					compile_count;
	int					left_dongle;
	int					right_dongle;
	struct s_simulation	*simulation;
	pthread_t			thread;
}	t_coder;

typedef struct s_simulation
{
	t_data			*data;
	t_dongle		*dongles;
	t_coder			*coders;
	int				is_simulation_stopped;
	long			simulation_start_time;
	long			queue_order;
	pthread_mutex_t	scheduler_mutex;
	pthread_cond_t	scheduler_cond;
	pthread_t		monitor_thread;
	pthread_mutex_t	simulation_stop_mutex;
	pthread_mutex_t	simulation_log_mutex;
	pthread_mutex_t	simulation_state_mutex;
}	t_simulation;

typedef struct s_queues
{
	t_coder	*coder;
	int		order;
	long	priority;
}	t_queues;

int				ft_is_integer_value(char *s);
int				ft_is_valid_args(int ac, char **av);
void			*ft_monitor_routine(void *arg);
int				ft_is_simulation_stopped(t_simulation *simulation);
long			ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_get_max(int a, int b);
int				ft_get_min(int a, int b);
t_data			*ft_get_arg_value(char **av);
int				ft_set_simulation_stopped(t_simulation *simulation);
t_simulation	*ft_init_simulation(t_data *data);
int				ft_init_coders(t_simulation *simulation);
int				ft_init_dongles(t_simulation *simulation);
int				ft_start_simulation(t_simulation **simulation, t_data *args);
int				ft_create_coder_threads(t_simulation *simulation);
int				ft_join_coder_threads(t_simulation *simulation);
void			*ft_coder_routine(void *arg);
void			ft_release_dongle(t_coder *coder);
int				ft_acquire_dongle(t_coder *coder);
void			ft_compile(t_coder *coder);
void			ft_debug(t_coder *coder);
void			ft_refactor(t_coder *coder);
int				ft_all_coders_finished(t_simulation *simulation);
long			ft_get_current_time_in_ms(void);
struct timespec	ft_get_timeout(long availability_time);
int				ft_request_before(t_queues *a, t_queues *b);
void			ft_heap_push(t_dongle *dongle, t_queues request);
void			ft_heap_pop(t_dongle *dongle);
t_queues		*ft_heap_peek(t_dongle *dongle);
t_queues		ft_create_queue(t_coder *coder, int order);
int				ft_get_queue_order(t_simulation *simulation);
int				ft_is_first_request(t_dongle *dongle, t_coder *coder);
int				ft_can_acquire_both(t_coder *coder);
void			ft_add_request(t_coder *coder, t_queues *request);
void			ft_remove_request(t_coder *coder);
void			ft_update_dongles(t_simulation *simulation);
void			ft_log_state(t_coder *coder, char *state);
int				ft_init_scheduler(t_simulation *simulation);
int				ft_init_mutexes(t_simulation *simulation);

#endif
