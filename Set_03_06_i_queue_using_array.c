#include <stdio.h>
#include <stdlib.h>
#define SIZE 5   // maximum size of queue

int queue[SIZE];
int front = -1, rear = -1;

// Check if queue is full
int isFull() {
    return ((rear + 1) % SIZE == front);
}

// Check if queue is empty
int isEmpty() {
    return (front == -1);
}

// Enqueue operation
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is FULL!\n");
        return;
    }
    if (front == -1) front = 0;  // first insertion
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("Inserted %d\n", value);
}

// Dequeue operation
int dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int data = queue[front];
    if (front == rear) {
        // Queue becomes empty
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
    return data;
}

// Display queue
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();
    printf("Deleted: %d\n", dequeue());
    display();
    enqueue(50);
    enqueue(60);
    display();
    enqueue(70); // will show full
    return 0;
}

