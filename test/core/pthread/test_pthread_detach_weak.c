#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *worker_thread(void *arg) {
	printf("worker_thread\n");

	// Infinite loop
	while (1) {}

	return NULL;
}

int main() {
	pthread_t thread;

	printf("main\n");
	int rc = pthread_create(&thread, NULL, worker_thread, NULL);
	assert(rc == 0);

	// Make the thread weakly referenced
	rc = pthread_detach(thread);
	assert(rc == 0);

	// Sleep a bit to let the thread execute its entry point
	sleep(1);

	printf("done\n");
	return 0;
}
