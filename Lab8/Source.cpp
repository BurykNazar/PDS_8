#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<stack>
#include<string>
#include<sstream>

#include<Windows.h>

#define ui unsigned int

using namespace std;

vector<vector<ui>> graph;
vector<int> dfsNumber;
ui verCt, edgCt;

bool readGraph(const string& path) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "������� ��� ������� ����� ��� ����������." << endl;
		return false;
	}
	if (!(file >> verCt >> edgCt)) {
		cerr << "������� ��� ��������� ������� ������ �� ����� �����." << endl;
		return false;
	}
	graph.clear();
	graph.resize(verCt);
	for (ui i = 0; i < edgCt; i++) {
		ui u, v;
		if (!(file >> u >> v)) {
			cerr << "������� � �������� ����� �����." << endl;
			return false;
		}
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}
	file.close();
	return true;
}

void print() {
	cout << "�������� ������:" << endl;
	for (ui i = 0; i < graph.size(); i++) {
		cout << "������� " << (i + 1) << ": {";
		for (ui j = 0; j < graph[i].size(); j++) {
			cout << (graph[i][j] + 1);
			if (j < graph[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << "}" << endl;
	}
}

void printDFSStack(const stack<int>& stk, int colWidth) {
	stack<int> temp = stk;
	stringstream ss;
	ss << "[";
	bool first = true;
	while (!temp.empty()) {
		if (!first)
			ss << ", ";
		ss << (temp.top() + 1);
		temp.pop();
		first = false;
	}
	ss << "]";
	cout << left << setw(colWidth) << ss.str();
}

void printLine(int totalWidth) {
	cout << "+" << string(totalWidth - 2, '-') << "+" << endl;
}


void dfs(int start, const vector<vector<ui>>& graph) {
	vector<bool> isVisited(graph.size(), false);
	dfsNumber.clear();
	dfsNumber.resize(graph.size(), -1);
	stack<int> stk;
	size_t dfsCount = 0;

	stk.push(start);
	isVisited[start] = true;
	dfsNumber[start] = ++dfsCount;

	const int colWidth = 20;
	const int totalWidth = colWidth * 3 + 4;

	printLine(totalWidth);
	cout << "| " << left << setw(colWidth - 2) << "������� �������"
		<< " | " << setw(colWidth - 2) << "DFS-�����"
		<< " | " << setw(colWidth - 2) << "���� �����" << " |" << endl;
	printLine(totalWidth);

	while (!stk.empty()) {
		int curr = stk.top();
		cout << "| " << left << setw(colWidth - 2) << (curr + 1)
			<< " | " << setw(colWidth - 2) << dfsNumber[curr]
			<< " | ";
		printDFSStack(stk, colWidth - 2);
		cout << " |" << endl;
		printLine(totalWidth);

		bool isFUnv = false;
		for (int neighbor : graph[curr]) {
			if (!isVisited[neighbor]) {
				isVisited[neighbor] = true;
				dfsNumber[neighbor] = ++dfsCount;
				stk.push(neighbor);
				isFUnv = true;
				break;
			}
		}
		if (!isFUnv)
			stk.pop();
	}
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	string path;
	cout << "������ ���� ��� ���������� �����: ";

	getline(cin, path);
	if (!readGraph(path)) {
		return 1;
	}
	print();
	ui fDFS;
	cout << "������ ����� ������� ��� ������ �����: ";
	cin >> fDFS;
	if (fDFS < 1 || fDFS > graph.size()) {
		cerr << "������� ��� ������ ���� ������ �����."
			<< endl;
		return 2;
	}
	cout << "�������� ������ ������������� �����:" << endl;
	dfs(fDFS - 1, graph);
	return 0;
}