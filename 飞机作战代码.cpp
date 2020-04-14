//˫���ɻ���ֻ������һ������ģ�����������Է����������Ƿɻ�ÿ��ֻ����һ�ܣ����ÿ��ģ��Ľ����
//�Լ������һ��ʣ�ɻ��ˣ�ʣ�˼��ܡ�
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
struct SaveM//�洢�ҷ��ɻ�����
{
	double Lng;//����
	double Lat;//γ��
	double Hit;//�߶�
	int numberM;//�ҷ��ɻ����
	int numberY;//�з��ɻ����
}*Msave;
struct SaveY//�洢�з��ɻ�����
{
	double Lng;//����
	double Lat;//γ��
	double Hit;//�߶�
	int numberY;//�з��ɻ��ı��
	bool fall;//F����û���ܣ�T���������
}*Ysave;
vector <vector<double>> Lengthsave(100);//�洢�ҷ��ɻ���ط��ɻ��ľ���
double jisuan(double Lng,double Lng1)//���������γ�������ľ���
{
	double result,trg,R=6371;
	trg=abs(Lng - Lng1);
	result = (abs(sin(trg / 2)) * R) * 2;
	return result;
}
void calculaeandcsort(int MYPLN,int YRPLN)//��������Լ��Ծ���Ϊ��׼��������
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
	vector<vector<double>>::iterator left, right;//���õ�����������ʱʹ��
	left = right = Lengthsave.begin();
	for (i = 0; i < MYPLN*YRPLN; i++)
	{
		right++;
	}
	sort(left, right);
}
void print(int MYPLN,int YRPLN)//�������������ҷ�Ӧ�ù����Է���һ�ܷɻ�
{
	int i = 1,j;
	while (i <= min(MYPLN, YRPLN))//���ս�����
	{
		cout << "�ҷ�" << Lengthsave[0][1] << "��ս�������Է�" << Lengthsave[0][2] << "��ս��,����Ϊ";
		printf("%.3lfkm��\n", Lengthsave[0][0]);
		Ysave[int(Lengthsave[0][2]) - 1].fall = true;
		int number1 = Lengthsave[0][2];
		int number2 = Lengthsave[0][1];
		for (j = 0; j < MYPLN*YRPLN;)//���ѱ�����ķɻ����Ѿ��ù��ķɻ�ɾ��
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
	//0�泤�ȣ�1���ҷ���ţ�2��з����
	//�洢
	cout << "                         ||**********************************************************||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                ��Ŀ���Ⱥ��ս��������С����              ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||                                                          ||" << endl;
	cout << "                         ||**********************************************************||" << endl;
	cout << "��ֱ������ҷ�ս���������͵з�ս����������ÿһ��ս���������ܳ���10�ܡ�" << endl;
	int MYPLN, YRPLN;
	cin >> MYPLN >> YRPLN;
	for (int i = 0; i < Lengthsave.size(); i++)//�����ڴ���䣬�Ա���д洢����
	{
		Lengthsave[i].resize(3);
	}
	Msave = new SaveM[MYPLN];//��̬�����ڴ棬�����û���������ݷ����ڴ�
	Ysave = new SaveY[YRPLN];
	int i = 1;
	double x, y, z;
	double LNG, LAT, HIT;
	cout << "�������ҷ�ս���ľ�γ�߶����꣬��γ����-180��180֮�䣬����������������γ����������������γ���߶ȵ�λΪkm��" << endl;
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
	cout << "������з�ս��������,����Ϊ������" << endl;
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
	if (MYPLN>YRPLN)//�ж�˫����һ����ʣ�·ɻ�
	{
		cout<<"�ҷ���ʣ��"<<MYPLN-YRPLN<<"�ܷɻ�δ�������з��ɻ���"<<endl;
	}
	else if (MYPLN == YRPLN)
	{
		cout << "˫����û��ʣ�·ɻ�" << endl;
	}
	else
	{
		cout << "�з���ʣ��" << YRPLN - MYPLN << "�ܷɻ���" << endl;
		while (1)
		{
			YRPLN -= MYPLN;
			cout << "�Ƿ�����ɷɻ���������,�������������1����������Ҫ�밴0��" << endl;
			cin >> flag;
			if (flag == 1 && YRPLN > 0)//ִ�м�����ǲ�ɻ������з�
			{
				cout << "�������ɳ��ɻ�����" << endl;
				cin >> MYPLN;
				i = 1;
				cout << "�������ҷ�ս���ľ�γ�߶����꣬��γ����-180��180֮�䣬����������������γ����������������γ���߶ȵ�λΪkm" << endl;
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
				vector<vector<double>>::iterator left, right;//���õ������������ʱ��ʹ��
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
					cout << "�ҷ�" << Lengthsave[0][1] << "��ս�������Է�" << Lengthsave[0][2] << "��ս��,����Ϊ";
					printf("%.3lfkm��\n", Lengthsave[0][0]);
					Ysave[int(Lengthsave[0][2]) - 1].fall = true;
					for (j = 0; j < MYPLN*YRPLN;j++)//���ѱ�����ķɻ����Ѿ��ù��ķɻ�ɾ��
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
				cout << "����������������롣" << endl;
				MYPLN = 0;
			}
			if (YRPLN - MYPLN <= 0 || YRPLN <= 0)
			{
				cout << "�з��ɻ��Ѿ�ȫ������,����������ǲ�ɻ�" << endl;
				break;
			}
		}
	}
	cout << "��л����ʹ�ã�ף����ս��ʤ" << endl;
	system("pause");
	return 0;
}
