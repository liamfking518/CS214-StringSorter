#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

struct node	//struct for nodes in linked list
{
	char* word;
	struct node* next;
};

struct node* head = NULL;	//initializing linked list head as null

struct node* create_node(char* arr)	//function for creating new node
{
	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	node->word = arr;
	node->next = NULL;
	return node;
}

void insert(char* str)		//inserts string into linked list
{
	if(head == NULL)
	{
		head = create_node(str);
		return;
	}
	else if(strcmp(str, head->word) <= 0)
	{
		struct node* node = create_node(str);
		node->next = head;
		head = node;
		return;
	}
	else
	{
		struct node* temp = head;
		struct node* prev = NULL;
		while(temp != NULL)
		{
			if(strcmp(str, temp->word) > 0)
			{
				prev = temp;
				temp = temp->next;
			}
			else
			{
				struct node* node = create_node(str);
				node->next = temp;
				prev->next = node;
				return;
			}
		}
		struct node* node = create_node(str);
		prev->next = node;
	}
	return;
}

void print()	//prints out sorted linked list
{
	struct node* temp = head;
	struct node* prev = NULL;
	while(temp != NULL){
		printf("%s\n", temp->word);
		prev = temp;
		temp = temp->next;
		free(prev->word);
		free(prev);
	}
}

int main(int argc, char * argv[])
{
	if(argc==1)		//outputs error if no arguments given
	{
		printf("ERROR: expected one argument. found zero\nexiting gracefully...\n");
		return -1;
	}
	else if(argc>2)		//outputs error if too many arguments given
	{
		printf("ERROR: expected one argument. found %d\nexiting gracefully...\n", (argc-1));
		return -1;
	}

	int length = 0;		//used to keep track of length of input string
	while(argv[1][length]!='\0')	//determines length of input string
	{
		length++;
	}

	int i;		//for loop counter
	int j = 0;	//used to keep track of each viable string in input
	int k;		//used to copy each found string to "word"
	int x;		//used when copying found strings to "word"
	char* word = NULL;
	for(i=0;i<length;i++)   //finds strings in input and calls insert
	{
		while(isalpha(argv[1][i]) != 0)	//finds last index of the next viable string
		{
			i++;
			j++;
		}
		if(j > 0)	//if string is found, copies it to "word" then inserts
		{
			char* word = (char*)malloc(sizeof(char)*(j+1));
			x=i-j;
			for(k=0;k<j;k++)
			{
				word[k] = argv[1][x+k];
			}
			word[k] = '\0';
			insert(word);
			j = 0;
			word = NULL;
		}
	}

	if(head != NULL)
	{
		print();
	}

	free(word);

	return 0;
}
