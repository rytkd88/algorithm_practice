#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<set>
#include<queue>
using namespace std;
typedef pair<int, int> ii;
int N, M, K;
int map[11][11];
int yang[11][11];
deque<pair<int, ii>> dq;
vector<pair<int, ii>> die;
ii dir[8] = { {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1} };

void spring()//¿©¸§µµ
{
	deque<pair<int, ii>> new_dq;
	while (!dq.empty())
	{
		int now_age = dq.front().first;
		ii now_pos = dq.front().second;
		dq.pop_front();
		if (map[now_pos.first][now_pos.second] >= now_age) {
			map[now_pos.first][now_pos.second] -= now_age;
			new_dq.push_back({ now_age + 1,now_pos });
		}
		else {
			die.push_back({ now_age,now_pos });
		}
	}
	swap(new_dq, dq);
}
void summer()
{
	for (int i = 0; i < die.size(); i++)
	{
		map[die[i].second.first][die[i].second.second] += die[i].first / 2;
	}
	die.clear();
}
void fall()
{
	deque<pair<int, ii>> new_dq;
	while (!dq.empty())
	{
		int now_age = dq.front().first;
		ii now_pos = dq.front().second;
		dq.pop_front();
		new_dq.push_back({ now_age,now_pos });
		if (now_age % 5 == 0)
		{
			for (int a = 0; a < 8; a++)
			{
				int ny = now_pos.first + dir[a].first;
				int nx = now_pos.second + dir[a].second;
				if (ny >= 0 && nx >= 0 && ny < N && nx < N)
				{
					new_dq.push_front({ 1,{ny,nx} });
				}
			}
		}
	}
	swap(new_dq, dq);
}
void winter()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] += yang[i][j];
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> yang[i][j];
			map[i][j] = 5;
		}
	}
	int x, y, z;
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y >> z;
		dq.push_back({ z,{x - 1,y - 1} });
	}
	while (K--)
	{
		spring();
		summer();
		fall();
		winter();
	}
	cout << dq.size();
	return 0;
}