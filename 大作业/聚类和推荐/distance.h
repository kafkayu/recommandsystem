#pragma once
#include"video.h"
#include<iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

//default (1)	
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator myset_intersection(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2,
    OutputIterator result);
//custom (2)	
template <class InputIterator1, class InputIterator2,
    class OutputIterator, class Compare>
    OutputIterator myset_intersection(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2,
        OutputIterator result, Compare comp);
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator myset_intersection(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2,
    OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2) ++first1;
        else if (*first2 < *first1) ++first2;
        else {
            if (first1->weight <= first2->weight)*result = *first1;
            else *result = *first2;

            ++result; ++first1; ++first2;
        }
    }
    return result;
}
double disTagsCal(vector<Tags>A, vector<Tags>B)
{
    vector<Tags> v;
    //v.push_back(A[0]);
    v.resize(min(A.size(), B.size()));
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    //set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集 
    //wcout.imbue(locale("chs"));
    /*for (auto i : A)
    {
        wcout << i.tags << i.weight << endl;
    }*/
    vector<Tags>::iterator end = myset_intersection(A.begin(), A.end(), B.begin(), B.end(), v.begin());
    //cout << "---------交集------------- " << endl;
    //wcout.imbue(locale("chs"));
    double res = 0;
    for (auto i = v.begin(); i != end; i++)
    {
        // wcout << i->tags << i->weight << endl;
        res += i->weight;
    }

    //cout << endl;


    return res;
}

double disTagsCal(User A, User B)
{
    return disTagsCal(A.user_tags, B.user_tags);
}
double disTagsCal(User A, Video B)
{
    return disTagsCal(A.user_tags, B.video_tags);
}
double disTagsCal(Video B, User A)
{
    return disTagsCal(A.user_tags, B.video_tags);
}
double disTagsCal(Video A, Video B)
{
    return  disTagsCal(A.video_tags, B.video_tags);
}
void writeresult(vector<Video> data)
{
    vector<vector<double>> res;
    for (int i = 0; i < data.size(); i++)
    {
        vector<double> T;
        for (int j = 0; j < data.size(); j++)
        {
            T.push_back(disTagsCal(data[i], data[j]));
        }
        res.push_back(T);

    }


    std::ofstream fout;
    fout.open("mat.txt", std::ios::app);//在文件末尾追加写入
    for (auto i : res) {
        for (auto j : i) {
            fout << j << " ";
        }
        fout << "\n";
    }

    //fout << res << std::endl;//每次写完一个矩阵以后换行
    fout.close();


}

