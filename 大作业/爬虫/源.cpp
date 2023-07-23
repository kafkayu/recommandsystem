#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<codecvt>
using namespace std;
class Video
{
public:
	vector<wstring>tags;
	int time;//(秒)
	wstring url;
};
class User
{
public:
	vector<wstring>pass_url;
	vector<wstring>user_tags;
	vector<wstring> showPass()
	{
		return this->pass_url;
	}
	void addUrl(wstring tmp_url)
	{
		this->pass_url.push_back(tmp_url);
	}
	vector<wstring> showTags()
	{
		return this->user_tags;
	}
	void changeTags(vector<wstring>tmp_user_tags)
	{
		this->user_tags = tmp_user_tags;
	}
	void addTags(wstring tmp_tags)
	{
		this->user_tags.push_back(tmp_tags);
	}
};
vector<vector<Video>>s_video;
vector<wstring>indexTags;
void get_sumTags()
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	ifstream in(L"c:/code/大作业_标签分类/data/summary.txt");
	string line_tmp;
	if (in)
	{
		//读入，导入数据
		getline(in, line_tmp);
		wstring line = conv.from_bytes(line_tmp);
		int index_l = 0;
		int index_r = -1;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '#')
			{
				index_l = index_r + 1;
				index_r = i;
				wstring tmpIndexTag = line.substr(index_l, index_r - index_l);
				indexTags.push_back(tmpIndexTag);
			}
		}
	}
}
void getIn()
{
	for (int k=0;k<indexTags.size();k++)
	{
		wstring tmpIndexTag = indexTags[k];
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		wstring path = L"c:/code/大作业_标签分类/data/";
		path.append(tmpIndexTag);
		path.append(L".txt");
		ifstream in(path);
		vector<Video>video;
		s_video.push_back(video);
		string line_tmp;
		if (in)
		{
			//读入，导入数据
			while (getline(in, line_tmp))
			{
				wstring line = conv.from_bytes(line_tmp);
				int len = line.length();
				int count_flag = 0;
				vector<wstring> tmp_tags;//存tag
				wstring tmp_url;//存url
				int tmp_time;//存时间
				int tmp_i = 0;
				for (int i = 0; i < len; i++)
				{
					//处理tags

					if ((line[i] == '#') && (count_flag == 0))
					{
						tmp_i = i;
						count_flag++;
						int tmp_l = 0;
						int tmp_r = -1;
						for (int j = 0; j < i; j++)
						{
							if (line[j] == '+')
							{
								tmp_l = tmp_r + 1;
								tmp_r = j;
								wstring str1 = line.substr(tmp_l, tmp_r - tmp_l);
								tmp_tags.push_back(str1);
							}
						}
						tmp_l = tmp_r + 1;
						tmp_r = i;
						tmp_tags.push_back(line.substr(tmp_l, tmp_r - tmp_l));
					}

					//处理时间
					if ((line[i] == '#') && (count_flag == 1))
					{
						wstring tmp_str_time = line.substr(tmp_i + 1, 5);
						tmp_time = (tmp_str_time[0] - '0') * 10 * 60 + (tmp_str_time[1] - '0') * 60 + (tmp_str_time[3] - '0') * 10 + (tmp_str_time[4] - '0');
						tmp_url = line.substr(i + 7, line.length() - i - 7);
						break;
					}
				}
				if (tmp_tags.size() != 0)
				{
					s_video[k].push_back({ tmp_tags, tmp_time, tmp_url });
				} 
			}
		}
	}
}
vector<Video> returnVideo(wstring tagText)
{
	int index = -1;
	for(int i=0;i<indexTags.size()-1;i++)
	{
		if (indexTags[i] == tagText)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		return s_video[index];
	}
	else
	{
		vector<Video>v;
		return v;
	}
}
int main()
{
	get_sumTags();
	getIn();
	//待注释
	wstring cinwstr=L"铃芽之旅";
	vector<Video> tmp = returnVideo(cinwstr);
	wcout.imbue(locale("chs"));
	for (auto i : tmp)
	{
		for (auto j : i.tags)
		{
			wcout << j << " ";
		}
		cout << i.time << " ";
		wcout << i.url << endl;
	}
	system("pause");
	return 0;
}