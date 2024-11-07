#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab8\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestReadGraph_Success)
		{
			string testPath = "testGraph.txt";
			ofstream testFile(testPath);
			testFile << "3 3\n1 2\n2 3\n3 1\n";
			testFile.close();

			Assert::IsTrue(readGraph(testPath));
			Assert::AreEqual(verCt, (ui)3);
			Assert::AreEqual(edgCt, (ui)3);
			Assert::AreEqual(graph[0].size(), (size_t)2);
			Assert::AreEqual(graph[1].size(), (size_t)2);
			Assert::AreEqual(graph[2].size(), (size_t)2);
		}

		TEST_METHOD(TestReadGraph_FileNotFound)
		{
			string testPath = "nonExistentFile.txt";
			Assert::IsFalse(readGraph(testPath));
		}

		TEST_METHOD(TestDFS_Traversal)
		{
			string testPath = "testGraph.txt";
			ofstream testFile(testPath);
			testFile << "3 3\n1 2\n2 3\n3 1\n";
			testFile.close();

			ifstream input(testPath);
			if (!(input >> verCt >> edgCt)) {
				cerr << "Помилка при зчитуванні графа з файлу." << endl;
				Assert::Fail();
			}
			graph.clear();
			graph.resize(verCt);
			for (unsigned int i = 0; i < edgCt; i++) {
				unsigned int u, v;
				input >> u >> v;
				graph[u - 1].push_back(v - 1);
				graph[v - 1].push_back(u - 1);
			}
			input.close();

			stack<int> stk;
			stk.push(0);
			vector<bool> isVisited(verCt, false);

			size_t dfsCount = 0;

			dfs(0, graph);

			Assert::AreEqual(dfsNumber[0], 1);
			Assert::AreEqual(dfsNumber[1], 2);
			Assert::AreEqual(dfsNumber[2], 3);
		}

	};
}
