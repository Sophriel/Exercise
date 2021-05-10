#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <queue>
using namespace std;

int mX, mY;

class node
{
public:
	int x, y;
	int w, cnt;

	bool operator()(node a, node b)
	{
		return pow((mX - a.x), 2) + pow((mY - a.y), 2) + a.cnt > pow((mX - b.x), 2) + pow((mY - b.y), 2) + b.cnt;
	}
};


int solution(vector<vector<int> > maps)
{
	int answer = 99999999;

	mX = maps[0].size();
	mY = maps.size();

	priority_queue<node, vector<node>, node> nodes;

	node n;
	n.x = 0;
	n.y = 0;
	n.w = maps[0][0];
	n.cnt = 1;
	nodes.push(n);

	while (!nodes.empty())
	{
		int nx = nodes.top().x;
		int ny = nodes.top().y;
		int nw = nodes.top().w;
		int ncnt = nodes.top().cnt;
		nodes.pop();

		if (nx == mX-1 && ny == mY-1)
			return ncnt;

		if (nw == 1)
		{
			//  аб
			if (nx - 1 > -1)
			{
				node n;
				n.x = nx - 1;
				n.y = ny;
				n.w = maps[n.y][n.x];
				n.cnt = ncnt + 1;
				if (n.w == 1)
					nodes.push(n);
			}

			//  ©Л
			if (nx + 1 < mX)
			{
				node n;
				n.x = nx + 1;
				n.y = ny;
				n.w = maps[n.y][n.x];
				n.cnt = ncnt + 1;
				if (n.w == 1)
					nodes.push(n);
			}

			//  ╩С
			if (ny - 1 > -1)
			{
				node n;
				n.x = nx;
				n.y = ny - 1;
				n.w = maps[n.y][n.x];
				n.cnt = ncnt + 1;
				if (n.w == 1)
					nodes.push(n);
			}

			//  го
			if (ny + 1 < mY)
			{
				node n;
				n.x = nx;
				n.y = ny + 1;
				n.w = maps[n.y][n.x];
				n.cnt = ncnt + 1;
				if (n.w == 1)
					nodes.push(n);
			}
		}

		maps[ny][nx] = 0;		
	}

	if (answer > 0)
		return answer;
	else
		return -1;
}

int main()
{
	solution({{ 1, 0, 1, 1, 1 }, { 1, 0, 1, 0, 1 }, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1}});
	return 0;
}
