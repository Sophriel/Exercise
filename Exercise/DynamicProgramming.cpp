#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

//  ���α׷��ӽ� N���� ���
int solution(int N, int number) {
	int answer = 0;

	//"N"*(i+1)�� �ʱ�ȭ
	vector<set<int>> arr(8);
	for (int i = 0; i < 8; i++) {
		int n = 0;
		int digit = i + 1;
		while (digit > 0) {
			digit--;
			n += N * pow(10, digit);
		}
		arr[i].insert(n);
	}
	//[DP] ��Ģ�������� ������ ���� ��� Ȯ��
	for (int i = 1; i < 8; i++) {
		for (int j = 0; j < i; j++) {
			for (auto &x : arr[j]) {
				for (auto &y : arr[i - j - 1]) {
					arr[i].insert(x + y);
					arr[i].insert(x*y);
					arr[i].insert(x - y);
					if (y != 0) arr[i].insert(x / y);
				}
			}
		}
		//number�� �ִ��� Ȯ��
		if (arr[i].find(number) != arr[i].end()) {
			return i + 1;
		}
	}
	//1���� 8���� �߿� return ������ -1 return
	return -1;
}

//  ȿ������ ȭ�� ����
int main()
{
	int N, M;
	cin >> N >> M;

	vector<int> coins;
	vector<int> counts(M + 1);

	for (int i = 0; i < N; i++)
	{
		int c;
		cin >> c;
		coins.push_back(c);
	}

	sort(coins.begin(), coins.end());

	for (int i = 1; i < coins.front(); i++)
		counts[i] = -1;

	for (int i = 0; i < coins.size() && coins[i] <= M; i++)
		counts[coins[i]] = 1;

	for (int i = coins.front() + 1; i < counts.size(); i++)
	{
		if (counts[i] == 1)
			continue;

		int ex = i;
		int minCoin = coins.front();
		while (ex != 0)
		{
			for (int j = 0; j < coins.size(); j++)
			{
				if (coins[j] > ex || counts[ex - coins[j]] == -1)
					continue;

				if (counts[ex - minCoin] > counts[ex - coins[j]] || counts[ex - minCoin] == -1)
					minCoin = coins[j];
			}
			counts[i] += counts[minCoin];
			ex -= minCoin;

			if (ex < 0)
			{
				cout << -1;
				return 0;
			}
		}
	}

	cout << counts[M - 1];

	return 0;
}