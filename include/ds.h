#ifndef DS_H_
#define DS_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct queue_t
{
    int front, rear;
    size_t size, capacity;
    int *array;
} queue_t;

typedef struct stackt_t
{
    int top;
    size_t capacity;
    int *array;
} stackt_t;

queue_t *queue_init(size_t);
bool queue_full(queue_t *);
bool queue_empty(queue_t *);
void queue_enqueue(queue_t *, int);
int queue_dequeue(queue_t *);
int queue_front(queue_t *);
int queue_rear(queue_t *);

stackt_t *stack_init(size_t);
bool stack_full(stackt_t *);
bool stack_empty(stackt_t *);
void stack_push(stackt_t *, int);
int stack_pop(stackt_t *);
int stack_peek(stackt_t *);

#endif