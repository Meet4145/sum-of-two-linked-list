#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

void head_insert(Node** pHead, int value);
void reverse(Node** head);
Node* list_sum(Node* head1, Node* head2);
void print_list(Node* head);
void destroy_list(Node* head);

int main(int argc, char* argv[])
{
	//add up 189 + 11
	Node* head1 = NULL;
	Node* head2 = NULL;
	Node* head_sum = NULL;
	//create a list for the number 189
	head_insert(&head1, 9);
	head_insert(&head1, 8);
	head_insert(&head1, 1);
	//create a list for the number 11
	head_insert(&head2, 1);
	head_insert(&head2, 1);
	head_sum = list_sum(head1, head2);
	printf("The sum of ");
	print_list(head1);
	printf(" + ");
	print_list(head2);
	printf("\n");
	printf(" = ");
	print_list(head_sum);
	printf("\n");
	//clean up three lists
	destroy_list(head1); head1 = NULL;
	destroy_list(head2); head2 = NULL;
	destroy_list(head_sum); head_sum = NULL;
	return 0;
}


void head_insert(Node** pHead, int value)
{
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		printf("Failed to allocate space for %d node.\n", value);
		exit(1);
	}
	temp->data = value;
	temp->next = *pHead;
	*pHead = temp;
}

Node* list_sum(Node* head1, Node* head2)
{
	Node* head_1 = head1;
	Node* head_2 = head2;

	reverse(&head_1);
	reverse(&head_2);

	Node* temp_head1 = head_1;
	Node* temp_head2 = head_2;
	Node* new_node = NULL;

	int carry = 0;
	int sum;

	while (temp_head1 != NULL || temp_head2 != NULL || carry > 0) {
		sum = 0;

		if (temp_head1 != NULL) {
			sum += temp_head1->data;
			temp_head1 = temp_head1->next;
		}

		if (temp_head2 != NULL) {
			sum += temp_head2->data;
			temp_head2 = temp_head2->next;
		}

		sum = sum + carry;
		carry = sum / 10;
		sum = sum % 10;
		head_insert(&new_node, sum);
	}

	if (carry > 0)
	{
		int new_carry = carry % 10;
		head_insert(&new_node, new_carry);
		new_carry = new_carry / 10;
	}

	reverse(&head_1);
	reverse(&head_2);

	return new_node;
}

void print_list(Node* head)
{
	while (head != NULL) {
		printf("%d", head->data);
		head = head->next;
	}
}

void reverse(Node** head)
{
	Node* previous = NULL;
	Node* current = *head;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*head = previous;
}

void destroy_list(Node* head)
{
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}