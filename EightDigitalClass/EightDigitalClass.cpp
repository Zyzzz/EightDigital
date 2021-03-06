// EightDigitalClass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<time.h>
#include <vector>
#define N 9
using namespace std;
class Node
{
public:
	Node(vector<int> picture, int deepNum, int fitness, bool visted){
		this->picture = picture;
		this->deepNum = deepNum;
		this->fitness = fitness;
		this->visted = visted;
	}
	void setvisted(bool visted) {
		this->visted = visted;
	}
	void setinfo(int deepNum, int fitness, bool visted)
	{
		this->deepNum = deepNum;
		this->fitness = fitness;
		this->visted = visted;
	}
	vector<int> getPicture() {
		return picture;
	}
	int getDeepNum() {
		return deepNum;
	}
	int getFitness() {
		return fitness;
	}
	bool getVisted() {
		return visted;
	}
private:
	vector<int> picture;
	int deepNum;
	int fitness;
	bool visted;
};

class EightDigital
{
public:
	vector<int> start;
	vector<int> path;
	vector<int> target;
	bool isSolution();
	void autoGenerate(vector<int> prcture);
	int Astar();
	void showAll(int res);
private:
	void show(int res);
	void saveState(Node curstate);
	bool isEqual(vector<int> picture, int n);
	bool isEqual(vector<int> picture);
	int evalute(vector<int> picture);
	bool move(vector<int> picture, vector<int>& temp, int n);
	int checkAdd(vector<int> picture);
	int inverseNumber(vector<int> picture);
	vector<Node> state;

};
int EightDigital::inverseNumber(vector<int> picture){
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (picture[j] == 0)
				continue;
			if (picture[i] > picture[j])
				sum++;
		}
	}
	return sum;
}
bool EightDigital::isSolution() {
	if (inverseNumber(start) % 2 == inverseNumber(target) % 2)
		return true;//有解
	else
		return false;//无解
}
bool EightDigital::isEqual(vector<int> picture, int n) {
	vector<int> temp = state[n].getPicture();
	for (int i = 0; i < N; i++) {
		if (temp[i] != picture[i])
			return false;
	}
	return true;
}
bool EightDigital::isEqual(vector<int> picture) {
	for (int i = 0; i < N; i++) {
		if (target[i] != picture[i])
			return false;
	}
	return true;
}
int EightDigital::evalute(vector<int> picture) {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		if (target[i] != picture[i])
			sum++;
	}
	return sum;
}
bool EightDigital::move(vector<int> picture, vector<int>& temp, int n) {
	//1 上 2 下 3 左 4 右
	int pos = 0;
	for (int i = 0; i < N; i++) {
		temp.push_back(picture[i]);
		if (picture[i] == 0) {
			pos = i;
		}
	}
	switch (n)
	{
	case 1:
		if (pos == 0 || pos == 1 || pos == 2)
			return false;
		temp[pos] = picture[pos - 3];
		temp[pos - 3] = 0;
		break;
	case 2:
		if (pos == 6 || pos == 7 || pos == 8)
			return false;
		temp[pos] = picture[pos + 3];
		temp[pos + 3] = 0;
		break;
	case 3:
		if (pos == 0 || pos == 3 || pos == 6)
			return false;
		temp[pos] = picture[pos - 1];
		temp[pos - 1] = 0;
		break;
	case 4:
		if (pos == 2 || pos == 5 || pos == 8)
			return false;
		temp[pos] = picture[pos + 1];
		temp[pos + 1] = 0;
		break;
	default:
		return false;
	}
	return true;
}
void EightDigital::saveState(Node curState) {
	state.push_back(curState);
}
int  EightDigital::checkAdd(vector<int> picture) {
	for (int i = 0; i < state.size(); i++) {
		if (isEqual(picture, i)) 
			return i;
	}
	return -1;
}
int EightDigital::Astar() {
	int deepnum = 0; int curpos=0;
	Node curnode = Node(start, deepnum++, evalute(start), false);
	saveState(curnode);
	path.push_back(-1);
	while (!isEqual(curnode.getPicture())) {
		for (int i = 1; i < 5; i++) {
			vector<int> temp;
			if (move(curnode.getPicture(), temp, i)) {
				int pos = checkAdd(temp); 
				if (pos == -1) {
					path.push_back(curpos);
					saveState(Node(temp, curnode.getDeepNum() + 1, evalute(temp) + curnode.getDeepNum() + 1, false));
				}
				else { 
					int len = curnode.getDeepNum() + 1;
					int fit = evalute(temp) + len;
					if (fit < state[pos].getFitness()) {
						path[pos] = curpos;
						state[pos].setinfo(len, fit, false);
					}
				}
			}
		}
		state[curpos].setvisted(true);
		int minCur=-1;
		for (int i = 0; i < state.size(); i++) {
			if(!state[i].getVisted()&&(minCur==-1||state[minCur].getFitness()>state[i].getFitness()))
				minCur=i;
		}
		curpos = minCur;
		curnode = state[curpos];
	}
	return curpos;
}
void EightDigital::autoGenerate(vector<int> picture)
{	
	srand((unsigned int)(time(NULL)));
	int maxMove = 50;
	while (maxMove--) {
		vector<int> tmp;
		int dir = rand() % 4 + 1;
		if (move(picture, tmp, dir))
			picture = tmp;
	}
	start = picture;
}
void EightDigital::showAll(int res)
{
	vector<int> shortest;
	while (res != 0) {
		shortest.push_back(res);
		res = path[res];
	}
	cout << "第0步："<<endl;
	show(0);
	for (int i = shortest.size() - 1; i >= 0; i--) {
		cout << "第 " << shortest.size() - i << " 步";
		cout << endl;
		show(shortest[i]);
	}
}
void EightDigital::show(int res)
{
	vector<int> picture = state[res].getPicture();
	for (int i = 0; i < picture.size(); i++) {
		
		cout << picture[i] << " ";
		if (i == 2 || i == 5 || i == 8) {
			cout << endl;
		}
	}
	cout << endl;
}
int main()
{
	EightDigital E;
	vector<int> target = { 1,2,3,4,5,6,7,8,0 };
	E.target = target;
	E.autoGenerate(target);
	if (!E.isSolution()) {
		cout << "无解！";
	}
	int res = E.Astar();
	E.showAll(res);
}

