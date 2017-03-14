#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	char* data;
	struct node* nextNode;
} Node;


typedef struct LinkedQueue {
	Node* head;
	Node* tail;
	int count;

} LinkedQueue;

void CreateQueue(LinkedQueue** Queue);
void DestroyQueue(LinkedQueue* Queue);

Node* CreateNode(char* newNode);
void DestroyNode(Node* _Node);
void Enqueue(LinkedQueue* Queue, Node* newNode);
Node* Dequeue(LinkedQueue* Queue);

int IsEmpty(LinkedQueue* Queue);