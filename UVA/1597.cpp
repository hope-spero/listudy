#include <bits/stdc++.h>
using namespace std;
int n, m;
map< string, vector< pair<int, int> > > mp;//每个单词对应的文章号和行号 
vector<string> doc[110];//文章 
int main()
{
	cin >> n; getchar();
	for(int i = 0; i < n; i++)
	{
		int line = 0; string s;
		while(getline(cin, s) && s[0] != '*')//输入文章 
		{
			doc[i].push_back(s);
			for(auto& c : s)
				if(!isalpha(c)) c = ' ';//将非字母转换为空格 
				else c = tolower(c);
			stringstream in(s);
			string word;
			while(in >> word)
				mp[word].push_back(make_pair(i, line)); //包含该单词的文章号和文章行号 
			line += 1;
		}
	}
	cin >> m; getchar();
	while(m--)
	{
		string op; getline(cin, op);
		string word;
		int i = op.find(' '), j = op.rfind(' ');//寻找第一个空格和最后一个空格位置
		set< pair<int, int> > out;
		if(i == string::npos) //查找单个单词 
			out.insert(mp[op].begin(), mp[op].end());
		else//与或非 
		{
			if(op[0] == 'N')//非 
			{
				word = op.substr(i + 1);
				set<int> _set;
				for(int i = 0; i < n; i++)
					_set.insert(i);
				for(auto p : mp[word])
					_set.erase(p.first);
				for(auto p : _set)
				{
					for(auto line: doc[p])
						cout << line << endl;
					if(p != *_set.rbegin())
						cout <<"----------"<<endl;
				}
				if(_set.empty())
					cout << "Sorry, I found nothing." << endl;
			}
			else//与或 
			{
				string word1 = op.substr(0, i); string word2 = op.substr(j + 1);
				out.insert(mp[word1].begin(), mp[word1].end());
				out.insert(mp[word2].begin(), mp[word2].end());
				if(j - i == 4)
				{
					set<int> s1, s2;
					for(auto p : mp[word1])
						s1.insert(p.first);
					for(auto p : mp[word2])
						if(s1.find(p.first) != s1.end())
							s2.insert(p.first);
					auto tmp = out;
					for(auto p : tmp)
						if(s2.find(p.first) == s2.end())
							out.erase(p);
				}
			}
		}
		int pre = -1;
		if(op[0] != 'N')
		{
			for(auto p : out)
			{
				if(pre != -1 && pre != p.first)
					cout <<"----------"<<endl;
				pre = p.first; 
				cout << doc[p.first][p.second] << endl;
			}
			if(out.empty())
				cout << "Sorry, I found nothing." << endl;
		}
		cout <<"==========" <<endl;
	}	
	return 0;	
} 
