// https://github.com/emscripten-core/emscripten/issues/15762

#include <pthread.h>

pthread_t other_thread;

static void* thread_main(void* arg) {
  return NULL;
}

int main(int argc, char* argv[]) {
  pthread_create(&other_thread, NULL, thread_main, NULL);
}
