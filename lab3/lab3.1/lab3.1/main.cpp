#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct node
{
	char inf[256];  // �������� ����������
	int priority;
	struct node* next; // ������ �� ��������� ������� 
};

struct node* head = NULL, * last = NULL, * f = NULL; // ��������� �� ������ � ��������� �������� ������
int dlinna = 0;

// ������� ���������� ��������, ��������� ������
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // ������� ���������� ��������
struct node* get_struct(void); // ������� �������� ��������

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice = 1;

	while (choice)
	{
		printf("�������� ��������:\n");
		printf("(1) �������� ������\n");
		printf("(2) ���������� �������� � ������\n");
		printf("(3) �������� �������� �� ������\n");
		printf("(4) ����� �������� � ������\n");
		printf("(0) ����� �� ���������\n\n");
		printf("��� �����: ");
		scanf("%d", &choice);

		system("cls");

		switch (choice)
		{
		case 1:
			review();
			system("pause");
			system("cls");
			break;
		case 2:
			spstore();
			system("pause");
			system("cls");
			break;
		case 3:
			printf("������� ���������� ��������\n>> ");
			scanf("%s", find_el);
			del(find_el);
			system("pause");
			system("cls");
			break;
		case 4:
			printf("������� ���������� ��������\n>> ");
			scanf("%s", find_el);
			find(find_el);
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int prior;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");   // ������ ������
	scanf("%s", s);
	printf("������� ��������� �������: \n");
	scanf("%d", &prior);

	if (*s == 0 || !prior)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}

	strcpy(p->inf, s);
	p->priority = prior;
	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

/* ���������� � ������ �������� */
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;

	}
	else if ((head->priority > p->priority) && p != NULL) // ���� ��������� ����� head
	{
		p->next = head;
		head = p;
		last = p->next;
	}
	else if ((p->priority > last->priority) && p != NULL) // ���� ����� ������� ����������� ����� last
	{
		last->next = p;
		last = p;
	}
	else if (head != NULL && p != NULL)
	{
		if (head->next == NULL && p != NULL) // ���� ������� ���� � ������, � ����� �������� ����� ����
		{
			head->next = p;
			last = p;
			return;
		}

		struct node* prev = head; // �������, ����� �������� ����� �������� �����
		struct node* struc = prev->next;

		while (struc)
		{
			if (struc->priority > p->priority)
			{
				p->next = struc;
				prev->next = p;
			}
			prev = struc;
			struc = struc->next;
		}
	}

	return;
}

/* �������� ����������� ������. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		printf("��� - %s, ��������� - %d\n", struc->inf, struc->priority);

		//printf("��� - %s, \n", struc->inf);
		struc = struc->next;
	}

	// ������� 1. ������� � ������������ ����������

	/*for (int p = 0; p < 5; p++)
	{
		struc = head;
		while (struc)
		{
			if (struc->priority == p + 1)
			{
				printf("��� - %s, ��������� - %d \n", struc->inf, struc->priority);
			}
			struc = struc->next;
		}
	}
	*/

	return;
}

/* ����� �������� �� �����������. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("������� �� ������\n");
	return NULL;
}

/* �������� �������� �� �����������. */
void del(char* name)
{
	struct node* struc = head; // ���������, ���������� �� ������ ���������� �� ������ ������
	struct node* prev = NULL;// ��������� �� �������������� ���������� �������
	int flag = 0;      // ��������� ���������� ���������� �������� � ������

	if (head == NULL) // ���� ������ ������ ����� NULL, �� ������ ����
	{
		printf("������ ����\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // ���� ��������� ������� - ������
	{
		flag = 1;
		head = struc->next; // ������������� ������ �� ��������� �������
		free(struc);  // ������� ������ �������
		struc = head; // ������������� ��������� ��� ����������� ������
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // ������ �� ������ � ����� ���������� ��������
	{
		if (strcmp(name, struc->inf) == 0) // ���� �����, ��
		{
			flag = 1;         // ���������� ���������
			if (struc->next)  // ���� ��������� ������� �� ��������� � ������
			{
				prev->next = struc->next; // ������ ���������
				free(struc);		    // �������  �������
				struc = prev->next; // ������������� ��������� ��� ����������� ������
			}
			else			// ���� ��������� ������� ��������� � ������
			{
				prev->next = NULL; // �������� ��������� ��������������� ��������
				free(struc);	// �������  �������
				last = prev;
				return;
			}
		}
		else // ���� �� �����, ��
		{
			prev = struc; // ������������� ��������� ��� ����������� ������
			struc = struc->next;
		}
	}

	if (flag == 0)				// ���� ���� = 0, ������ ������ ������� �� ������
	{
		printf("������� �� ������\n");
		return;
	}
}