#include <stdio.h>
#include <unistd.h>

static inline void perform_countdown() {
	for (int i = 8; i; --i) {
		printf("%d\n", i);
		sleep(1);
	}
	puts("liftoff");
	sleep(1);
}

static inline void wait_for_next_countdown() {
	for (int i = 17; i; --i) {
		puts("..");
		sleep(3);
	}
}

int main() {
	for (;;) {
		perform_countdown();
		wait_for_next_countdown();
	}
}
