#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10
#define MAX 100

typedef struct {
    int lower, upper, thno;
} args;

void* compute(void* arg) {
    args *a = (args *)arg;
    int l = a->lower;
    int u = a->upper;
    int n = a->thno;
    int c = 0;
    printf("Sub thread :%d\n", n);
    for (int i = l; i <= u; i++) {
        c = 0;
        for (int j = 2; j <= (i / 2); j++) {
            if (i % j == 0)
                c++;
        }
        if (c == 0 && i != 1)  // Ensure that 1 is not considered as a prime number
            printf("%d ", i);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thid[N];
    args *a1;

    for (int i = 0; i < N; i++) {
        a1 = malloc(sizeof(args));  // Allocate memory for each thread's argument
        a1->lower = (i * (MAX / N) + 1);
        a1->upper = (a1->lower + (MAX / N) - 1);
        a1->thno = i;
        pthread_create(&thid[i], NULL, compute, (void*)a1);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thid[i], NULL);
    }

    return 0;
}

