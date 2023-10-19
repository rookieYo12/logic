#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root; // ��������� �� ������ ������

struct Node* CreateTree(struct Node* root, struct Node* r, int data); // ��������
void print_tree(struct Node* r, int l); // �����
void SearchData(struct Node* r, int d); // �����

int main()
{
	// ���� � ����� �� �������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int d, start = 1;

	root = NULL;
	printf("-1 - ��������� ���������� ������\n");
	while (start)
	{
		printf("������� �����: ");
		scanf_s("%d", &d);
		if (d == -1)
		{
			printf("���������� ������ ��������\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, d);

	}

	print_tree(root, 0);

	printf("\n������� �����, ������� ������ �����: ");
	scanf("%d", &d);
	SearchData(root, d);

	return 0;
}

// ������� �������� ������
struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL) // ���� ����� ��� ���� �������
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("������ ��������� ������!");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r; // �������� ��������� �����

		// ����������� ���� � ��������
		if (data > root->data) root->left = r;
		else root->right = r;
		return r;
	}

	// ������������ �� ������ � ������� �������� ��� ���������� ������ ����
	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

// ������� ������ ������
void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

void SearchData(struct Node* r, int d)
{
	if (d == r->data)
	{
		printf("������� ������!\n");
		return;
	}
	else if (r->left && d > r->data)
	{
		SearchData(r->left, d);
	}
	else if (r->right && d < r->data)
	{
		SearchData(r->right, d);
	}
	else
	{
		printf("������� �� ������!\n");
		return;
	}

	return;
}