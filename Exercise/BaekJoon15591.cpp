#include <iostream>
using namespace std;

#include <algorithm>
#include <vector>
#include <queue>

class Video
{
public:
	int VideoNumber;
	vector<pair<Video*, int>> RelatedVideos;
	bool VisitedVideos[5001];

public:
	void SetUSADO(int Num, int TargetNum, Video* TargetVideo, int r)
	{
		VideoNumber = Num;
		RelatedVideos.push_back({ TargetVideo, r });	
		VisitedVideos[VideoNumber] = true;
	}

	int CountRelatedVideos(int minUSADO)
	{
		int count = 0;

		queue<pair<Video*, int>> q;
		q.push({this, 1000000000});
		fill_n(VisitedVideos, 5001, false);

		while (q.size())
		{
			pair<Video*, int> cur = q.front();
			q.pop();

			VisitedVideos[cur.first->VideoNumber] = true;

			if (cur.second < minUSADO)
				continue;

			for (unsigned int i = 0; i < cur.first->RelatedVideos.size(); i++)
			{
				if (VisitedVideos[cur.first->RelatedVideos[i].first->VideoNumber])
					continue;

				int r = min(cur.first->RelatedVideos[i].second, cur.second);
				if (r >= minUSADO)
					count++;

				q.push({cur.first->RelatedVideos[i].first, r});
			}
		}

		return count;
	}
};

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(NULL);

	int N, Q;
	int p, q, r;
	int k, v;

	cin >> N >> Q;

	if (N < 2 || Q < 1 || Q > 5000)
		return 0;

	vector<Video> videos(N + 1);

	for (int i = 1; i < N; i++)
	{
		cin >> p >> q >> r;

		if (p < 1 || q > N || r < 1 || r > 1000000000)
			return 0;

		videos[p].SetUSADO(p, q, &videos[q], r);
		videos[q].SetUSADO(q, p, &videos[p], r);
	}

	for (int i = 0; i < Q; i++)
	{
		cin >> k >> v;

		if (k < 1 || k > 1000000000 || v < 1 || v > N)
			return 0;

		cout << videos[v].CountRelatedVideos(k) << "\n";
	}

	return 0;
}