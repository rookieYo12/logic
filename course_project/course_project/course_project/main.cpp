#include<iostream>
#include<vector>
#include<conio.h>
#include<time.h>
#include<locale.h>
#include <stack>
#include <string>
#include <iomanip>
#include <fstream>

int num = 1;
bool tit = 0;
using namespace std;

void traverse(int u, bool visited[], const int VALUE, int* graph[]);
bool isConnected(int* graph[], const int VALUE);
int isEulerian(int* graph[], vector<int>& degree, const int VALUE);
void create(int* graph[], const int VALUE);
void createCopy(int* graph[], int* graphCopy[], int const VALUE);
void FindWay(vector<int>& deg, vector<int>& res, int* graph[], const int VALUE);
void titul();
void count_vertex(int* count);
bool choiceFunc(int message);
void outputFile(int* graph[], vector<int>& degree, vector<int>& res, int const VALUE, int check);

int main() {
	system("cls");
	setlocale(LC_ALL, "RUS");

	if (!tit)
		titul();

	srand((unsigned)time(0));

	int VALUE = 0;

	count_vertex(&VALUE);

	vector<int> deg(VALUE); // для хранения степени вершин
	vector<int> res;

	int** graph = new int* [VALUE];
	for (int i = 0; i < VALUE; i++)
	{
		graph[i] = new int[VALUE];
	}

	int** graphCopy = new int* [VALUE];
	for (int i = 0; i < VALUE; i++)
	{
		graphCopy[i] = new int[VALUE];
	}

	create(graph, VALUE);
	createCopy(graph, graphCopy, VALUE);

	int check = isEulerian(graph, deg, VALUE);

	switch (check) {
	case 0:
		cout << "Граф не является Эйлеровым.";
		break;
	case 1:
		cout << "Граф имеет Эйлеров цикл.\n";
		FindWay(deg, res, graph, VALUE);
		break;
	case 2:
		cout << "Граф имеет Эйлеров путь.\n";
		FindWay(deg, res, graph, VALUE);
		break;
	default:
		break;
	}

	if (choiceFunc(1))
	{
		outputFile(graphCopy, deg, res, VALUE, check);
	}

	for (int i = 0; i < VALUE; i++)
	{
		delete[] graph[i];
		delete[] graphCopy[i];
	}
	delete graph;
	delete graphCopy;

	if (choiceFunc(2))
	{
		num++;
		main();
	}
	else
		return 0;
}

void titul() {
	printf("\n");
	printf(" Министерство науки и высшего образования Российской Федерации\n");
	printf(" Пензенский государственный университет\n");
	printf(" Кафедра «Вычислительная техника»\n");

	printf("\n\n");
	printf(" КУРСОВОЙ ПРОЕКТ\n");
	printf(" по дисциплине:\n ЛОГИКА И ОСНОВЫ АЛГОРИТМИЗАЦИИ В ИНЖЕНЕРНЫХ ЗАДАЧАХ\n");
	printf(" тема проекта:\n РЕАЛИЗАЦИЯ АЛГОРИТМА НАХОЖДЕНИЯ ЭЙЛЕРОВЫХ ЦИКЛОВ\n ");

	printf("\n\n\n");
	printf(" Выполнил:\n");
	printf(" студент группы 22ВВП1\n");
	printf(" Харитонов А.А.\n");
	printf("\n\n");
	printf(" Принял:\n");
	printf(" Акифьев И.В.\n");
	printf("\n\n\n");
	printf(" Пенза 2023\n\n\n");

	cout << ">> Нажмите любую клавишу, чтобы продолжить...";
	_getch();
	system("cls");

	tit = 1;
}

void count_vertex(int* count)
{
	bool flag = 0;

	do
	{
		string value;
		value.resize(5);
		cout << "Граф №" << num << endl << endl;
		cout << "Введите размерность графа [2; 10]: ";

		getline(cin, value);

		flag = 0;

		if (value[0] == '0')
			flag = 1;

		for (int i = 0; i < value.size(); i++)
		{
			if (!isdigit(value[i]) || isspace(value[i]))
				flag = 1;
		}

		if (!flag)
		{
			if (value.size() == 1 && std::atoi(value.c_str()) == 1)
				flag = 1;
			if (std::atoi(value.c_str()) > 10)
				flag = 1;
			if (value.size() == 0)
				flag = 1;
		}

		if (flag == 1)
		{
			cout << "!!! Введите корректное число вершин!" << endl << endl;
			cout << "> Нажмите любую клавишу, чтобы продолжить...";
			_getch();
			system("cls");
		}
		else
		{
			*count = std::atoi(value.c_str());
			break;
		}
	} while (flag);
}

bool choiceFunc(int message)
{
	bool flag = 0;

	do
	{
		string str;
		str.resize(5);

		switch (message)
		{
		case 1:
			cout << "\n\nСохранить в файл? (Да - 1 / Нет - 0): ";
			break;
		case 2:
			cout << "\n\nСоздать еще один граф? (Да - 1 / Нет - 0): ";
			break;
		default:
			break;
		}

		getline(cin, str);

		flag = 0;

		for (int i = 0; i < str.size(); i++)
		{
			if (!isdigit(str[i]) || isspace(str[i]))
				flag = 1;
		}

		if (!flag)
		{
			if (std::atoi(str.c_str()) > 1)
				flag = 1;
			if (str.size() > 1 && str[0] == '0')
				flag = 1;
			if (str.size() == 0)
				flag = 1;
		}

		if (flag)
		{
			cout << "!!! Введите корректное число!" << endl << endl;
			cout << "> Нажмите любую клавишу, чтобы продолжить...";
			_getch();
			system("cls");
		}
		else if (std::atoi(str.c_str()) == 1)
			return 1;
		else
		{
			return 0;
		}
	} while (flag);
}

