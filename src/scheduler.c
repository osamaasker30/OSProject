#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------------- QUEUE ---------------- */
Queue* create_queue(void) {
    Queue* q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

bool is_queue_empty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, Task* t) {
    t->next = NULL;
    if (!q->rear)
        q->front = q->rear = t;
    else {
        q->rear->next = t;
        q->rear = t;
    }
    q->size++;
}

Task* dequeue(Queue* q) {
    if (!q->front) return NULL;
    Task* t = q->front;
    q->front = t->next;
    if (!q->front) q->rear = NULL;
    q->size--;
    t->next = NULL;
    return t;
}

/* ---------------- SCHEDULER ---------------- */

Scheduler* create_scheduler(void) {
    Scheduler* s = malloc(sizeof(Scheduler));
    s->realtime_queue = create_queue();
    s->high_queue = create_queue();
    s->medium_queue = create_queue();
    s->low_queue = create_queue();
    s->input_queue = create_queue();
    s->current_task = NULL;
    s->current_time = 0;
    s->task_counter = 0;
    s->just_started = 0;
    return s;
}

void load_tasks_from_file(Scheduler* s, const char* file) {
    FILE* f = fopen(file, "r");
    if (!f) {
        printf("Error: file not opened %s\n", file);
        exit(1);
    }
    int a,p,b;
    while (fscanf(f,"%d,%d,%d",&a,&p,&b)==3)
        enqueue(s->input_queue, create_task(a,p,b,s->task_counter++));
    fclose(f);
}

static void process_arrivals(Scheduler* s) {
    Task *p=NULL, *c=s->input_queue->front;
    while(c){
        if(c->arrival_time == s->current_time){
            Task* t = c;
            if(!p) s->input_queue->front = c->next;
            else p->next = c->next;
            if(t == s->input_queue->rear) s->input_queue->rear = p;
            c = c->next;
            s->input_queue->size--;

            t->last_queue_time = s->current_time;

            if(t->priority == PRIORITY_REALTIME)
                enqueue(s->realtime_queue, t);
            else if(t->priority == PRIORITY_HIGH)
                enqueue(s->high_queue, t);
            else if(t->priority == PRIORITY_MEDIUM)
                enqueue(s->medium_queue, t);
            else
                enqueue(s->low_queue, t);
        } else {
            p = c;
            c = c->next;
        }
    }
}

/* ---------- timeout ---------- */
static void handle_timeouts(Scheduler* s){
    Queue* qs[] = { s->high_queue, s->medium_queue, s->low_queue };
    for(int i=0;i<3;i++){
        Task *p=NULL,*c=qs[i]->front;
        while(c){
            if(s->current_time - c->last_queue_time >= 20){
                print_msg(c, "proses zamanasimi", s->current_time);
                if(!p) qs[i]->front = c->next;
                else p->next = c->next;
                if(c == qs[i]->rear) qs[i]->rear = p;
                Task* tmp = c;
                c = c->next;
                free(tmp);
                qs[i]->size--;
            } else {
                p = c;
                c = c->next;
            }
        }
    }
}

static Queue* select_queue(Scheduler* s){
    if(!is_queue_empty(s->realtime_queue)) return s->realtime_queue;
    if(!is_queue_empty(s->high_queue)) return s->high_queue;
    if(!is_queue_empty(s->medium_queue)) return s->medium_queue;
    if(!is_queue_empty(s->low_queue)) return s->low_queue;
    return NULL;
}

/* ================= RUN ================= */
/*==============prosesin baslamasi =======*/
void run_scheduler(Scheduler* s) {
    while (1) {

        process_arrivals(s);
        handle_timeouts(s);

        if (!s->current_task) {
            Queue* q = select_queue(s);
            if (q) {
                s->current_task = dequeue(q);
                print_msg(s->current_task, "proses basladi", s->current_time);
                s->just_started = 1;
            }
        }

        if (s->current_task && !s->just_started) {
            int log_time = s->current_time + 1;
            s->current_task->remaining_time--;

            if (s->current_task->remaining_time == 0) {
                print_msg(s->current_task, "proses sonlandi", log_time);
                free(s->current_task);
                s->current_task = NULL;
            }
            else if (s->current_task->priority == PRIORITY_REALTIME) {
                print_msg(s->current_task, "proses yurutuluyor", log_time);
            }
            else {
                print_msg(s->current_task, "proses askida", log_time);
                if (s->current_task->current_priority < PRIORITY_MAX)
                    s->current_task->current_priority++;

                s->current_task->last_queue_time = log_time;

                if (s->current_task->current_priority == PRIORITY_HIGH)
                    enqueue(s->high_queue, s->current_task);
                else if (s->current_task->current_priority == PRIORITY_MEDIUM)
                    enqueue(s->medium_queue, s->current_task);
                else
                    enqueue(s->low_queue, s->current_task);

                s->current_task = NULL;
            }
        }

        if (!s->just_started)
            s->current_time++;

        s->just_started = 0;

        if (is_queue_empty(s->input_queue) &&
            is_queue_empty(s->realtime_queue) &&
            is_queue_empty(s->high_queue) &&
            is_queue_empty(s->medium_queue) &&
            is_queue_empty(s->low_queue) &&
            !s->current_task)
            break;
    }
}
