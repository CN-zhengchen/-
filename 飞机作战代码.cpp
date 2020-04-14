//双方飞机，只有我们一方发起模拟进攻，假设对方不动，我们飞机每次只能用一架，输出每次模拟的结果，
//以及最后哪一方剩飞机了，剩了几架。
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;
struct SaveM//存储我方飞机数据
{
	double Lng;//经度
	double Lat;//纬度
	double Hit;//高度
	int numberM;//我方飞机编号
	int numberY;//敌方飞机编号
}*Msave;
struct SaveY//存储敌方飞机数据
{
	double Lng;//经度
	double Lat;//纬度
	double Hit;//高度
	int numberY;//敌方飞机的编号
	bool fall;//F代表没击败，T代表击败了
}*Ysave;
vector <vector<double>> Lengthsave(100);//存储我方飞机与地方飞机的距离
double jisuan(double Lng,double Lng1)//计算给定经纬度所相差的距离
{
	double result,trg,R=6371;
	trg=abs(Lng - Lng1);
	result = (abs(sin(trg / 2)) * R) * 2;
	return result;
}
void calculaeandcsort(int MYPLN,int YRPLN)//计算距离以及以距离为基准进行排序
{
	int i, j, k = 0;
	double LNG, LAT, HIT;
	for (i = 1; i <= MYPLN; i++)
	{
		for (j = 1; j <= YRPLN; j++)
		{
			Lengthsave[k][1] = double(i);
			Lengthsave[k][2] = double(j);
			LNG = jisuan(Msave[i - 1].Lng, Ysave[j - 1].Lng);
			LAT = jisuan(Msave[i - 1].Lat, Ysave[j - 1].Lat);
			HIT = abs(Msave[i - 1].Hit-Ysave[j - 1].Hit);
			Lengthsave[k][0] = sqrt((pow(LNG, 2) + pow(LAT, 2) + pow(HIT, 2)));
			k++;
		}
	}
	vector<vector<double>>::iterator left, right;//设置迭代器，排序时使用
	left = right = Lengthsave.begin();
	for (i = 0; i < MYPLN*YRPLN; i++)
	{
		right++;
	}
	sort(left, right);
}
void print(int MYPLN,int YRPLN)//输出函数，输出我方应该攻击对方哪一架飞机
{
	int i = 1,j;
	while (i <= min(MYPLN, YRPLN))//输出战斗结果
	{
		cout << "我方" << Lengthsave[0][1] << "号战机攻击对方" << Lengthsave[0][2] << "号战机,距离为";
		printf("%.3lfkm。\n", Lengthsave[0][0]);
		Ysave[int(Lengthsave[0][2]) - 1].fall = true;
		int number1 = Lengthsave[0][2];
		int number2 = Lengthsave[0][1];
		for (j = 0; j < MYPLN*YRPLN;)//将已被打掉的飞机和已经用过的飞机删除
		{
			if (Lengthsave[j][2] == number1)
			{
				Lengthsave.erase(Lengthsave.begin() + j);
			}
			else if (Lengthsave[j][1] == number2)
			{
				Lengthsave.erase(Lengthsave.begin() + j);
			}
			else
			{
				j++;
			}
		}
		i++;
	}
}
int main()
{
	//0存长度，1存我方编号，2存敌方编号
	//存储
	cout << "                         ||**********************************************************||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                多目标机群作战攻击策略小程序              ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||**********************************************************||" << endl;
	cout << "请分别输入我方战机的数量和敌方战机的数量，每一方战机数量不能超过10架。" << endl;
	int MYPLN, YRPLN;
	cin >> MYPLN >> YRPLN;
	for (int i = 0; i < Lengthsave.size(); i++)//进行内存分配，以便进行存储数据
	{
		Lengthsave[i].resize(3);
	}
	Msave = new SaveM[MYPLN];//动态分配内存，根据用户输入的数据分配内存
	Ysave = new SaveY[YRPLN];
	int i = 1;
	double x, y, z;
	double LNG, LAT, HIT;
	cout << "请输入我方战机的经纬高度坐标，经纬度在-180到180之间，负数代表西经，北纬。正数代表东经，南纬，高度单位为km。" << endl;
	while (i <= MYPLN)
	{
		cin >> x >> y >> z;
		Msave[i - 1].Lng = x;
		Msave[i - 1].Lat = y;
		Msave[i - 1].Hit = z;
		Msave[i - 1].numberM = i;
		i++;
	}
	i = 1;
	cout << "请输入敌方战机的坐标,坐标为正数。" << endl;
	while (i <= YRPLN)
	{
		cin >> x >> y >> z;
		Ysave[i - 1].Lng = x;
		Ysave[i - 1].Lat = y;
		Ysave[i - 1].Hit = z;
		Ysave[i - 1].fall = false;
		i++;
	}
	int j;
	i = 1;
	calculaeandcsort(MYPLN, YRPLN);
	print(MYPLN,YRPLN);
	int flag;
	if (MYPLN>YRPLN)//判断双方哪一方还剩下飞机
	{
		cout<<"我方还剩下"<<MYPLN-YRPLN<<"架飞机未攻击过敌方飞机。"<<endl;
	}
	else if (MYPLN == YRPLN)
	{
		cout << "双方都没有剩下飞机" << endl;
	}
	else
	{
		cout << "敌方还剩下" << YRPLN - MYPLN << "架飞机。" << endl;
		while (1)
		{
			YRPLN -= MYPLN;
			cout << "是否继续派飞机进攻对面,如需继续请输入1，如若不需要请按0。" << endl;
			cin >> flag;
			if (flag == 1 && YRPLN > 0)//执行继续派遣飞机攻击敌方
			{
				cout << "请输入派出飞机架数" << endl;
				cin >> MYPLN;
				i = 1;
				cout << "请输入我方战机的经纬高度坐标，经纬度在-180到180之间，负数代表西经，北纬。正数代表东经，南纬。高度单位为km" << endl;
				Msave = new SaveM[MYPLN];
				while (i <= MYPLN)
				{
					cin >> x >> y >> z;
					Msave[i - 1].Lng = x;
					Msave[i - 1].Lat = y;
					Msave[i - 1].Hit = z;
					Msave[i - 1].numberM = i;
					i++;
				}
				int k = 0, l = 0;
				for (i = 1; i <= MYPLN; i++)
				{
					for (j = 1; j <= YRPLN; j++)
					{
						if (Ysave[l].fall==true)
						{
							j--;
							l++;
						}
						else
						{
							Lengthsave[k][1] = double(i);
							Lengthsave[k][2] = (l + 1);
							LNG = jisuan(Msave[i - 1].Lng, Ysave[j - 1].Lng);
							LAT = jisuan(Msave[i - 1].Lat, Ysave[j - 1].Lat);
							HIT = abs(Msave[i - 1].Hit - Ysave[j - 1].Hit);
							Lengthsave[k][0] = sqrt((pow(LNG, 2) + pow(LAT, 2) + pow(HIT, 2)));
							k++;
							l++;
						}
					}
					l = 0;
				}
				vector<vector<double>>::iterator left, right;//设置迭代器，排序的时候使用
				left = right = Lengthsave.begin();
				for (i = 0; i < MYPLN*YRPLN; i++)
				{
					right++;
				}
				sort(left, right);
				i = 1;
				while (i <= min(MYPLN, YRPLN))
				{
					l = 0;
					int number1 = Lengthsave[0][2];
					int number2 = Lengthsave[0][1];
					cout << "我方" << Lengthsave[0][1] << "号战机攻击对方" << Lengthsave[0][2] << "号战机,距离为";
					printf("%.3lfkm。\n", Lengthsave[0][0]);
					Ysave[int(Lengthsave[0][2]) - 1].fall = true;
					for (j = 0; j < MYPLN*YRPLN;j++)//将已被打掉的飞机和已经用过的飞机删除
					{
						if (Lengthsave[l][2] == number1)
						{
							Lengthsave.erase(Lengthsave.begin() + l);
						}
						else if (Lengthsave[l][1] == number2)
						{
							Lengthsave.erase(Lengthsave.begin() + l);
						}
						else
						{
							l++;
						}
					}
					i++;
				}
			}
			else if (flag == 0)
			{
				break;
			}
			else
			{
				cout << "输入错误，请重新输入。" << endl;
				MYPLN = 0;
			}
			if (YRPLN - MYPLN <= 0 || YRPLN <= 0)
			{
				cout << "敌方飞机已经全部剿灭,您无需再派遣飞机" << endl;
				break;
			}
		}
	}
	cout << "感谢您的使用，祝您百战百胜" << endl;
	system("pause");
	return 0;
}
