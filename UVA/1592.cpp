#include <bits/stdc++.h>
using namespace std;
const int maxn = 10005;
vector<int> table[maxn];
map<string, int> num;
int getId(string str)
{
	if(!num.count(str))
		num[str] = num.size();
	return num[str];
}
int main()
{
	int n, m;
	while(cin>> n >> m)
	{
		getchar();//接收空格
		num.clear();
		for(int i = 0; i < n; i++)
		{
			string str, substr;
			getline(cin, str);
			stringstream in(str);
			table[i].clear();
			while(getline(in, substr, ','))//可以利用getline和stringstream进行字符串的分割
			{
				int id = getId(substr);
				table[i].push_back(id);
			}
		}
		
		bool isPNF = true;
		for(int c1 = 0; c1 < m - 1 && isPNF; c1++)
		{
			for(int c2 = c1 + 1; c2 < m && isPNF; c2++)
			{
				map<pair<int, int>, int> gp;//gp放在里面，防止出现(r1,c1),(r1,c2)与(r2,c3),(r2,c4)相等的情况
				for(int r = 0; r < n && isPNF; r++)
				{
					int num1 = table[r][c1];
					int num2 = table[r][c2];
					pair<int, int> p(num1, num2);
					if(!gp.count(p))
						gp[p] = r;
					else
					{
						cout << "NO" << endl;
						cout << gp[p] + 1 << " " << r + 1 << endl;
						cout << c1 + 1 << " " << c2 + 1 << endl;
						isPNF = false;
					}
				}
			}
		}
		if(isPNF)
			cout << "YES" << endl;
	}
	return 0;
} 
