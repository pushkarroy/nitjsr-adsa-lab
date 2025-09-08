#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Stack {
    int arr[SIZE];
    int top;
};

void init(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, int val) {
    if (s->top == SIZE - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = val;
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

// Method-1: Push costly
struct Queue {
    struct Stack s1, s2;
};

void enqueue(struct Queue* q, int val) {
    // Move all from s1 -> s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element into s1
    push(&q->s1, val);

    // Move back s2 -> s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    printf("Enqueued %d\n", val);
}

int dequeue(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    return pop(&q->s1);
}

int main() {
    struct Queue q;
    init(&q.s1);
    init(&q.s2);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    return 0;
}