// проверка на связность
void traverse(int u, bool visited[], const int VALUE, int* graph[]) {
	visited[u] = true;    //отмечаем вершины как посещенные

	for (int v = 0; v < VALUE; v++) {
		if (graph[u][v]) // проверка наличия путя
		{
			if (!visited[v]) traverse(v, visited, VALUE, graph); // если не посещалась, то переходим
		}
	}
}

bool isConnected(int* graph[], const int VALUE) {
	bool* vis = new bool[VALUE];

	//для всех вершин u в качестве начальной точки проверим, видны ли все узлы
	for (int u = 0; u < VALUE; u++)
	{
		for (int i = 0; i < VALUE; i++)	vis[i] = false;    // инициализируем, поскольку узел не посещался

		traverse(u, vis, VALUE, graph);

		for (int i = 0; i < VALUE; i++)
		{
			if (!vis[i])    //если есть узел, не посещенный обходом, граф не связан
				return false;
		}
	}
	return true;
}

// проверка на наличие Эйлерова пути или цикла
int isEulerian(int* graph[], vector<int>& degree, const int VALUE) {
	if (isConnected(graph, VALUE) == false)    //когда граф не связан
		return 0;

	int oddDegree = 0;

	for (int i = 0; i < VALUE; i++) {
		for (int j = 0; j < VALUE; j++) {
			if (graph[i][j])
				degree[i]++;    // увеличение степени, когда соединенный край найден
		}

		if (degree[i] % 2 != 0)    //когда степень вершин нечетна
			oddDegree++;  // подсчет вершин нечетной степени
	}

	cout << "Степень вершин\n";
	for (int i = 0; i < VALUE; i++)
	{
		cout << "Вершина " << i << " - " << degree[i] << endl;
	}cout << endl;

	if (oddDegree > 2)	// если > 2, то нет ни цикла, ни пути	
		return 0;
	else if (oddDegree == 0) // если = 0, то цикл	
		return 1;
	else // если = 2, то путь
		return 2;
}

// создание графа
void create(int* graph[], const int VALUE)
{
	for (int i = 0; i < VALUE; i++)
	{
		for (int j = 0; j < VALUE; j++)
		{
			if (i == j) graph[i][j] = 0;
			else if (j < i)
			{
				graph[i][j] = rand() % 2;
				graph[j][i] = graph[i][j];
			}
		}
	}

	for (int i = 0; i < VALUE; i++)
	{
		for (int j = 0; j < VALUE; j++)
		{
			cout << graph[i][j] << " ";
		}cout << endl;
	}cout << "\n";
}

void createCopy(int* graph[], int* graphCopy[], int const VALUE)
{
	for (int i = 0; i < VALUE; i++)
	{
		for (int j = 0; j < VALUE; j++)
		{
			graphCopy[i][j] = graph[i][j];
		}
	}
}

// поиск пути
void FindWay(vector<int>& deg, vector<int>& res, int* graph[], const int VALUE)
{
	int first = 0;
	while (!deg[first])  ++first;

	int v1 = -1, v2 = -1;
	bool bad = false;

	for (int i = 0; i < VALUE; ++i)
		if (deg[i] & 1)
		{
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;
		}


	if (v1 != -1)
		++graph[v1][v2], ++graph[v2][v1];

	stack <int> st;
	st.push(first);

	while (!st.empty()) // пока st не пустой
	{
		int v = st.top(); // v = самому верхнему элементу в стеке
		int i;
		for (i = 0; i < VALUE; ++i)
		{
			if (graph[v][i]) break;
		}

		if (i == VALUE)
		{
			res.push_back(v);
			st.pop();
		}
		else
		{
			--graph[v][i];
			--graph[i][v];
			st.push(i);
		}
	}

	// для цикла не используется
	if (v1 != -1)
	{
		for (size_t i = 0; i + 1 < res.size(); ++i)
		{
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
			{
				vector<int> res2;

				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);

				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);

				res = res2;

				break;

			}

		}
	}

	cout << "Путь:";

	for (size_t i = 0; i < res.size(); ++i)
		cout << " " << res[i] + 1;
}

void outputFile(int* graph[], vector<int>& degree, vector<int>& res, const int VALUE, int check)
{
	string fileName;
	cout << "Введите название файла: ";
	getline(cin, fileName);

	ofstream fout;
	fout.open(fileName);

	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		fout << "Количество вершин в графе: " << VALUE << endl << endl;

		for (int i = 0; i < VALUE; i++)
		{
			for (int j = 0; j < VALUE; j++)
			{
				fout << graph[i][j] << " ";
			}fout << endl;
		}fout << endl;

		fout << "Степень вершин\n";
		for (int i = 0; i < VALUE; i++)
		{
			fout << "Вершина " << i << " - " << degree[i] << endl;
		}fout << endl;

		switch (check)
		{
		case 0:
			fout << "Граф не является Эйлеровым.";
			break;
		case 1:
			fout << "Граф имеет Эйлеров цикл." << endl;

			fout << "Путь:";
			for (size_t i = 0; i < res.size(); ++i)
				fout << " " << res[i] + 1;
			break;
		case 2:
			fout << "Граф имеет Эйлеров путь.\n";

			fout << "Путь:";
			for (size_t i = 0; i < res.size(); ++i)
				fout << " " << res[i] + 1;
			break;
		default:
			break;
		}
	}

	fout.close();
}