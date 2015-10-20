/* By aleung-c, 42 */

#include "thread_testing.h"

void identify_cur_thread(t_thread_test_struct *th_test_struct)
{
	pthread_t	cur_tid;

	cur_tid = pthread_self();
	if (cur_tid == th_test_struct->tid[0])
		printf("Thread 1 active\n");
	else if (cur_tid == th_test_struct->tid[1])
		printf("Thread 2 active\n");
	else if (cur_tid == th_test_struct->tid[2])
		printf("Thread 3 active\n");
	else if (cur_tid == th_test_struct->tid[3])
		printf("Thread 4 active\n");
}

void calculate_ten_thousands(t_thread_test_struct *th_test_struct)
{
	int i;
	float work_val1;
	float work_val2;

	identify_cur_thread(th_test_struct);
	i = 0;
	work_val1 = 46.75;
	work_val2 = 64.72;
	while (i < 2500)
	{
		work_val1 = fabs(work_val1 * work_val2 * work_val2 * 80.6) * cos(work_val2); // useless calculation for proc work.
		th_test_struct->base_val += 1.0;
		th_test_struct->turn_nb++;
		i++;
	}
	printf("Thread finished: base_val = %.2f\n", th_test_struct->base_val);
	pthread_mutex_unlock(&(th_test_struct->lock));
}

void init_struct_var(t_thread_test_struct *th_test_struct)
{
	identify_cur_thread(th_test_struct);
	th_test_struct->start_point = 0;
	th_test_struct->turn_nb = 0;
	th_test_struct->base_val = 0;
	printf("Thread finished: variables set\n");
}

int main(void)
{
	int i;
	int err;
	t_thread_test_struct th_test_struct;
	
	// Mutex init;
	if (pthread_mutex_init(&(th_test_struct.lock), NULL) != 0)
    {
        printf("Mutex init failed\n");
        return 1;
    }
    // Using one of the four thread to init struct variables.
    err = pthread_create(&(th_test_struct.tid[0]), NULL, (void *)&init_struct_var, (void *)&th_test_struct);
	if (err != 0)
		printf("Can't create thread: [%s]", strerror(err));
	else
		printf("Thread created successfully\n");
	pthread_join(th_test_struct.tid[0], NULL); // block the main: init before all.
    i = 0;
	while (i < 4)
	{
		pthread_mutex_lock(&(th_test_struct.lock));
		err = pthread_create(&(th_test_struct.tid[i]), NULL, (void *)&calculate_ten_thousands, (void *)&th_test_struct);
		if (err != 0)
			printf("Can't create thread: [%s]", strerror(err));
		else
			printf("Thread created successfully\n");
		i++;
	}
	// Blocking main for the four threads.
	i = 0;
	while (i < 4)
	{
		pthread_join(th_test_struct.tid[i], NULL);
    	i++;
	}
	pthread_mutex_destroy(&(th_test_struct.lock));
	printf("Total work finished: turns done = %d\n", th_test_struct.turn_nb);
	return (0);
}
