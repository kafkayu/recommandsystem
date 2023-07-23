#include<iostream>
#include<cmath>
#include<vector>
#include<ctime>
#include"recommand.h"
using namespace std;
typedef unsigned int uint;
#include <boost/locale.hpp>
//struct Cluster
//{
//    vector<double> centroid;
//    vector<uint> samples;
//};
//
//vector<Cluster> birch(vector<Video> data, uint k, uint maxepoches)
//{
//    vector<vector<double>> dis_matrix;
//    //1.�����������Ƶ�ľ������
//    //���������Ƶ���
//
//    
//}
std::string wstring2string(const std::wstring& source)
{
	const std::string type = "GBK";/*= "GBK"*/
	std::string s;
	try
	{
		s = boost::locale::conv::from_utf(source, type);
	}
	catch (const std::exception&)
	{
		return "";
	}
	return s;
}

class F67Video :public F3Video
{
public:
	Video clustercenter;
	int centerlen = 0;
	F67Video() {};
	F67Video(Video& A)
	{
		this->url = A.url;
		this->video_tags = A.video_tags;
		this->videoTime = A.videoTime;
		this->disval = 0;
	}
	void helpprint()
	{
		wcout << "url = " << this->url << "\n" << "��ǩ";
		for (int i = 0; i < this->video_tags.size(); i++)
		{
			wcout << this->video_tags[i].tags << this->video_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "Ȩֵ" << this->disval << endl;
	}

};
class F67User :public F3User
{
public:
	User clustercenter;
	int centerlen = 0;
	F67User() {};
	F67User(User& A)
	{
		this->ID = A.ID;
		this->user_tags = A.user_tags;
		this->pass_url = A.pass_url;
		this->disval = 0;
	}
	void helpprint()
	{
		wcout << "ID = " << this->ID << "\n" << "��ǩ";
		for (int i = 0; i < this->user_tags.size(); i++)
		{
			wcout << this->user_tags[i].tags << this->user_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "Ȩֵ" << this->disval << endl;
	}

};
bool F67cmpurl(F67Video& a, F67Video& b)
{
	return a.url < b.url;
}
bool F67cmpurl2(F67User& a, F67User& b)
{
	return a.ID < b.ID;
}

bool F67cmpValue(F67Video& a, F67Video& b) {
	return a.disval < b.disval;
}
bool F67cmpValue2(F67User& a, F67User& b) {
	return a.disval < b.disval;
}
void centerchange(F67Video& center, F67Video& a, int centerlen)
{
	//sort(center.video_tags.begin(), center.video_tags.end());
	//sort(a.video_tags.begin(), a.video_tags.end());
	//vector<Tags> res;

	for (int i = 0, j = 0; (j < a.video_tags.size());)
	{
		if (i >= center.video_tags.size())
		{
			center.video_tags.push_back(a.video_tags[j++]);

			continue;
		}
		if (center.video_tags[i] == a.video_tags[j]) {
			center.video_tags[i].weight += a.video_tags[j++].weight / (centerlen);

		}
		else if (center.video_tags[i] < a.video_tags[j])
		{
			i++;
		}
		else if (a.video_tags[j] < center.video_tags[i])
		{
			center.video_tags.push_back(a.video_tags[j++]);
		}
	}
	//total = Tagssum(center.video_tags);
	//���¾�������
	for (int i = 0; i < center.video_tags.size(); i++)
	{
		center.video_tags[i].weight = center.video_tags[i].weight * centerlen / (centerlen + 1);
	}
	//sort(center.video_tags.begin(), center.video_tags.end());


}
void centerchange(F67User& center, F67User& a, int centerlen)
{
	sort(center.user_tags.begin(), center.user_tags.end());
	sort(a.user_tags.begin(), a.user_tags.end());
	//vector<Tags> res;

	for (int i = 0, j = 0; (j < a.user_tags.size());)
	{
		if (i >= center.user_tags.size())
		{
			center.user_tags.push_back(a.user_tags[j++]);

			continue;
		}
		if (center.user_tags[i] == a.user_tags[j]) {
			center.user_tags[i].weight += a.user_tags[j++].weight / (centerlen);

		}
		else if (center.user_tags[i] < a.user_tags[j])
		{
			i++;
		}
		else if (a.user_tags[j] < center.user_tags[i])
		{
			center.user_tags.push_back(a.user_tags[j++]);
		}
	}
	//total = Tagssum(center.video_tags);
	//���¾�������
	for (int i = 0; i < center.user_tags.size(); i++)
	{
		center.user_tags[i].weight = center.user_tags[i].weight * centerlen / (centerlen + 1);
	}
	//sort(center.user_tags.begin(), center.user_tags.end());


}
double Tagssum(vector<Tags>arr)
{
	double r = 0;
	for (int i = 0; i < arr.size(); i++)r += arr[i].weight;//��ʵ������ģ�������Ƶ�����û�����Ȩ����ֵһ����2
	return r;
}
void display_cluster(vector<F67Video> F67Video)
{
	for (int i = 0; i < F67Video.size(); i++)
	{
		F67Video[i].helpdisplay();
	}
}
void display_cluster(vector<F67User> F67USer)
{
	for (int i = 0; i < F67USer.size(); i++)
	{
		F67USer[i].helpdisplay();
	}
}

struct birchNode
{
	vector<F67Video> data;                    /*������*/
	birchNode* lchild = NULL, * rchild = NULL; /*��������������*/
	F67Video center;
	birchNode() {};
	void chcenter(F67Video A)
	{
		centerchange(this->center, A, data.size());

	}


};
struct birchNode2
{
	vector<F67User> data;                    /*������*/
	birchNode2* lchild = NULL, * rchild = NULL; /*��������������*/
	F67User center;
	birchNode2() {};
	void chcenter(F67User A)
	{
		centerchange(this->center, A, data.size());

	}


};
bool BIsLeaf(birchNode A)
{
	return (!A.lchild && !A.rchild);

}
bool BIsLeaf(birchNode2 A)
{
	return (!A.lchild && !A.rchild);

}
int CountLeaf(birchNode root)
{
	if (BIsLeaf(root))return 1;
	else
	{
		return CountLeaf(*root.lchild) + CountLeaf(*root.rchild);
	}
}
int CountLeaf(birchNode2 root)
{
	if (BIsLeaf(root))return 1;
	else
	{
		return CountLeaf(*root.lchild) + CountLeaf(*root.rchild);
	}
}
void getcenter(vector<F67Video>& center, birchNode root)
{
	if (BIsLeaf(root))center.push_back(root.center);
	else
	{
		getcenter(center, *root.lchild);
		getcenter(center, *root.rchild);
	}

}
void getcenter(vector<F67User>& center, birchNode2 root)
{
	if (BIsLeaf(root))center.push_back(root.center);
	else
	{
		getcenter(center, *root.lchild);
		getcenter(center, *root.rchild);
	}

}


void InsertTree(birchNode& root, F67Video A, double minr)//��Ƶ����
{
	birchNode* n = &root;
	//1.�ݹ��ҵ������Ҷ�ӽڵ�
	while (!BIsLeaf(*n)) {
		//����ýڵ����Ҫ�ȸ��¸ýڵ�ľ�������,���ýڵ����data
		n->data.push_back(A);
		n->chcenter(A);
		double d1 = disTagsCal((n->lchild)->center.video_tags, A.video_tags);
		double d2 = disTagsCal((n->rchild)->center.video_tags, A.video_tags);
		//double d1 = disTagsCal((n.lchild->data.)
		if (d1 < d2)//�����rchild���ƶȸ��������������
		{
			n = n->rchild;
		}
		else
		{
			n = n->lchild;
		}
	}
	//2.����������Ҷ�ӽڵ�
	if (n->data.size() == 0)
	{
		n->data.push_back(A);
		n->center = A;
	}//Ϊ0��ֱ�ӳ�ʼ�����ڵ�
	else
	{
		//������Ҷ�ӽڵ�����ֵ
		n->chcenter(A);//���¸ýڵ��ǩ
		double d = disTagsCal(A.video_tags, n->center.video_tags);
		if (d > minr)//������ƶȸ���minr��ֵ����ֱ�Ӽ���
			n->data.push_back(A);
		else
		{
			//�����������ֵ���򽫸ýڵ���ѣ����������������ӽڵ�
			n->data.push_back(A);
			birchNode* lc = new birchNode, * rc = new birchNode;
			lc->data.push_back(A);//A�ڵ��Զ�װ������
			lc->center = A;
			for (int i = 0; i < n->data.size(); i++)
			{
				double d1 = disTagsCal(A.video_tags, n->data[i].video_tags);
				if (d1 > 0.6) {//���������ֵ��ֱ��װ������
					lc->data.push_back(n->data[i]);
					lc->chcenter(n->data[i]);
				}
				else
				{
					if (rc->data.size() == 0) {//����Һ���Ϊ0��ֱ��ֱ��װ���Һ���
						rc->data.push_back(n->data[i]);
						rc->center = n->data[i];
					}
					else
					{//����Һ��Ӳ�Ϊ0��������ĵ�
						rc->data.push_back(n->data[i]);
						rc->chcenter(n->data[i]);
					}

				}
			}
			//�����ɵ������ӽڵ����
			n->data.push_back(A);
			n->lchild = lc;
			n->rchild = rc;



		}
	}



}
void InsertTree(birchNode2& root, F67User A, double minr)//�û�����
{
	birchNode2* n = &root;
	//1.�ݹ��ҵ������Ҷ�ӽڵ�
	while (!BIsLeaf(*n)) {
		//����ýڵ����Ҫ�ȸ��¸ýڵ�ľ�������,���ýڵ����data
		n->data.push_back(A);
		n->chcenter(A);
		double d1 = disTagsCal((n->lchild)->center.user_tags, A.user_tags);
		double d2 = disTagsCal((n->rchild)->center.user_tags, A.user_tags);
		//double d1 = disTagsCal((n.lchild->data.)
		if (d1 < d2)//�����rchild���ƶȸ��������������
		{
			n = n->rchild;
		}
		else
		{
			n = n->lchild;
		}
	}
	//2.����������Ҷ�ӽڵ�
	if (n->data.size() == 0)
	{
		n->data.push_back(A);
		n->center = A;
	}//Ϊ0��ֱ�ӳ�ʼ�����ڵ�
	else
	{
		//������Ҷ�ӽڵ�����ֵ
		n->chcenter(A);//���¸ýڵ��ǩ
		double d = disTagsCal(A.user_tags, n->center.user_tags);
		if (d > minr)//������ƶȸ���minr��ֵ����ֱ�Ӽ���
			n->data.push_back(A);
		else
		{
			//�����������ֵ���򽫸ýڵ���ѣ����������������ӽڵ�
			n->data.push_back(A);
			birchNode2* lc = new birchNode2, * rc = new birchNode2;
			lc->data.push_back(A);//A�ڵ��Զ�װ������
			lc->center = A;
			for (int i = 0; i < n->data.size(); i++)
			{
				double d1 = disTagsCal(A.user_tags, n->data[i].user_tags);
				if (d1 > 0.6) {//���������ֵ��ֱ��װ������
					lc->data.push_back(n->data[i]);
					lc->chcenter(n->data[i]);
				}
				else
				{
					if (rc->data.size() == 0) {//����Һ���Ϊ0��ֱ��ֱ��װ���Һ���
						rc->data.push_back(n->data[i]);
						rc->center = n->data[i];
					}
					else
					{//����Һ��Ӳ�Ϊ0��������ĵ�
						rc->data.push_back(n->data[i]);
						rc->chcenter(n->data[i]);
					}

				}
			}
			//�����ɵ������ӽڵ����
			n->data.push_back(A);
			n->lchild = lc;
			n->rchild = rc;



		}
	}



}
void CreateTree(vector<F67Video> allvideo, double minr, birchNode& root)
{
	//allvideoΪ������Ƶ���ݣ�minrΪ������ƶȣ����ڸ����ƶȾͲ��ܼ���ýڵ�
	//1.���϶���ڵ㣬�������ﵽ��ֵ���߹�ϵ
	//birchNode root;
	cout << "******��ʼ����birchtree******" << endl;
	for (int i = 0; i < allvideo.size(); i+=100)
	{
		if (i % 100 == 0)cout << "�ѽ��� " << i << "/" << allvideo.size() << endl;
		InsertTree(root, allvideo[i], minr);


	}
	cout << "createtree�д�СΪ" << root.data.size() << endl;
	cout << "******�������******" << endl;
}
void CreateTree(vector<F67User> allvideo, double minr, birchNode2& root)
{
	//allvideoΪ������Ƶ���ݣ�minrΪ������ƶȣ����ڸ����ƶȾͲ��ܼ���ýڵ�
	//1.���϶���ڵ㣬�������ﵽ��ֵ���߹�ϵ
	//birchNode root;
	cout << "******��ʼ����birchtree******" << endl;
	for (int i = 0; i < allvideo.size(); i++)
	{
		if (i % 100 == 0)cout << "�ѽ��� " << i << "/" << allvideo.size() << endl;
		InsertTree(root, allvideo[i], minr);


	}
	cout << "createtree�д�СΪ" << root.data.size() << endl;
	cout << "******�������******" << endl;
}
void testTree2()
{
	//2.�����������ݣ����¾�������
	vector<F67User> allUser;
	int l = u_video.size();
	for (int i = 0; i < l; i++)
	{


		vector<User> tmp = u_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allUser.push_back(F67User(tmp[j]));

		}
	}
	sort(allUser.begin(), allUser.end(), F67cmpurl2);
	allUser.erase(unique(allUser.begin(), allUser.end()), allUser.end());

