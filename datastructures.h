#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#define MAX_STEPS 1000
#define MAX_SIZE 100

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure
typedef struct {
    Node* top;
    int size;
} Stack;

// Queue structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} Queue;

// Metrics tracker structure
typedef struct {
    long long operations;
    int max_recursion_depth;
    int current_depth;
    int steps[MAX_STEPS][MAX_SIZE];
    int step_sizes[MAX_STEPS];
    int step_count;
    double execution_time_ms;
} ExecutionMetrics;

// Function declarations for Stack
Stack* create_stack();
void stack_push(Stack* s, int value);
int stack_pop(Stack* s);
int stack_is_empty(Stack* s);

// Function declarations for Queue
Queue* create_queue();
void queue_enqueue(Queue* q, int value);
int queue_dequeue(Queue* q);
int queue_is_empty(Queue* q);

// Metrics helper
void record_step(ExecutionMetrics* metrics, int arr[], int size);

#endif