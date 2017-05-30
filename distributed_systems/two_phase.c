/* Sample code to demonstrate two phase commit algorithm
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 *
 * Takes a delta value from client and applies it to
 * two variables. Think of it as transferring money from account
 * A to account B.
 */
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
int x = 100;
int y = 200;
int delta;

enum state_s {
	UNINIT,
	PREPARE,
	PREPARED,
	COMMIT,
	COMMITTED
};

typedef enum state_s state_t;

state_t status[MAX];

void *consumer(void *arg)
{
	int id = *(int *)arg;
	char filename[255];
	char filename1[255];
	char xtion[255];

	sprintf(filename, "Thread.%d.tmp", id);
	sprintf(filename1, "Thread.%d.final", id);

//	printf("Starting thread %d\n", id);
	while(1) {
		switch(status[id]) {
			case PREPARE:
				{
				int fd = open(filename, O_WRONLY|O_CREAT, 0755);
				if (fd == -1) {exit(-1);}
				printf("delta is %d\n", delta);
				bzero(xtion, sizeof(xtion));
				int nbytes = sprintf(xtion, "old_val = %d, %d, delta = %d\n",
						x, y, delta);
				write(fd, xtion, nbytes);
				close(fd);
				status[id] = PREPARED;
				break;
				}
			case COMMIT:
				{
				int fd = open(filename1,
						O_WRONLY|O_CREAT, 0755);
				if (fd == -1) {exit(-1);}

				bzero(xtion, sizeof(xtion));
				int nbytes = sprintf(xtion, "new_val = %d, %d\n", x + delta,
								     y - delta);
				write(fd, xtion, nbytes);
				close(fd);
				status[id] = COMMITTED;
				break;
				}
			default:
				sleep(1);
		}
	}
}

void wait_for_status(state_t id)
{
	int i;
	while (1) {
		int count = 0;
		for (i = 0; i < MAX; i++) {
			if (status[i] == id) count++;
		}
		if (count == MAX) break;
		sleep(1);
	}
}

void set_state(state_t id)
{
	int i;
	for (i = 0; i < MAX; i++) {
		status[i] = id;
	}
}

int main()
{
	pthread_t tid[MAX];
	int i;

	int id[MAX];

	for (i = 0; i < MAX; i++) {
		id[i] = i;
		pthread_create(&tid[i], NULL, consumer, &id[i]);
	}

	printf("X = %d, y = %d\n", x, y);
	printf("Enter the delta to be applied : ");
	scanf("%d", &delta);

	printf("Sendig the request to %d slaves\n", MAX);
	set_state(PREPARE);
	wait_for_status(PREPARED);
	set_state(COMMIT);
	wait_for_status(COMMITTED);

	printf("Final committed value = %d, %d\n", x + delta, y - delta);
}