	cout << "�ܹ������û���" << allUser.size() << endl;
	birchNode2 root;
	CreateTree(allUser, 0.2, root);
	vector<F67User>cen;
	getcenter(cen, root);
	cout << "�������ݴ�СΪ" << root.data.size() << endl;
	cout << "��������Ϊ" << CountLeaf(root) << endl;
	cout << "��õľ������ĸ���Ϊ" << cen.size() << endl;

}
void testTree()
{
	//2.�����������ݣ����¾�������
	vector<F67Video> allVideo;
	int l = s_video.size();
	for (int i = 0; i < l; i++)
	{


		vector<Video> tmp = s_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allVideo.push_back(F67Video(tmp[j]));

		}
	}
	sort(allVideo.begin(), allVideo.end(), F67cmpurl);
	allVideo.erase(unique(allVideo.begin(), allVideo.end()), allVideo.end());

	cout << "�ܹ�������Ƶ��" << allVideo.size() << endl;
	birchNode root;
	CreateTree(allVideo, 0.2, root);
	vector<F67Video>cen;
	getcenter(cen, root);
	cout << "�������ݴ�СΪ" << root.data.size() << endl;
	cout << "��������Ϊ" << CountLeaf(root) << endl;
	cout << "��õľ������ĸ���Ϊ" << cen.size() << endl;

}
void writeresulttxt(vector<F67User>res)
{
	//д���ı�

	ofstream ofs;
	
	ofs.open("video_cluster_result.txt", wios::out);
	ofs << "�û�����������" << endl;
	ofs << "�������ĸ���Ϊ" << res.size() << "\n";
	ofs << "�������ļ����ǩ����: " << endl;
	for (int i = 0; i < res.size(); i++) {
		ofs << "��������" << i + 1 << ": " << endl;
		ofs << "�����û���Ŀ" << res[i].centerlen << endl;
		//����
		//endl���ڻ���
		string a;
		for (int j = 0; j < res[i].user_tags.size(); j++)
		{
			a = wstring2string(res[i].user_tags[j].tags);
			ofs << a << res[i].user_tags[j].weight << " ";
		}


	}
	ofs.close();


}
void writeresulttxt(vector<F67Video> res, string str)
{
	//д���ı�

	ofstream ofs;

	ofs.open(str, wios::out);
	ofs << "��Ƶ����������" << endl;
	ofs << "�������ĸ���Ϊ" << res.size() << "\n";
	ofs << "�������ļ����ǩ����: " << endl;
	for (int i = 0; i < res.size(); i++) {
		ofs << "��������" << i + 1 << ": " << endl;
		//"������Ƶ��Ŀ" <<
		ofs <<  res[i].centerlen << endl;
		//����
		//endl���ڻ���
		//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;//����ת����
		for (int j = 0; j < res[i].video_tags.size(); j++)
		{
			//std::string narrowstr = conv.to_bytes(res[i].video_tags[j].tags);
			string s = wstring2string(res[i].video_tags[j].tags);
			ofs << s<< res[i].video_tags[j].weight << " ";
		}
		ofs << endl;

	}
	ofs.close();

}
bool comparevalue(Tags& A, Tags& B)
{
	return A.weight > B.weight;

}
void simplize(F67Video& A)
{
	sort(A.video_tags.begin(), A.video_tags.end(), comparevalue);
	vector<Tags>t;
	for (int i = 0; i < 5 && i< A.video_tags.size(); i++) {
		A.video_tags[i].weight = 1.0 / 5;
		t.push_back(A.video_tags[i]);
	}

}
void simplize(vector<F67Video>&A)
{
	for (int i = 0; i < A.size(); i++)
	{
		simplize(A[i]);
	}

}
void kmeans()
{

	wcout.imbue(locale("chs"));//�������
	//1.������������
	vector<F67Video> allVideo;
	int l = s_video.size();
	for (int i = 0; i < l; i++)
	{


		vector<Video> tmp = s_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allVideo.push_back(F67Video(tmp[j]));

		}
	}
	sort(allVideo.begin(), allVideo.end(), F67cmpurl);
	allVideo.erase(unique(allVideo.begin(), allVideo.end()), allVideo.end());

	cout << "�ܹ�������Ƶ��" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.��ʼ����������
	//�������cftree��õľ�������

	birchNode root;
	CreateTree(allVideo, 0.2, root);

	getcenter(center, root);
	cout << "�������ݴ�СΪ" << root.data.size() << endl;
	cout << "��������Ϊ" << CountLeaf(root) << endl;
	cout << "��õľ������ĸ���Ϊ" << center.size() << endl;
	for (int i = 0; i < s_video.size(); i+=5)
	{
		if(s_video[i].size()!= 0)
		center.push_back(F67Video(s_video[i][0]));

	}

	cout << "�������ĸ���Ϊ" << center.size() << endl;
	center[0].helpprint();

	simplize(center);
	//3.���¾�������
	//�����������������������
	int maxt = 10;//����������
	int dc = 3;//����һ�κ���һ��֮��䶯���಻����dc������Ϊ����
	int lastcenter = 0;
	double minr = 0.2;//��С���ƶ�
	for (int k = 0; k < maxt; k++) {

		cout << "��" << k << "�ε�����\n" << "�ϴε�����˴ε������Ϊ��" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k> 0) { cout << "�������㷨����" << endl; break; }
		lastcenter = center.size();//��¼��һ�ξ���䶯����
		for (int i = 0; i < allVideo.size(); i+=100)
		{
			//���������о������ĵľ���
			int index = 0; //��¼��һ�����ĸ��������Ľ������䶯
			if (i % 200 == 0)cout << "�Ѿ�����" << i << "��" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].video_tags, allVideo[i].video_tags);
				if (allVideo[i].disval < d)
				{
					//�����Ϊĳһ��
					allVideo[i].disval = d;
					index = j;
				}


			}
			//��һ����Ƶ��������¸��¾������ĵı�ǩ
			allVideo[i].clustercenter = center[index];//���չ�����
			center[index].centerlen++;
			if (allVideo[i].disval > minr)//С��minr��ʾ�����������κξ�������
				centerchange(center[index], allVideo[i], center[index].centerlen);
			else
			{
				allVideo[i].centerlen++;//���õ�����Ϊ��������
				allVideo[i].clustercenter = allVideo[i];
				center.push_back(allVideo[i]);


			}

		}

		display_cluster(center);



	}
	//д���ı�
	string s = "birch+kmeans_video_cluster_result.txt";
	writeresulttxt(center,s);

}
void notBirchkmeans()
{

	wcout.imbue(locale("chs"));//�������
	//1.������������
	vector<F67Video> allVideo;
	int l = s_video.size();
	for (int i = 0; i < l; i++)
	{


		vector<Video> tmp = s_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allVideo.push_back(F67Video(tmp[j]));

		}
	}
	sort(allVideo.begin(), allVideo.end(), F67cmpurl);
	allVideo.erase(unique(allVideo.begin(), allVideo.end()), allVideo.end());

	cout << "�ܹ�������Ƶ��" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.��ʼ����������
	//�������cftree��õľ�������
	center.push_back(s_video[0][0]);
	//birchNode root;
	//CreateTree(allVideo, 0.2, root);

	//getcenter(center, root);
	///*cout << "�������ݴ�СΪ" << root.data.size() << endl;
	//cout << "��������Ϊ" << CountLeaf(root) << endl;
	//cout << "��õľ������ĸ���Ϊ" << center.size() << endl;*/
	///*for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67Video(s_video[i][0]));

	//}*/

	//cout << "�������ĸ���Ϊ" << center.size() << endl;
	//center[0].helpprint();


	//3.���¾�������
	//�����������������������
	int maxt = 10;//����������
	int dc = 3;//����һ�κ���һ��֮��䶯���಻����dc������Ϊ����
	int lastcenter = 0;
	double minr = 0.2;//��С���ƶ�
	for (int k = 0; k < maxt; k++) {

		cout << "��" << k << "�ε�����\n" << "�ϴε�����˴ε������Ϊ��" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k > 0) { cout << "�������㷨����" << endl; break; }
		lastcenter = center.size();//��¼��һ�ξ���䶯����
		for (int i = 0; i < allVideo.size(); i += 100)
		{
			//���������о������ĵľ���
			int index = 0; //��¼��һ�����ĸ��������Ľ������䶯
			if (i % 200 == 0)cout << "�Ѿ�����" << i << "��" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].video_tags, allVideo[i].video_tags);
				if (allVideo[i].disval < d)
				{
					//�����Ϊĳһ��
					allVideo[i].disval = d;
					index = j;
				}


			}
			//��һ����Ƶ��������¸��¾������ĵı�ǩ
			allVideo[i].clustercenter = center[index];//���չ�����
			center[index].centerlen++;
			if (allVideo[i].disval > minr)//С��minr��ʾ�����������κξ�������
				centerchange(center[index], allVideo[i], center[index].centerlen);
			else
			{
				allVideo[i].centerlen++;//���õ�����Ϊ��������
				allVideo[i].clustercenter = allVideo[i];
				center.push_back(allVideo[i]);


			}

		}

		display_cluster(center);



	}
	//д���ı�
	string s = "kmeans_user_cluster_result.txt";
	writeresulttxt(center, s);

}
void Birch()
{

	wcout.imbue(locale("chs"));//�������
	//1.������������
	vector<F67Video> allVideo;
	int l = s_video.size();
	for (int i = 0; i < l; i++)
	{


		vector<Video> tmp = s_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allVideo.push_back(F67Video(tmp[j]));

		}
	}
	sort(allVideo.begin(), allVideo.end(), F67cmpurl);
	allVideo.erase(unique(allVideo.begin(), allVideo.end()), allVideo.end());

	cout << "�ܹ�������Ƶ��" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.��ʼ����������
	//�������cftree��õľ�������

	birchNode root;
	CreateTree(allVideo, 0.2, root);

	getcenter(center, root);
	cout << "�������ݴ�СΪ" << root.data.size() << endl;
	cout << "��������Ϊ" << CountLeaf(root) << endl;
	cout << "��õľ������ĸ���Ϊ" << center.size() << endl;
	//for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67Video(s_video[i][0]));

	//}

	cout << "�������ĸ���Ϊ" << center.size() << endl;
	center[0].helpprint();
	string s = "birch_user_cluster_result.txt";
	writeresulttxt(center, s);

}
void kmeans2()
{

	wcout.imbue(locale("chs"));//�������
	//1.������������
	vector<F67User> allUser;
	int l = u_video.size();
	for (int i = 1; i < l; i++)
	{


		vector<User> tmp = u_video[i];

		for (int j = 0; j < tmp.size(); j++)
		{
			allUser.push_back(F67User(tmp[j]));

		}
	}
	sort(allUser.begin(), allUser.end(), F67cmpurl2);
	allUser.erase(unique(allUser.begin(), allUser.end()), allUser.end());

	cout << "�ܹ�������Ƶ��" << allUser.size() << endl;


	vector<F67User> center;
	//2.��ʼ����������
	//�������cftree��õľ�������

	birchNode2 root;
	CreateTree(allUser, 0.5, root);

	getcenter(center, root);
	//cout << "�������ݴ�СΪ" << root.data.size() << endl;
	//cout << "��������Ϊ" << CountLeaf(root) << endl;
	//cout << "��õľ������ĸ���Ϊ" << center.size() << endl;
	//for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67User(u_video[i][0]));

	//}

	cout << "�������ĸ���Ϊ" << center.size() << endl;
	center[0].helpprint();


	//3.���¾�������
	//�����������������������
	int maxt = 10;//����������
	int dc = 5;//����һ�κ���һ��֮��䶯���಻����dc������Ϊ����
	int lastcenter = 0;
	double minr = 0.2;//��С���ƶ�
	for (int k = 0; k < maxt; k++) {

		cout << "��" << k << "�ε�����\n" << "�ϴε�����˴ε������Ϊ��" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k> 0 ) { cout << "�������㷨����" << endl; break; }
		lastcenter = center.size();//��¼��һ�ξ���䶯����
		for (int i = 0; i < allUser.size(); i++)
		{
			//���������о������ĵľ���
			int index = 0; //��¼��һ�����ĸ��������Ľ������䶯
			if (i % 200 == 0)cout << "�Ѿ�����" << i << "��" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].user_tags, allUser[i].user_tags);
				if (allUser[i].disval < d)
				{
					//�����Ϊĳһ��
					allUser[i].disval = d;
					index = j;
				}


			}
			//��һ����Ƶ��������¸��¾������ĵı�ǩ
			allUser[i].clustercenter = center[index];//���չ�����
			center[index].centerlen++;
			if (allUser[i].disval > minr)//С��minr��ʾ�����������κξ�������
				centerchange(center[index], allUser[i], center[index].centerlen);
			else
			{
				allUser[i].centerlen++;//���õ�����Ϊ��������
				allUser[i].clustercenter = allUser[i];
				center.push_back(allUser[i]);


			}

		}

		display_cluster(center);



	}
	//д���ı�
	writeresulttxt(center);

}