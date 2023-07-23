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
//    //1.计算出所有视频的距离矩阵
//    //将最近的视频配对
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
		wcout << "url = " << this->url << "\n" << "标签";
		for (int i = 0; i < this->video_tags.size(); i++)
		{
			wcout << this->video_tags[i].tags << this->video_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "权值" << this->disval << endl;
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
		wcout << "ID = " << this->ID << "\n" << "标签";
		for (int i = 0; i < this->user_tags.size(); i++)
		{
			wcout << this->user_tags[i].tags << this->user_tags[i].weight << " ";
		}
		wcout << "\n";
		wcout << "权值" << this->disval << endl;
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
	//更新聚类中心
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
	//更新聚类中心
	for (int i = 0; i < center.user_tags.size(); i++)
	{
		center.user_tags[i].weight = center.user_tags[i].weight * centerlen / (centerlen + 1);
	}
	//sort(center.user_tags.begin(), center.user_tags.end());


}
double Tagssum(vector<Tags>arr)
{
	double r = 0;
	for (int i = 0; i < arr.size(); i++)r += arr[i].weight;//其实不用算的，两个视频或者用户最终权重总值一定是2
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
	vector<F67Video> data;                    /*数据域*/
	birchNode* lchild = NULL, * rchild = NULL; /*左子树和右子树*/
	F67Video center;
	birchNode() {};
	void chcenter(F67Video A)
	{
		centerchange(this->center, A, data.size());

	}


};
struct birchNode2
{
	vector<F67User> data;                    /*数据域*/
	birchNode2* lchild = NULL, * rchild = NULL; /*左子树和右子树*/
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


void InsertTree(birchNode& root, F67Video A, double minr)//视频插入
{
	birchNode* n = &root;
	//1.递归找到最近的叶子节点
	while (!BIsLeaf(*n)) {
		//进入该节点后需要先更新该节点的聚类中心,将该节点加入data
		n->data.push_back(A);
		n->chcenter(A);
		double d1 = disTagsCal((n->lchild)->center.video_tags, A.video_tags);
		double d2 = disTagsCal((n->rchild)->center.video_tags, A.video_tags);
		//double d1 = disTagsCal((n.lchild->data.)
		if (d1 < d2)//如果和rchild相似度更大，则进入右子树
		{
			n = n->rchild;
		}
		else
		{
			n = n->lchild;
		}
	}
	//2.接下来处理叶子节点
	if (n->data.size() == 0)
	{
		n->data.push_back(A);
		n->center = A;
	}//为0则直接初始化根节点
	else
	{
		//计算与叶子节点距离的值
		n->chcenter(A);//更新该节点标签
		double d = disTagsCal(A.video_tags, n->center.video_tags);
		if (d > minr)//如果相似度高于minr阈值，则直接加入
			n->data.push_back(A);
		else
		{
			//如果不满足阈值，则将该节点分裂，重新生成两个孩子节点
			n->data.push_back(A);
			birchNode* lc = new birchNode, * rc = new birchNode;
			lc->data.push_back(A);//A节点自动装入左孩子
			lc->center = A;
			for (int i = 0; i < n->data.size(); i++)
			{
				double d1 = disTagsCal(A.video_tags, n->data[i].video_tags);
				if (d1 > 0.6) {//如果大于阈值则直接装入左孩子
					lc->data.push_back(n->data[i]);
					lc->chcenter(n->data[i]);
				}
				else
				{
					if (rc->data.size() == 0) {//如果右孩子为0则直接直接装入右孩子
						rc->data.push_back(n->data[i]);
						rc->center = n->data[i];
					}
					else
					{//如果右孩子不为0则更新中心点
						rc->data.push_back(n->data[i]);
						rc->chcenter(n->data[i]);
					}

				}
			}
			//将生成的两个子节点加入
			n->data.push_back(A);
			n->lchild = lc;
			n->rchild = rc;



		}
	}



}
void InsertTree(birchNode2& root, F67User A, double minr)//用户插入
{
	birchNode2* n = &root;
	//1.递归找到最近的叶子节点
	while (!BIsLeaf(*n)) {
		//进入该节点后需要先更新该节点的聚类中心,将该节点加入data
		n->data.push_back(A);
		n->chcenter(A);
		double d1 = disTagsCal((n->lchild)->center.user_tags, A.user_tags);
		double d2 = disTagsCal((n->rchild)->center.user_tags, A.user_tags);
		//double d1 = disTagsCal((n.lchild->data.)
		if (d1 < d2)//如果和rchild相似度更大，则进入右子树
		{
			n = n->rchild;
		}
		else
		{
			n = n->lchild;
		}
	}
	//2.接下来处理叶子节点
	if (n->data.size() == 0)
	{
		n->data.push_back(A);
		n->center = A;
	}//为0则直接初始化根节点
	else
	{
		//计算与叶子节点距离的值
		n->chcenter(A);//更新该节点标签
		double d = disTagsCal(A.user_tags, n->center.user_tags);
		if (d > minr)//如果相似度高于minr阈值，则直接加入
			n->data.push_back(A);
		else
		{
			//如果不满足阈值，则将该节点分裂，重新生成两个孩子节点
			n->data.push_back(A);
			birchNode2* lc = new birchNode2, * rc = new birchNode2;
			lc->data.push_back(A);//A节点自动装入左孩子
			lc->center = A;
			for (int i = 0; i < n->data.size(); i++)
			{
				double d1 = disTagsCal(A.user_tags, n->data[i].user_tags);
				if (d1 > 0.6) {//如果大于阈值则直接装入左孩子
					lc->data.push_back(n->data[i]);
					lc->chcenter(n->data[i]);
				}
				else
				{
					if (rc->data.size() == 0) {//如果右孩子为0则直接直接装入右孩子
						rc->data.push_back(n->data[i]);
						rc->center = n->data[i];
					}
					else
					{//如果右孩子不为0则更新中心点
						rc->data.push_back(n->data[i]);
						rc->chcenter(n->data[i]);
					}

				}
			}
			//将生成的两个子节点加入
			n->data.push_back(A);
			n->lchild = lc;
			n->rchild = rc;



		}
	}



}
void CreateTree(vector<F67Video> allvideo, double minr, birchNode& root)
{
	//allvideo为所有视频数据，minr为最低相似度，低于该相似度就不能加入该节点
	//1.不断读入节点，当数量达到阈值或者关系
	//birchNode root;
	cout << "******开始建造birchtree******" << endl;
	for (int i = 0; i < allvideo.size(); i+=100)
	{
		if (i % 100 == 0)cout << "已建造 " << i << "/" << allvideo.size() << endl;
		InsertTree(root, allvideo[i], minr);


	}
	cout << "createtree中大小为" << root.data.size() << endl;
	cout << "******建造结束******" << endl;
}
void CreateTree(vector<F67User> allvideo, double minr, birchNode2& root)
{
	//allvideo为所有视频数据，minr为最低相似度，低于该相似度就不能加入该节点
	//1.不断读入节点，当数量达到阈值或者关系
	//birchNode root;
	cout << "******开始建造birchtree******" << endl;
	for (int i = 0; i < allvideo.size(); i++)
	{
		if (i % 100 == 0)cout << "已建造 " << i << "/" << allvideo.size() << endl;
		InsertTree(root, allvideo[i], minr);


	}
	cout << "createtree中大小为" << root.data.size() << endl;
	cout << "******建造结束******" << endl;
}
void testTree2()
{
	//2.加载所有数据，更新聚类中心
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

	cout << "总共可能用户有" << allUser.size() << endl;
	birchNode2 root;
	CreateTree(allUser, 0.2, root);
	vector<F67User>cen;
	getcenter(cen, root);
	cout << "聚类数据大小为" << root.data.size() << endl;
	cout << "聚类种类为" << CountLeaf(root) << endl;
	cout << "获得的聚类中心个数为" << cen.size() << endl;

}
void testTree()
{
	//2.加载所有数据，更新聚类中心
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

	cout << "总共可能视频有" << allVideo.size() << endl;
	birchNode root;
	CreateTree(allVideo, 0.2, root);
	vector<F67Video>cen;
	getcenter(cen, root);
	cout << "聚类数据大小为" << root.data.size() << endl;
	cout << "聚类种类为" << CountLeaf(root) << endl;
	cout << "获得的聚类中心个数为" << cen.size() << endl;

}
void writeresulttxt(vector<F67User>res)
{
	//写入文本

	ofstream ofs;
	
	ofs.open("video_cluster_result.txt", wios::out);
	ofs << "用户聚类结果如下" << endl;
	ofs << "聚类中心个数为" << res.size() << "\n";
	ofs << "聚类中心及其标签如下: " << endl;
	for (int i = 0; i < res.size(); i++) {
		ofs << "聚类中心" << i + 1 << ": " << endl;
		ofs << "该类用户数目" << res[i].centerlen << endl;
		//输入
		//endl用于换行
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
	//写入文本

	ofstream ofs;

	ofs.open(str, wios::out);
	ofs << "视频聚类结果如下" << endl;
	ofs << "聚类中心个数为" << res.size() << "\n";
	ofs << "聚类中心及其标签如下: " << endl;
	for (int i = 0; i < res.size(); i++) {
		ofs << "聚类中心" << i + 1 << ": " << endl;
		//"该类视频数目" <<
		ofs <<  res[i].centerlen << endl;
		//输入
		//endl用于换行
		//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;//创建转换类
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

	wcout.imbue(locale("chs"));//设置输出
	//1.加载所有数据
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

	cout << "总共可能视频有" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.初始化聚类中心
	//这里采用cftree获得的聚类中心

	birchNode root;
	CreateTree(allVideo, 0.2, root);

	getcenter(center, root);
	cout << "聚类数据大小为" << root.data.size() << endl;
	cout << "聚类种类为" << CountLeaf(root) << endl;
	cout << "获得的聚类中心个数为" << center.size() << endl;
	for (int i = 0; i < s_video.size(); i+=5)
	{
		if(s_video[i].size()!= 0)
		center.push_back(F67Video(s_video[i][0]));

	}

	cout << "聚类中心个数为" << center.size() << endl;
	center[0].helpprint();

	simplize(center);
	//3.更新聚类中心
	//设置最大迭代次数和收敛检测
	int maxt = 10;//最大迭代次数
	int dc = 3;//若上一次和下一次之间变动种类不超过dc个则视为收敛
	int lastcenter = 0;
	double minr = 0.2;//最小相似度
	for (int k = 0; k < maxt; k++) {

		cout << "第" << k << "次迭代：\n" << "上次迭代与此次迭代相差为：" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k> 0) { cout << "收敛，算法结束" << endl; break; }
		lastcenter = center.size();//记录上一次聚类变动个数
		for (int i = 0; i < allVideo.size(); i+=100)
		{
			//计算与所有聚类中心的距离
			int index = 0; //记录这一轮中哪个聚类中心将发生变动
			if (i % 200 == 0)cout << "已经运行" << i << "次" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].video_tags, allVideo[i].video_tags);
				if (allVideo[i].disval < d)
				{
					//将其归为某一类
					allVideo[i].disval = d;
					index = j;
				}


			}
			//当一个视频加入后重新更新聚类中心的标签
			allVideo[i].clustercenter = center[index];//最终归类结果
			center[index].centerlen++;
			if (allVideo[i].disval > minr)//小于minr表示不属于现有任何聚类中心
				centerchange(center[index], allVideo[i], center[index].centerlen);
			else
			{
				allVideo[i].centerlen++;//将该点设置为聚类中心
				allVideo[i].clustercenter = allVideo[i];
				center.push_back(allVideo[i]);


			}

		}

