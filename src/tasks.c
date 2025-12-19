#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------------- COLORS ---------------- */
static const char* colors[] = {
    "\033[1;31m","\033[1;32m","\033[1;33m","\033[1;34m",
    "\033[1;35m","\033[1;36m","\033[1;91m","\033[1;92m"
};
#define COLOR_RESET "\033[0m"
#define NUM_COLORS 8

Task* create_task(int at, int pr, int bt, int id) {
    Task* t = malloc(sizeof(Task));
    t->id = id;
    t->arrival_time = at;
    t->priority = pr;
    t->current_priority = pr;
    t->burst_time = bt;
    t->remaining_time = bt;
    t->last_queue_time = at;
    t->next = NULL;
    return t;
}

void print_msg(Task* t, const char* msg, int time) {
    printf("%s%d.%04d sn %s (id:%04d oncelik:%d kalan sure:%d sn)%s\n",
           colors[t->id % NUM_COLORS],
           time, 0,
           msg,
           t->id,
           t->current_priority,
           t->remaining_time,
           COLOR_RESET);
}
