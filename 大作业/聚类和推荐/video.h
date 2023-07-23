#include<iostream>
#include<string>
#include<vector>
#include<codecvt>
#include<time.h>
#include <utility>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace std;
class Tags
{
public:
	wstring tags;
	double weight;
	//序列化
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& tags;
		ar& weight;
	}
	bool operator<(const Tags& a) {
		if (a.tags < this->tags) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator==(const Tags& a) {
		if (a.tags == this->tags) {
			return true;
		}
		else {
			return false;
		}
	}
};
class User
{
public:
	User(int ID) { this->ID = ID; };
	User() { this->ID = 0; };
	int ID;
	vector<wstring>pass_url;
	vector<Tags>user_tags;
	vector<wstring> showPass();
	void addUrl(wstring tmp_url);
	vector<Tags> showTags();
	void changeTags(vector<Tags>tmp_user_tags);
	void addTags(wstring tmp_tags);
	//序列化
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& ID;
		ar& pass_url;
		ar& user_tags;
	}
};
class Video
{
public:
	vector<Tags>video_tags;
	int videoTime;//(秒)
	wstring url;
	//热度预测
	double heat;
	int lastSecond;
	void changeHeat(tm presentTime);
	//序列化
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& video_tags;
		ar& videoTime;
		ar& url;
		ar& heat;
		ar& lastSecond;
	}
}; 
class IndexNumVideo
{
public:
	vector<int>IndexNumVideo;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& IndexNumVideo;
	}
};
class IndexNumUser
{
public:
	vector<int>IndexNumUser;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& IndexNumUser;
	}
};
//类函数实现
vector<vector<Video>>s_video;
vector<wstring>indexTags;
vector<vector<User>>u_video;
IndexNumVideo index_num_video;
IndexNumUser index_num_user;
//func函数
vector<wstring> User::showPass()
{
	return this->pass_url;
}
void User::addUrl(wstring tmp_url)
{
	this->pass_url.push_back(tmp_url);
}
vector<Tags> User::showTags()
{
	return this->user_tags;
}
void User::changeTags(vector<Tags>tmp_user_tags)
{
	this->user_tags = tmp_user_tags;
}
void User::addTags(wstring tmp_tags)
{
	this->user_tags.push_back({ tmp_tags,0 });
	int index = -1;
	for (int i = 0; i < indexTags.size() - 1; i++)
	{
		if (indexTags[i] == tmp_tags)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		u_video[index].push_back(*this);
	}

}
void Video::changeHeat(tm presentTime)
{
	//只计算一个月内
	int nowSecond = presentTime.tm_mday * 24 * 60 * 60 + presentTime.tm_hour * 60 * 60 + presentTime.tm_min * 60 + presentTime.tm_sec;
	double dSecond = nowSecond - lastSecond;
	if (dSecond > 24 * 60 * 60)//超过24h
	{
		double score = ((dSecond - 24 * 60 * 60) / 60) / (2.5);
		if ((heat - score) < 0)
		{
			heat = 0;
		}
		else
		{
			heat = heat - score;
		}
	}
}
//读入、输出函数
void get_sumTags()
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	ifstream in(L"../大作业_标签分类/data/summary.txt");
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
	for (int k = 0; k < indexTags.size(); k++)
	{
		wstring tmpIndexTag = indexTags[k];
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		wstring path = L"../大作业_标签分类/data/";
		path.append(tmpIndexTag);
		path.append(L".txt");
		ifstream in(path);
		vector<Video>video;
		s_video.push_back(video);
		vector<User>user;
		u_video.push_back(user);
		string line_tmp;
		if (in)
		{
			//读入，导入数据
			while (getline(in, line_tmp))
			{
				wstring line = conv.from_bytes(line_tmp);
				int len = line.length();
				int count_flag = 0;
				vector<Tags> tmp_tags;//存tag
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
								tmp_tags.push_back({ str1, 1 });
							}
						}
						tmp_l = tmp_r + 1;
						tmp_r = i;
						tmp_tags.push_back({ line.substr(tmp_l, tmp_r - tmp_l),1 });
					}

					//修改tags权重

					for (int i = 0; i < tmp_tags.size(); i++)
					{

						tmp_tags[i].weight = double(1) / tmp_tags.size();
						//cout << tmp_tags[i].weight << endl;

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
	//init heat
	for (int i = 0; i < s_video.size(); i++)
	{
		for (int j = 0; j < s_video[i].size(); j++)
		{
			s_video[i][j].heat = 0;
			struct tm tm_t;
			time_t now = time(NULL);
			localtime_s(&tm_t, &now);
			s_video[i][j].lastSecond = tm_t.tm_mday * 24 * 60 * 60 + tm_t.tm_hour * 60 * 60 + tm_t.tm_min * 60 + tm_t.tm_sec;
		}

	}
}
vector<Video> returnVideo(wstring tagText)
{
	int index = -1;
	for (int i = 0; i < indexTags.size() - 1; i++)
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
vector<User> returnUser(wstring nameText)
{
	int index = -1;
	for (int i = 0; i < indexTags.size() - 1; i++)
	{
		if (indexTags[i] == nameText)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		return u_video[index];
	}
	else
	{
		vector<User>v;
		return v;
	}

}
bool SaveIndexNumVideo(std::wstring wstrPath)
{
	std::ofstream ofs(wstrPath, std::ios::binary | std::ios_base::out | std::ios_base::trunc);
	if (!ofs.good())
	{
		return false;
	}

	boost::archive::binary_oarchive oa(ofs);
	oa << index_num_video;
	return true;
}
bool LoadIndexNumVideo(std::wstring wstrPath)
{
	// 打开文件
	std::ifstream ifs(wstrPath, std::ios::binary);
	boost::archive::binary_iarchive ia(ifs);
	if (!ifs.good())
	{
		return false;
	}
	// 从文件里恢复状态
	ia >> index_num_video;
	return true;
}
bool SaveIndexNumUser(std::wstring wstrPath)
{
	std::ofstream ofs(wstrPath, std::ios::binary | std::ios_base::out | std::ios_base::trunc);
	if (!ofs.good())
	{
		return false;
	}

	boost::archive::binary_oarchive oa(ofs);
	oa << index_num_user;
	return true;
}
bool LoadIndexNumUser(std::wstring wstrPath)
{
	// 打开文件
	std::ifstream ifs(wstrPath, std::ios::binary);
	boost::archive::binary_iarchive ia(ifs);
	if (!ifs.good())
	{
		return false;
	}
	// 从文件里恢复状态
	ia >> index_num_user;
	return true;
}
bool SaveVideo(std::wstring wstrPath, int index_i)
{
	std::ofstream ofs(wstrPath, std::ios::binary | std::ios_base::out | std::ios_base::trunc);
	if (!ofs.good())
	{
		return false;
	}

	boost::archive::binary_oarchive oa(ofs);
	for (auto i : s_video[index_i])
	{
		oa << i;
	}
	return true;
}
bool LoadVideo(std::wstring wstrPath, int index_i)
{
	// 打开文件
	std::ifstream ifs(wstrPath, std::ios::binary);
	boost::archive::binary_iarchive ia(ifs);
	if (!ifs.good())
	{
		return false;
	}
	// 从文件里恢复状态
	int cnt = index_num_video.IndexNumVideo[index_i];
	while (cnt--)
	{
		Video v;
		ia >> v;

		s_video[index_i].push_back(v);
	}
	return true;
}
bool SaveUser(std::wstring wstrPath, int index_i)
{
	std::ofstream ofs(wstrPath, std::ios::binary | std::ios_base::out | std::ios_base::trunc);
	if (!ofs.good())
	{
		return false;
	}

	boost::archive::binary_oarchive oa(ofs);
	for (auto i : u_video[index_i])
	{
		oa << i;
	}
	return true;
}
bool LoadUser(std::wstring wstrPath, int index_i)
{
	// 打开文件
	std::ifstream ifs(wstrPath, std::ios::binary);
	boost::archive::binary_iarchive ia(ifs);
	if (!ifs.good())
	{
		return false;
	}
	// 从文件里恢复状态
	int cnt = index_num_user.IndexNumUser[index_i];
	while (cnt--)
	{
		User v;
		ia >> v;

		u_video[index_i].push_back(v);
	}
	return true;
}
void initNumVideo()
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		index_num_video.IndexNumVideo.push_back(s_video[i].size());
	}
}
void initNumUser()
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		index_num_user.IndexNumUser.push_back(1);
	}
	for (int i = 0; i < u_video.size(); i++)
	{
		class User tmp_User;
		tmp_User.ID = -1;
		u_video[i].push_back(tmp_User);
	}
}
void init_s_video()
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		vector<Video>v;
		s_video.push_back(v);
	}
}
void init_u_video()
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		vector<User>v;
		u_video.push_back(v);
	}
}
void change_u_video()
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		index_num_user.IndexNumUser.push_back(u_video[i].size());
	}
}
void Load()
{
	get_sumTags();
	getIn();//(first)
	//load index_num_video
	/*LoadIndexNumVideo(L"./data/index_num_video.bin");//(second)
	//Load s_video
	init_s_video();//(second)
	for (int i = 0; i < indexTags.size(); i++)
	{
		cout << i << endl;
		wstring path = L"./data/";
		path.append(indexTags[i]);
		path.append(L".bin");
		LoadVideo(path, i);
	}
	//Load u_video
	init_u_video();//(second)
	cout << "u" << endl;
	LoadIndexNumUser(L"./data_u/index_num_User.bin");//(second)
	for (int i = 0; i < indexTags.size(); i++)
	{
		cout << i << endl;
		wstring path = L"./data_u/";
		path.append(indexTags[i]);
		path.append(L".bin");
		LoadUser(path, i);
	}*/
}
void Save()
{
	initNumVideo();//(first)
	initNumUser();//(first)
	//change_u_video();//(second)
	//save index_num_video
	SaveIndexNumVideo(L"./data/index_num_video.bin");
	SaveIndexNumUser(L"./data_u/index_num_user.bin");
	//save s_video
	for (int i = 0; i < indexTags.size(); i++)
	{
		wstring path = L"./data/";
		path.append(indexTags[i]);
		path.append(L".bin");
		SaveVideo(path, i);
	}
	//save u_video
	for (int i = 0; i < indexTags.size(); i++)
	{
		wstring path = L"./data_u/";
		path.append(indexTags[i]);
		path.append(L".bin");
		SaveUser(path, i);
	}
}
int gettags_position(wstring tags)
{
	for (int i = 0; i < indexTags.size(); i++)
	{
		if (tags == indexTags[i])
		{
			return i;
		}
	}
	return 0;//若不等则返回0


}
void helpaddu_videotags(User& A)
{
	for (int i = 0; i < A.user_tags.size(); i++) {
		int h = gettags_position(A.user_tags[i].tags);

		for (int j = 0; j < u_video[h].size(); j++)
		{
			if (u_video[h][j].ID == A.ID)return;
		}
		//循环后仍未找到
		u_video[h].push_back(A);
		wcout << indexTags[h] << endl;;
	}
}

void helpCreateNewPeople(User& A)
{

	srand(unsigned(A.ID));
	int range = s_video.size();
	int k = rand() % range;
	while (s_video[k].size() == 0) k = rand() % range;
	cout << "value: " << k << endl;
	//创建1000个用户，每100个用户拥有相同的1个标签

	range = s_video[k].size();
	int d = rand() % range;
	A.changeTags(s_video[k][d].video_tags);
	A.pass_url.push_back(s_video[k][d].url);
	//将user加入全局变量
	//检查用户是否已经在标签存储内
	helpaddu_videotags(A);






}
void createNewPeople()
{
	//确认用户ID
	cout << "添加前" << sizeof(u_video) << endl;
	for (int i = 1; i < 1000; i++) {
		User* A = new User(i);
		helpCreateNewPeople(*A);
	}
	cout << "添加后" << sizeof(u_video) << endl;

}