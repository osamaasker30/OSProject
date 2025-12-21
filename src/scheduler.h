#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

#define PRIORITY_REALTIME 0
#define PRIORITY_HIGH     1
#define PRIORITY_MEDIUM   2
#define PRIORITY_LOW      3
#define PRIORITY_MAX      5

/* ---------- TASK ---------- */
typedef struct Task {
    int id;
    int arrival_time;
    int priority;
    int current_priority;
    int burst_time;
    int remaining_time;
    int last_queue_time;
    struct Task* next;
} Task;

/* ---------- QUEUE ------------ */
typedef struct {
    Task* front;
    Task* rear;
    int size;
} Queue;

/* ---------- SCHEDULER ----------- */
typedef struct {
    Queue* realtime_queue;
    Queue* high_queue;
    Queue* medium_queue;
    Queue* low_queue;
    Queue* input_queue;

    Task* current_task;
    int current_time;
    int task_counter;
    int just_started;
} Scheduler;

Queue* create_queue(void);
bool is_queue_empty(Queue* q);
void enqueue(Queue* q, Task* t);
Task* dequeue(Queue* q);

Task* create_task(int at, int pr, int bt, int id);
void print_msg(Task* t, const char* msg, int time);

Scheduler* create_scheduler(void);
void load_tasks_from_file(Scheduler* s, const char* file);
void run_scheduler(Scheduler* s);

#endif
