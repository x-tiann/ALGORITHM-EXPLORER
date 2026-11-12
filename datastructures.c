#include <stdio.h>
#include <stdlib.h>
#include "datastructures.h"

// --- Custom Stack Implementation ---
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void stack_push(Stack* s, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}

int stack_pop(Stack* s) {
    if (s->top == NULL) return -1;
    Node* temp = s->top;
    int popped = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return popped;
}

int stack_is_empty(Stack* s) {
    return s->top == NULL;
}

// --- Custom Queue Implementation ---
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void queue_enqueue(Queue* q, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (q->tail == NULL) {
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->size++;
}

int queue_dequeue(Queue* q) {
    if (q->head == NULL) return -1;
    Node* temp = q->head;
    int data = temp->data;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    free(temp);
    q->size--;
    return data;
}

int queue_is_empty(Queue* q) {
    return q->head == NULL;
}

// --- Metrics Helper ---
void record_step(ExecutionMetrics* metrics, int arr[], int size) {
    if (metrics->step_count < MAX_STEPS) {
        for (int i = 0; i < size; i++) {
            metrics->steps[metrics->step_count][i] = arr[i];
        }
        metrics->step_sizes[metrics->step_count] = size;
        metrics->step_count++;
    }
}