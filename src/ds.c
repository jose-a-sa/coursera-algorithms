#include "ds.h"
#include "utils.h"
#include <limits.h>

queue_t * queue_init(size_t capacity)
{
    queue_t *q;
    if ((q = (queue_t *)malloc(sizeof(queue_t))) == NULL)
        error("failed to malloc queue_t pointer in queue_init");

    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1;

    if ((q->array = (int *)malloc(capacity * sizeof(int))) == NULL)
        error("failed to malloc int pointer in queue_init");

    return q;
}

bool queue_full(queue_t *q)
{
    return (q->size == q->capacity);
}

bool queue_empty(queue_t *q)
{
    return (q->size == 0);
}

void queue_enqueue(queue_t *q, int item)
{
    if (queue_full(q))
        return;

    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = item;
    q->size = q->size + 1;
}

int queue_dequeue(queue_t *q)
{
    if (queue_empty(q))
        return INT_MIN;

    int item = q->array[q->front];

    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;

    return item;
}

int queue_front(queue_t *q)
{
    if (queue_empty(q))
        return INT_MIN;

    return q->array[q->front];
}

int queue_rear(queue_t *q)
{
    if (queue_empty(q))
        return INT_MIN;

    return q->array[q->rear];
}

stackt_t* stack_init(size_t capacity)
{
    stackt_t* s;
    if ((s = (stackt_t *)malloc(sizeof(stackt_t))) == NULL)
        error("failed to malloc stackt_t pointer in stack_init");

    s->capacity = capacity;
    s->top = -1;
    
    if ((s->array = (int *)malloc(capacity * sizeof(int))) == NULL)
        error("failed to malloc int pointer in stack_init");

    return s;
}

bool stack_full(stackt_t* s)
{
    return s->top == s->capacity - 1;
}
 
bool stack_empty(stackt_t* s)
{
    return s->top == -1;
}

void stack_push(stackt_t* s, int item)
{
    if (stack_full(s))
        return;
    
    s->array[++s->top] = item;
}

int stack_pop(stackt_t* s)
{
    if (stack_empty(s))
        return INT_MIN;
    
    return s->array[s->top--];
}

int stack_peek(stackt_t* s)
{
    if (stack_empty(s))
        return INT_MIN;
    
    return s->array[s->top];
}