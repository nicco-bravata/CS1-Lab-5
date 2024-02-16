#include <stdio.h>
#include <stdlib.h>

/*
Nicco Bravata
Lab Assignment 4
COP3502C-24Spring 0028
02/08/2024
*/

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{

	//Num_nodes is set to zero, so in the event that the head is null,
	//the while loop is skipped entirely and we correctly return 0 for the number of nodes
	int num_nodes = 0;
	//A temp helper is created to loop through the list
	node *tmp = head;

	//Loop through the list until there are no more nodes, increment the node
	//counter with each loop
	while(tmp != NULL) {
		num_nodes++;
		tmp = tmp->next;
	}

	//Return the number of nodes in the list
	return num_nodes;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	//A temp helper is created to loop through the list
	node *tmp = head;

	//If there is no head node, return a null value for the string
	if (tmp == NULL) {
		return NULL;
	}

	//If there is a single node in the list...
	if (tmp->next == NULL) {
		//Allocate a string the size of a single character
		char *single_message = malloc(sizeof(char) * 1);
		//Set the only element in the string equal to the letter in the head
		single_message[0] = tmp->letter;
		//Return the string containing one character
		return single_message;
	}

	//Dynamically allocate a string with the same length as the linked list
	char *message = malloc(sizeof(char) * length(head));
	//Set the first element in the string equal to the character in the head
	message[0] = tmp->letter;
	//Create an integer variable that tells us which node we are currently
	//iterating through
	int num_nodes = 1;

	//While there is still another node in the list...
	while (tmp->next != NULL) {
		//Loop to the next node in the list
		tmp = tmp->next;
		//Set the element of the string equal to the current node's character
		message[num_nodes] = tmp->letter;
		//Increase the number of nodes traversed
		num_nodes++;
	}

	//Return the string gathered from the linked list
	return message;

}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	//Dynamically allocate a new node to add to the end of the list
	node *newNode = (node*)malloc(sizeof(node));

	//If the new node cannot be allocated, print an appropriate error message
	if (newNode == NULL) {
		printf("Error allocating space for new node, storage full?\n");
	}

	//Initialize the proper values and pointers for the new node
	newNode->letter = c;
	newNode->next = NULL;

	//Create a temporary helper node
	node *tmp = *pHead;

	//If the head of the list doesn't exist, the new node becomes the head
	if (*pHead == NULL) {
		*pHead = newNode;
		return;
	}

	//While there are more nodes in the list...
	while (tmp->next != NULL) {
		//Set the temp equal to the next node until it reaches the last node
		tmp = tmp->next;
	}

	//The last node will now point to the new node, adding the new node to
	//the end of the list
	tmp->next = newNode;
	return;

}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//Create a temporary helper node
	node *tmp = *pHead;
	//While the current node is not null...
    while (tmp != NULL) {
		//Move the head to the next node
        *pHead = tmp->next;
		//and free the current node
        free(tmp);
		//before setting the current node equal to the next node.
        tmp = *pHead;
    }
	//Set the last remaining node equal to null
    *pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}