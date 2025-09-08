#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Queue {
    int arr[SIZE];
    int front, rear;
};

void init(struct Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int val) {
    if ((q->rear + 1) % SIZE == q->front) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % SIZE;
    q->arr[q->rear] = val;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return val;
}

// Stack using two queues
struct Stack {
    struct Queue q1, q2;
};

// Method-2: Pop costly
void push(struct Stack* s, int val) {
    enqueue(&s->q1, val);
    printf("Pushed %d\n", val);
}

int pop(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }

    // Move until only one left
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int val = dequeue(&s->q1); // last element = top of stack

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return val;
}

int main() {
    struct Stack s;
    init(&s.q1);
    init(&s.q2);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    return 0;
}

