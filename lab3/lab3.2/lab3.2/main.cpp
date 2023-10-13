#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// ������� 2. ���������� �������

struct node
{
	char inf[256];  // �������� ����������
	struct node *next; // ������ �� ��������� �������
};

struct node* head = NULL, * last = NULL, * f = NULL; // ��������� �� ������ � ��������� �������� ������
int dlinna = 0;

// ������� ���������� ��������, ��������� ������
void spstore(void), review(void), del(char* name), pop(int choice);

char find_el[256];
struct node* find(char* name); // ������� ���������� ��������
struct node* get_struct(void); // ������� �������� ��������

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice = 1;
	int choice4 = 1;

	while (choice)
	{
		printf("����� ������ - %d\n\n", dlinna);
		printf("�������� ��������:\n");
		printf("(1) �������� ������\n");
		printf("(2) ���������� �������� � ������\n");
		printf("(3) �������� ������ �������� �� ������\n");
		printf("(4) ���������� ������� �������� �� ������\n");
		printf("(5) ����� �������� � ������\n");
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
			printf("�������� ��������:\n");
			printf("(1) ������� � ����������� ��������\n");
			printf("(2) ������� � ��������� ��������\n\n");
			printf("��� �����: ");
			scanf("%d", &choice4);
			system("cls");
			pop(choice4);
			system("pause");
			system("cls");
			break;
		case 5:
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

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");   // ������ ������
	scanf("%s", s);

	if (*s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}

	strcpy(p->inf, s);
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
		dlinna += 1;
	}
	else if (head != NULL && p != NULL) // ������ ��� ����, �� ��������� � �����
	{
		last->next = p;
		last = p;
		dlinna += 1;
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
		printf("��� - %s,\n", struc->inf);
		struc = struc->next;
	}
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
		dlinna -= 1;
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
				dlinna -= 1;
			}
			else			// ���� ��������� ������� ��������� � ������
			{
				prev->next = NULL; // �������� ��������� ��������������� ��������
				free(struc);	// �������  �������
				last = prev;
				dlinna -= 1;
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

void pop(int choice)
{
	struct node* struc = head;

	if (choice && choice < 3)
	{
		if (struc == NULL)
		{
			printf("������ ����\n");
			return;
		}

		if (choice == 1)
		{
			printf("%s\n", struc->inf);
		}
		else if (choice == 2)
		{
			head = struc->next;
			printf("%s\n", struc->inf);
			free(struc);
			dlinna -= 1;
		}
	}
	else
	{
		printf("�� ���������� ����� ����!\n");
	}
}