		display_cluster(center);



	}
	//写入文本
	string s = "birch+kmeans_video_cluster_result.txt";
	writeresulttxt(center,s);

}
void notBirchkmeans()
{

	wcout.imbue(locale("chs"));//设置输出
	//1.加载所有数据
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

	cout << "总共可能视频有" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.初始化聚类中心
	//这里采用cftree获得的聚类中心
	center.push_back(s_video[0][0]);
	//birchNode root;
	//CreateTree(allVideo, 0.2, root);

	//getcenter(center, root);
	///*cout << "聚类数据大小为" << root.data.size() << endl;
	//cout << "聚类种类为" << CountLeaf(root) << endl;
	//cout << "获得的聚类中心个数为" << center.size() << endl;*/
	///*for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67Video(s_video[i][0]));

	//}*/

	//cout << "聚类中心个数为" << center.size() << endl;
	//center[0].helpprint();


	//3.更新聚类中心
	//设置最大迭代次数和收敛检测
	int maxt = 10;//最大迭代次数
	int dc = 3;//若上一次和下一次之间变动种类不超过dc个则视为收敛
	int lastcenter = 0;
	double minr = 0.2;//最小相似度
	for (int k = 0; k < maxt; k++) {

		cout << "第" << k << "次迭代：\n" << "上次迭代与此次迭代相差为：" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k > 0) { cout << "收敛，算法结束" << endl; break; }
		lastcenter = center.size();//记录上一次聚类变动个数
		for (int i = 0; i < allVideo.size(); i += 100)
		{
			//计算与所有聚类中心的距离
			int index = 0; //记录这一轮中哪个聚类中心将发生变动
			if (i % 200 == 0)cout << "已经运行" << i << "次" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].video_tags, allVideo[i].video_tags);
				if (allVideo[i].disval < d)
				{
					//将其归为某一类
					allVideo[i].disval = d;
					index = j;
				}


			}
			//当一个视频加入后重新更新聚类中心的标签
			allVideo[i].clustercenter = center[index];//最终归类结果
			center[index].centerlen++;
			if (allVideo[i].disval > minr)//小于minr表示不属于现有任何聚类中心
				centerchange(center[index], allVideo[i], center[index].centerlen);
			else
			{
				allVideo[i].centerlen++;//将该点设置为聚类中心
				allVideo[i].clustercenter = allVideo[i];
				center.push_back(allVideo[i]);


			}

		}

		display_cluster(center);



	}
	//写入文本
	string s = "kmeans_user_cluster_result.txt";
	writeresulttxt(center, s);

}
void Birch()
{

	wcout.imbue(locale("chs"));//设置输出
	//1.加载所有数据
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

	cout << "总共可能视频有" << allVideo.size() << endl;


	vector<F67Video> center;
	//2.初始化聚类中心
	//这里采用cftree获得的聚类中心

	birchNode root;
	CreateTree(allVideo, 0.2, root);

	getcenter(center, root);
	cout << "聚类数据大小为" << root.data.size() << endl;
	cout << "聚类种类为" << CountLeaf(root) << endl;
	cout << "获得的聚类中心个数为" << center.size() << endl;
	//for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67Video(s_video[i][0]));

	//}

	cout << "聚类中心个数为" << center.size() << endl;
	center[0].helpprint();
	string s = "birch_user_cluster_result.txt";
	writeresulttxt(center, s);

}
void kmeans2()
{

	wcout.imbue(locale("chs"));//设置输出
	//1.加载所有数据
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

	cout << "总共可能视频有" << allUser.size() << endl;


	vector<F67User> center;
	//2.初始化聚类中心
	//这里采用cftree获得的聚类中心

	birchNode2 root;
	CreateTree(allUser, 0.5, root);

	getcenter(center, root);
	//cout << "聚类数据大小为" << root.data.size() << endl;
	//cout << "聚类种类为" << CountLeaf(root) << endl;
	//cout << "获得的聚类中心个数为" << center.size() << endl;
	//for (int i = 0; i < s_video.size(); i+=5)
	//{
	//	if(s_video[i].size()!= 0)
	//	center.push_back(F67User(u_video[i][0]));

	//}

	cout << "聚类中心个数为" << center.size() << endl;
	center[0].helpprint();


	//3.更新聚类中心
	//设置最大迭代次数和收敛检测
	int maxt = 10;//最大迭代次数
	int dc = 5;//若上一次和下一次之间变动种类不超过dc个则视为收敛
	int lastcenter = 0;
	double minr = 0.2;//最小相似度
	for (int k = 0; k < maxt; k++) {

		cout << "第" << k << "次迭代：\n" << "上次迭代与此次迭代相差为：" << center.size() - lastcenter << endl;
		if ((center.size() - lastcenter) < dc && k> 0 ) { cout << "收敛，算法结束" << endl; break; }
		lastcenter = center.size();//记录上一次聚类变动个数
		for (int i = 0; i < allUser.size(); i++)
		{
			//计算与所有聚类中心的距离
			int index = 0; //记录这一轮中哪个聚类中心将发生变动
			if (i % 200 == 0)cout << "已经运行" << i << "次" << endl;
			for (int j = 0; j < center.size(); j++)
			{
				double d = disTagsCal(center[j].user_tags, allUser[i].user_tags);
				if (allUser[i].disval < d)
				{
					//将其归为某一类
					allUser[i].disval = d;
					index = j;
				}


			}
			//当一个视频加入后重新更新聚类中心的标签
			allUser[i].clustercenter = center[index];//最终归类结果
			center[index].centerlen++;
			if (allUser[i].disval > minr)//小于minr表示不属于现有任何聚类中心
				centerchange(center[index], allUser[i], center[index].centerlen);
			else
			{
				allUser[i].centerlen++;//将该点设置为聚类中心
				allUser[i].clustercenter = allUser[i];
				center.push_back(allUser[i]);


			}

		}

		display_cluster(center);



	}
	//写入文本
	writeresulttxt(center);

}