/* A Simple buffered queue based producer consumer.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 * Compile : gcc prod_consume_cond_variables.c -lpthread
 */

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t prod_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t cons_cv = PTHREAD_COND_INITIALIZER;

#define MAXSIZE 50
typedef struct Q_s {
	int buf[MAXSIZE];
	int current_size;
	int tail, head;
} Q_t;

Q_t g_Q;
int g_counter;

void enqueue(Q_t *Q, int n)
{
	while (Q->current_size == MAXSIZE) {
		pthread_cond_wait(&cons_cv, &mutex);
	}

	Q->buf[Q->tail] = g_counter++;
	Q->tail = (Q->tail + 1) % MAXSIZE;
	Q->current_size++;
	if (Q->current_size == 1) {
		pthread_cond_broadcast(&prod_cv);
	}
}

int dequeue(Q_t *Q) {
	int n;
	while (Q->current_size == 0) {
		pthread_cond_wait(&prod_cv, &mutex);
	}

	n = Q->buf[Q->head];
	Q->head = (Q->head + 1 ) % MAXSIZE;
	if (Q->current_size == MAXSIZE) {
		pthread_cond_broadcast(&cons_cv);
	}
	Q->current_size--;

	return n;
}

void *producer(void *arg)
{
	while (1) {
		pthread_mutex_lock(&mutex);

		printf("p");
		enqueue(&g_Q, g_counter);

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *consumer(void *arg)
{
	while (1) {
		pthread_mutex_lock(&mutex);

		printf("c");
		printf(" Got number %d \n", dequeue(&g_Q));

		pthread_mutex_unlock(&mutex);
		sleep(10);
	}
}

#define CONSUMERS 10
#define PRODUCERS 100

int main()
{
	pthread_t tids[PRODUCERS + CONSUMERS];

	int c = 0, i;

	for (i = 0; i < PRODUCERS; i++) {
		pthread_create(&tids[c++], NULL, producer, NULL);
	}
	for (i = 0; i < CONSUMERS; i++) {
		pthread_create(&tids[c++], NULL, consumer, NULL);
	}

	for (i = 0; i < (PRODUCERS + CONSUMERS); i++) {
		pthread_join(tids[i], NULL);
	}
}
