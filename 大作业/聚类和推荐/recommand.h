#pragma once
#include"distance.h"
#include<iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <queue>
using namespace std;

Video urlfind(wstring url)
{
	int l = s_video.size();
	for (int i = 0; i < l; i++)
	{
		int k = s_video[i].size();
		for (int j = 0; j < k; j++)
		{
			if (s_video[i][j].url == url)
				return s_video[i][j];
		}
	}

}
class F3User :public User
{
	//vector<wstring>pass_url;
	//vector<Tags>user_tags;
	//vector<wstring> showPass();
	//void addUrl(wstring tmp_url);
	//vector<Tags> showTags();
	//void changeTags(vector<Tags>tmp_user_tags);
	//void addTags(wstring tmp_tags);
	//wstring ID;
public:
	double disval;
	F3User() {};
	F3User(User& A, double value) {
		this->user_tags = A.user_tags;
		//this->videoTime = A.videoTime;//(秒)
		//this->url = A.url;
		this->disval = value;
		this->ID = A.ID;
		this->pass_url = A.pass_url;

	};
	User ToUser()
	{
		User A;
		A.ID = this->ID;
		A.pass_url = this->pass_url;
		A.user_tags = this->user_tags;

		return A;

	}
	bool operator<(const F3User& a)const {
		if (a.disval > this->disval) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(const F3User& a) {
		if (a.ID == this->ID) {
			return true;
		}
		else {
			return false;
		}
	}
	void helpdisplay() const
	{
		wcout << "ID = " << this->ID << "\n" << "标签";
		for (int i = 0; i < this->user_tags.size(); i++)
		{
			wcout << this->user_tags[i].tags << this->user_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "权值" << this->disval << endl;
	}


};
class F3Video :public Video
{
public:
	F3Video() { ; }
	F3Video(Video& A, double value) {
		this->video_tags = A.video_tags;
		this->videoTime = A.videoTime;//(秒)
		this->url = A.url;
		this->disval = value;

	};
	F3Video(Video& A) {
		this->video_tags = A.video_tags;
		this->videoTime = A.videoTime;//(秒)
		this->url = A.url;


	};
	Video ToVideo()
	{
		Video A;
		A.heat = this->heat;
		A.lastSecond = this->lastSecond;
		A.url = this->url;
		A.videoTime = this->videoTime;
		A.video_tags = this->video_tags;

		return A;

	}
	double disval;
	bool operator<(const F3Video& a)const {
		if (a.disval > this->disval) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(const F3Video& a) {
		if (a.url == this->url) {
			return true;
		}
		else {
			return false;
		}
	}
	void helpdisplay() const
	{
		wcout << "url = " << this->url << "\n" << "标签";
		for (int i = 0; i < this->video_tags.size(); i++)
		{
			wcout << this->video_tags[i].tags << this->video_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "权值" << this->disval << endl;
	}

};

void display_recommand(priority_queue<F3Video> F4Video, int n)
{

	for (int i = 0; i < n; i++)
	{
		F4Video.top().helpdisplay();
		F4Video.pop();

	}
}
void display_recommand(priority_queue<F3User> F4Video, int n)
{

	for (int i = 0; i < n; i++)
	{
		F4Video.top().helpdisplay();
		F4Video.pop();

	}
}
std::wstring GetWStringByChar(const char* szString)
{
	std::wstring wstrString;
	if (szString != NULL)
	{
		std::string str(szString);
		wstrString.assign(str.begin(), str.end());
	}

	return wstrString;
}

bool F34cmpurl(F3Video& a, F3Video& b)
{
	return a.url < b.url;
}
bool F34cmpurl2(F3User& a, F3User& b)
{
	return a.ID < b.ID;
}


bool F34cmpValue(F3Video& a, F3Video& b) {
	return a.disval < b.disval;
}
bool F34cmpValue2(F3User& a, F3User& b) {
	return a.disval < b.disval;
}
vector<User> F3UserSearch(User A)
{
	//2.获取可能存在相关标签的用户
	int l = A.user_tags.size();
	vector<F3User> p_User;

	for (int i = 0; i < l; i++)
	{


		vector<User> tmp = returnUser(A.user_tags[i].tags);

		for (int j = 0; j < tmp.size(); j++)
		{
			p_User.push_back(F3User(tmp[j], disTagsCal(A.user_tags, tmp[j].user_tags)));

		}
	}
	sort(p_User.begin(), p_User.end(), F34cmpurl2);
	p_User.erase(unique(p_User.begin(), p_User.end()), p_User.end());

	cout << "总共可能用户有" << p_User.size() << endl;

	//3.建立用户级优先队列
	priority_queue<F3User> F3USER;
	for (int i = 0; i < p_User.size(); i++)
	{
		F3USER.push(p_User[i]);
	}
	cout << "最大相似度为" << F3USER.top().disval << endl;

	//返回前n个
	int n = 8;
	display_recommand(F3USER, n);
	vector<User>res;
	for (int i = 1; i < n; i++) {
		res.push_back(F3USER.top());
		F3USER.pop();
	}
	return res;

}

vector<Video> F3VideoSearch(User A)
{
	//1.获取查询用户或者视频的标签vector
	//wstring u;
	//u = A.url;
	////u = GetWStringByChar("https://www.bilibili.com/video/BV15s4y1J75S/");
	//Video v = urlfind(u);
	//wcout << v.url << endl;
	//2.获取可能存在相关标签的视频
	int l = A.user_tags.size();
	vector<F3Video> p_video;

	for (int i = 0; i < l; i++)
	{


		vector<Video> tmp = returnVideo(A.user_tags[i].tags);

		for (int j = 0; j < tmp.size(); j++)
		{
			p_video.push_back(F3Video(tmp[j], disTagsCal(A.user_tags, tmp[j].video_tags)));

		}
	}
	sort(p_video.begin(), p_video.end(), F34cmpurl);
	p_video.erase(unique(p_video.begin(), p_video.end()), p_video.end());

	cout << "总共可能视频有" << p_video.size() << endl;
	clock_t s, e;
	s = clock();
	//3.建立用户级优先队列
	priority_queue<F3Video> F4Video;
	for (int i = 0; i < p_video.size(); i++)
	{
		F4Video.push(p_video[i]);
	}
	cout << "最大相似度为" << F4Video.top().disval << endl;
	e = clock();
	cout << "推荐耗时time = " << double(e - s) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ） 
	//返回前n个
	int n = 8;
	display_recommand(F4Video, n);
	vector<Video>res;
	for (int i = 0; i < n; i++) {
		res.push_back(F4Video.top());
		F4Video.pop();
	}
	return res;
}


