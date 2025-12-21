#include <stdio.h>
#include "scheduler.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s giris.txt\n", argv[0]);
        return 1;
    }
    //start proccess sceduler
    printf("=============================================\n");
    printf(" FreeRTOS  Scheduler Simulation\n");
    printf("=============================================\n\n");

    Scheduler* scheduler = create_scheduler();
    load_tasks_from_file(scheduler, argv[1]);
    run_scheduler(scheduler);

    printf("\nSimulation finished successfully\n");
    return 0;
}
