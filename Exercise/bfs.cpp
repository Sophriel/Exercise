#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int mX, mY;

int solution(vector<vector<int>> maps)
{
	int answer = -1;

	mX = maps[0].size();
	mY = maps.size();

	queue<pair<int, int>> nodes;

	nodes.push({ 0, 0 });

	while (!nodes.empty())
	{
		int nx = nodes.front().first;
		int ny = nodes.front().second;
		int nw = maps[nodes.front().second][nodes.front().first];
		nodes.pop();

		if (nx == mX - 1 && ny == mY - 1)
			return nw;

		//  ©Л
		if (nx + 1 < mX && maps[ny][nx + 1] == 1)
		{
			nodes.push({ nx + 1, ny });
			maps[ny][nx + 1] += nw;
		}

		//  го
		if (ny + 1 < mY && maps[ny + 1][nx] == 1)
		{
			nodes.push({ nx, ny + 1 });
			maps[ny + 1][nx] += nw;
		}

		//  аб
		if (nx - 1 > -1 && maps[ny][nx - 1] == 1)
		{
			nodes.push({ nx - 1, ny });
			maps[ny][nx - 1] += nw;
		}

		//  ╩С
		if (ny - 1 > -1 && maps[ny - 1][nx] == 1)
		{
			nodes.push({ nx, ny - 1 });
			maps[ny - 1][nx] += nw;
		}
	}

	return answer;
}

int main()
{
	solution({ { 1, 0, 1, 1, 1 }, { 1, 0, 1, 0, 1 }, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1} });
	return 0;
}