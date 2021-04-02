#include <iostream>
#include <algorithm>
using namespace std;

#include <vector>
#include <queue>

vector <pair<int, int>> Fields(2001);
int Parents[2001];

inline int pow2(int a)
{
	return a * a;
}

inline int getLength(pair<int, int> a, pair<int, int> b)
{
	return pow2(a.first - b.first) + pow2(a.second - b.second);
}

//  union find
inline int findParent(int field)
{
	if (field == Parents[field])
		return field;

	return Parents[field] = findParent(Parents[field]);
}

class Edge
{
public:
	int from, to;
	int cost;

	Edge() {}
	Edge(int f, int t, int c) : from(f), to(t), cost(c) {}

	bool operator() (Edge *a, Edge *b)
	{
		return a->cost > b->cost;
	}
};

priority_queue<Edge*, vector<Edge*>, Edge> Pipes;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, C;
	int TotalCost = 0;

	cin >> N >> C;

	//  필드 셋업
	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;

		Fields[i] = { x, y };
		Parents[i] = i;

		//  파이프 전부 연결
		for (int j = 0; j < i; j++)
		{
			int c = getLength(Fields[i], Fields[j]);

			if (c >= C)
				Pipes.push(new Edge(i, j, c));
		}
	}

	//  필요한 파이프만 고르기
	int connection = 0;
	while (!Pipes.empty())
	{
		int fParent = findParent(Pipes.top()->from);
		int tParent = findParent(Pipes.top()->to);

		if (fParent != tParent)
		{
			Parents[fParent] = min(Parents[fParent], Parents[tParent]);
			Parents[tParent] = min(Parents[fParent], Parents[tParent]);

			TotalCost += Pipes.top()->cost;
			connection++;
		}

		Pipes.pop();

		if (connection == N - 1)
			break;
	}

	if (connection == N - 1)
		cout << TotalCost;

	else
		cout << -1;

	return 0;
}