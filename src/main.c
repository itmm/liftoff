#include <stdio.h>
#include <unistd.h>
#include <zephyr/kernel.h>

static int counter = 10;

static void perform_work();

static K_WORK_DELAYABLE_DEFINE(work, perform_work);

#define SECONDS_IN_COUNTDOWN 1
#define SECONDS_DURING_WAIT 3
#define SECONDS_BETWEEN_COUNTDOWNS 60
#define STARTING_SECONDS_FOR_COUNTDOWN 10

static inline void perform_countdown() {
	if (counter > 0) {
		printf("%d\n", counter);
		counter -= SECONDS_IN_COUNTDOWN;
		k_work_reschedule(&work, K_SECONDS(SECONDS_IN_COUNTDOWN));
	} else {
		puts("liftoff");
		counter = SECONDS_BETWEEN_COUNTDOWNS - SECONDS_DURING_WAIT;
		k_work_reschedule(&work, K_SECONDS(SECONDS_DURING_WAIT));
	}
}

static inline void wait_for_next_countdown() {
	puts("..");
	counter -= SECONDS_DURING_WAIT;
	k_work_reschedule(&work, K_SECONDS(SECONDS_DURING_WAIT));
}

static void perform_work() {
	if (counter <= STARTING_SECONDS_FOR_COUNTDOWN) {
		perform_countdown();
	} else {
		wait_for_next_countdown();
	}
}

int main() {
	k_work_schedule(&work, K_SECONDS(0));
	for (;;) { k_sleep(K_SECONDS(100)); }
}
