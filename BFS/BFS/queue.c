#include "queue.h"

void CreateQueue(LinkedQueue** queue)
{
	(*queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	(*queue)->head = NULL;
	(*queue)->tail = NULL;
	(*queue)->count = 0;
}

void DestroyQueue(LinkedQueue** queue)
{
	while (!IsEmpty(queue)) {
		Node* popped = Dequeue(queue);
		DestroyNode(popped);
	}

	free(queue);
}

Node* CreateNode(char* data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = (char*)malloc(sizeof(newNode) + 1);

	strcpy(newNode->data, data);

	newNode->nextNode = NULL;

	return newNode;
}

void DestroyNode(Node* _Node)
{
	free(_Node->data);
	free(_Node);
}

void _Enqueue(LinkedQueue* queue, Node* newNode)
{
	if (queue->head == NULL) {
		queue->head = newNode;
		queue->tail = newNode;
		queue->count++;
	}
	else {
		queue->tail->nextNode = newNode;
		queue->tail = newNode;
		queue->count++;
	}
}

Node* _Dequeue(LinkedQueue* queue)
{
	Node* head = queue->head;

	if (queue->head->nextNode == NULL) {
		queue->head = NULL;
		queue->tail = NULL;
	}
	else {
		queue->head = queue->head->nextNode;
	}

	queue->count--;

	return head;
}

int IsEmpty(LinkedQueue *queue)
{
	return (queue->head == NULL);
}

