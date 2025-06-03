#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#define TICK_INTERVAL_NS 10000000
#define TEST_DURATION_SEC 5 

volatile sig_atomic_t tick_count = 0;

void tick_handler(int sig, siginfo_t *si, void *uc) {
    tick_count++;
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = tick_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    struct sigevent sev;
    timer_t timerid;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = TICK_INTERVAL_NS;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = TICK_INTERVAL_NS;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    printf("Timer started. Generating ticks every %.1f ms for %d seconds...\n",
           TICK_INTERVAL_NS / 1e6, TEST_DURATION_SEC);

    unsigned long dummy = 0;
    time_t start = time(NULL);
    while (time(NULL) - start < TEST_DURATION_SEC) {
        for (int i = 0; i < 1000000; i++) {
            dummy += i % 7;
        }
    }

    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    timer_settime(timerid, 0, &its, NULL);

    int expected_ticks = (TEST_DURATION_SEC * 1000000000L) / TICK_INTERVAL_NS;

    printf("\nExpected ticks: %d\n", expected_ticks);
    printf("Received ticks: %d\n", tick_count);
    printf("Missed ticks  : %d\n", expected_ticks - tick_count);

    return 0;
}
