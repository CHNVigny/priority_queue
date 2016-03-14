#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
typedef char valuetype;

typedef struct node1
{
	struct node2 *head;
}queue;

typedef struct node2
{
	int weight;
	valuetype value[20];
	struct node2 *next;
}Node;

void creat(queue *q)
{
	q->head = (Node*)malloc(sizeof(Node));
	q->head->next = NULL;
}

Node *top(queue *q)
{
	return q->head->next;
}
int empty(queue *q)
{
	if (q->head->next == NULL)
		return 1;
	else
		return 0;
}

//按照最大优先级入队
void max_priority_push(queue *q, int weight, valuetype value[])
{
	//int a;
	Node *p = (Node*)malloc(sizeof(Node));
	Node *temp = q->head;
	p->weight = weight;
	strcpy(p->value, value);
	p->next = NULL;
	if (empty(q))
	{
		p->next = temp->next;
		temp->next = p;
	}
	else
	{
		//temp = temp->next;
		while (temp->next !=NULL && p->weight < temp->next->weight)
			temp = temp->next;
		if (temp != NULL)
		{
			p->next = temp->next;
			temp->next = p;
		}
		else
			temp = p;
		
	}
}

//按照最小优先级入队
void min_priority_push(queue *q, int weight, valuetype value[])
{
	Node *p = (Node*)malloc(sizeof(Node));
	Node *temp = q->head;
	p->weight = weight;
	strcpy(p->value, value);
	p->next = NULL;
	if (empty(q))
	{
		p->next = temp->next;
		temp->next = p;
	}
	else
	{
		//temp = temp->next;
		while (temp->next !=NULL && p->weight > temp->next->weight)
			temp = temp->next;
		if (temp != NULL)
		{
			p->next = temp->next;
			temp->next = p;
		}
		else
			temp = p;
	}
}

//弹出
Node *pop(queue *q)
{
	Node *temp = q->head->next;
	q->head->next = temp->next;
	return temp;
}

//删除：两种方式，按照weight 按照value
void delete_weight(queue *q, int weight)
{
	Node *temp = q->head;
	Node *l = NULL;
	if (empty(q))
		return;
	while (weight != temp->next->weight)
	{
		temp = temp->next;
	}
	while (temp->next != NULL && temp->next->weight == weight)
	{
		l = temp->next;
		temp->next = l->next;
		free(l);
	}
}

void delete_value(queue *q, valuetype value[])
{
	Node *temp = q->head;
	Node *l = NULL;
	if (empty(q))
		return;
	while (temp->next != NULL && strcmp(value, temp->next->value)!=0)
	{
		temp = temp->next;
	}
	while (temp->next != NULL && strcmp(temp->next->value, value)==0)
	{
		l = temp->next;
		temp->next = l->next;
		free(l);
	}
}

//查看队列
void check(queue *q)
{
	Node *temp = q->head->next;
	if (temp == NULL)
		printf("empty!\n");
	while (temp)
	{
		printf("weight=%d,value=%s\n", temp->weight, temp->value);
		temp = temp->next;
	}
}

int main()
{
	int option, cont=1, delete_option, check_option, insert_num, *weights, delete_w;
	valuetype delete_v[N];
	valuetype **values;
	queue max_q, min_q;
	creat(&max_q);
	creat(&min_q);
	
	while (cont)
	{
		printf("choose options please:\n1.insert\n2.delete\n3.check\n");//1插入 2删除 3查看
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			printf("how many numbers to insert?\n");
			scanf("%d", &insert_num);
			weights = (int*)malloc(insert_num*sizeof(int));
			values = (valuetype**)malloc(insert_num*sizeof(valuetype*));
			for (int i = 0; i < insert_num; i++)
			{
				values[i] = (valuetype*)malloc(N*sizeof(valuetype));
			}
			printf("input weight and value:\n");
			for (int i = 0;i < insert_num;i++)
			{
				scanf("%d", weights+i);
				getchar();
				gets(values[i]);
			}
			//printf("1.max priority\n2.min priority\n");
			//scanf("%d", &insert_option);
			for (int i = 0;i < insert_num;i++)
			{
				max_priority_push(&max_q, weights[i], values[i]);
				min_priority_push(&min_q, weights[i], values[i]);
			}
			free(weights);
			for (int i = 0;i < insert_num;i++)
			{
				free(values[i]);
			}
			free(values);
			printf("done!\n");
			break;
		case 2:
			printf("choose:\n1.according to weight\n2.according to value\n");
			scanf("%d", &delete_option);
			switch (delete_option)
			{
			case 1:
				printf("input weight:\n");
				scanf("%d", &delete_w);
				delete_weight(&max_q, delete_w);
				delete_weight(&min_q, delete_w);
				break;
			case 2:
				printf("input value:\n");
				getchar();
				gets(delete_v);
				delete_value(&max_q, delete_v);
				delete_value(&min_q, delete_v);
				break;
			default:
				break;
			}
			break;
		case 3:
			printf("how to check?\n1.max\n2.min\n");
			scanf("%d", &check_option);
			switch (check_option)
			{
			case 1:
				check(&max_q);
				break;
			case 2:
				check(&min_q);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		printf("continue?\n1/0\n");
		scanf("%d", &cont);

	}
	system("pause");
	return 0;
}