#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

// Enqueue operation
void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
        rear->next = front; // circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front; // maintain circular link
    }
    printf("Inserted %d\n", value);
}

// Dequeue operation
int dequeue() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int value;
    if (front == rear) {
        value = front->data;
        free(front);
        front = rear = NULL;
    } else {
        struct Node* temp = front;
        value = temp->data;
        front = front->next;
        rear->next = front; // maintain circular link
        free(temp);
    }
    return value;
}

// Display queue
void display() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue: ");
    struct Node* temp = front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
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
    return 0;
}

