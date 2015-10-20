#ifndef THREAD_TESTING_H
# define THREAD_TESTING_H

# include <sys/types.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

typedef struct			s_thread_test_struct {
	// thread stocking.
	pthread_t			tid[4];
	pthread_mutex_t		lock;

	int					start_point;
	int					turn_nb;
	float				base_val;
}						t_thread_test_struct;

#endif
