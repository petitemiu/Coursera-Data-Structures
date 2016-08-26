#include <stdio.h>
#include <stdlib.h>

typedef struct llist_t{
	struct llist_t* prev;
	struct llist_t* next;
	char data;
} llist_t;

typedef struct stack_t{
	struct stack_t* prev;
	char data;
} stack_t;

llist_t* llist_create(char value){
	llist_t* list = malloc(sizeof(llist_t));
	list->prev = NULL;
	list->next = NULL;
	list->data = value;
	return list;
}

llist_t* llist_add(llist_t* list, char value){
	llist_t* entry = llist_create(value);
	entry->prev = list;
	list->next = entry;
	return entry;
}

llist_t* llist_remove_first(llist_t* head){
	llist_t* entry = head->next;
	free(head);
	return entry;
}

llist_t* llist_remove_last(llist_t* tail){
	llist_t* entry = tail->prev;
	free(tail);
	return entry;
}

stack_t* stack_create(char value){
	stack_t* stack = malloc(sizeof(stack));
	stack->data = value;
	stack->prev = NULL;
	return stack;
}

stack_t* push(stack_t* stack, char value){
	stack_t* entry = stack_create(value);
	entry->prev = stack;
	return entry;
}

stack_t* pop(stack_t* stack){
	stack_t* pointer = stack->prev;
	free(stack);
	return pointer;
}

int main(void){
	char tmp;
	scanf("%c", &tmp);
	llist_t *head = llist_create(tmp);
	llist_t *tail = head;
	stack_t *stack = NULL;

	while(scanf("%c", &tmp)){
		if(tmp == '\n'){
			break;
		}
		tail = llist_add(tail, tmp);
	}
	
	size_t open = 1, close = 1, unclosed = 0, pos = 0;
	while( head != NULL ){
		++pos;
		char sym = head->data;
		if( sym == '(' || sym == '[' || sym =='{') {
			stack = push(stack, sym);
			++open;
			unclosed = pos;
		}
		else if(sym == ')' || sym == ']' || sym == '}'){
			++close;
			if( stack == NULL){
				printf("%lu", pos);
				exit(0);
			}
			char top = stack->data;
			stack = pop(stack);
			if ( (top == '[' && sym != ']') || 
				(top == '(' && sym != ')') ||
				(top == '{' && sym != '}') ){
				printf("%lu", pos);
				exit(0);
			} 
			else{
			--unclosed;
			}
		}
		head = llist_remove_first(head);
	}
	if(open > close){
		printf("%lu", unclosed);
	}
	else{
		puts("Success");
	}
	return 0;
}
