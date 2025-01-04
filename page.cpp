#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#define ORDER_NUM 200
using namespace std;
int inum;
int block_num;//�ڴ������
int phy_memory[ORDER_NUM];//�����ڴ�
int page_fault;//ҳ��ʧЧ����
double miss;//ȱҳ��
int order[ORDER_NUM];//ָ������
int page[ORDER_NUM];//ָ���Ӧҳ��

void OPT();//Optimal
void LRU();//Least Recently Used
void FIFO();//Fist In First Out

void show_info();
int is_exit(int page);//���ҳ���Ƿ����ڴ����
int find_empty();//Ѱ�ҿ����ڴ��
void init_ins();//��ʼ��ָ������
void to_page();//ָ�����б任Ϊҳ��ַ��
void initMemory(int n);//��ʼ���ڴ��

int main()
{
	init_ins();
	to_page();
	int n;
	while (1)
	{
		printf("�������ڴ������(1-page_num): ");
		cin >> n;
		initMemory(n);
		printf("\n---------OPT�㷨��---------\n");
		OPT();
		initMemory(n);
		printf("\n---------LRU�㷨��---------\n");
		LRU();
		initMemory(n);
		printf("\n---------FIFO�㷨��---------\n");
		FIFO();
	}
	return 0;
}

void init_ins()//��ʼ��ָ������
{
	srand((unsigned)time(NULL));
	int a = rand() % ORDER_NUM; //0-199
	int rate = rand() % 10;//0~9,ģ�����
	int tmp = 0;
	order[0] = 0;
	for (int i = 1; i < ORDER_NUM; i++)
	{
		if(a==0)
		{
			while(rate==7)
				rate = rand() % 10;
		}
		if (rate <= 6)
		{
			a++;
			order[i] = a;
			if (a == ORDER_NUM-1)//ֻ����ǰ��
				rate = 7;	
			else
				rate = rand() % 10;
		}
		else if (rate == 7)//10%�ĸ���
		{
			tmp = rand() % (a);//��ǰ��
			a = tmp;
			order[i] = a;
			if(a==0)
			{
				while(rate==7)
					rate = rand() % 10;
			}
		}
		else if (rate >= 8)//%20�ĸ���
		{
			tmp = rand() % (ORDER_NUM - a ) + a ; //�����
			a = tmp;
			order[i] = a;
			if (a == ORDER_NUM-1)
				rate = 7;
			else
				rate = rand() % 10;
		}
	}
	printf("ָ������Ϊ:");
	for (int i = 0; i < ORDER_NUM; i++)
	{
		if (i % 20 == 0)
			printf("\n");
		cout << setw(3) << order[i] << " ";
	}
	printf("\n");
}
void to_page()//ָ�����б任Ϊҳ��ַ��
{
	int page_index;
	printf("������ÿҳָ��������1-ORDER_NUM��\n");
	cin >> inum;
	for (int i = 0; i < ORDER_NUM; i++)
		page[i] = order[i] / inum;
	printf("ҳ���ַ��Ϊ:");
	for (int i = 0; i < ORDER_NUM; i++)
	{
		page_index = i / inum;
		if ( i % inum == 0)
			cout << "\nPage " << setw(2) << page_index << ": " ;
		cout << setw(3) << page[i] << " ";
	}
	printf("\n");
}
void initMemory(int n)//��ʼ���ڴ��
{
	block_num = n;
	for (int i = 0; i < block_num; i++)
		phy_memory[i] = -1;
}
int is_exit(int page)//���ҳ���Ƿ����ڴ����
{
	for (int i = 0; i < block_num; i++)
	{
		if (phy_memory[i] == page)
			return i;
	}
	return -1;
}
int find_empty()//Ѱ�ҿ����ڴ��
{
	for (int i = 0; i < block_num; i++)
	{
		if (phy_memory[i] == -1)
			return i;
	}
	return -1;
}
void show_info()
{
	//printf("�ڴ�飺");
	//for (int i = 0; i < block_num; i++) 
	//{
	//	if (phy_memory[i] != -1) 
	//		printf("%d ", phy_memory[i]);
	//}
	//printf("\n");
	;
}
void OPT()
{
	int flag = -1;//�ڴ����Ƿ���ڸ�ҳ��
	int empty;//�����ڴ���
	page_fault = 0;
	int* distance = new int[block_num];
	for (int i = 0; i < block_num; i++)
		distance[i] = 0;
	for (int i = 0; i < ORDER_NUM; i++)
	{
		flag = is_exit(page[i]);
		if (flag != -1)
			//printf("��ǰ����ҳ��%d�����ڴ���\n", page[i]);
			;
		else//ȱҳ
		{
			//��������distance
			for (int i = 0; i < block_num; i++)
				distance[i] = 0;
			page_fault++;
			empty = find_empty();
			if (empty != -1)
			{//���ڿ��ڴ��
				phy_memory[empty] = page[i];
				show_info();
			}
			else
			{
				for (int j = 0; j < block_num; j++)
				{
					for(int k = i; k < ORDER_NUM;k++)
					{
						if (phy_memory[j] != page[k])
							distance[j]++;
						else
							break;
					}
				}
				int temp = 0;
				for (int i = 0; i < block_num; i++)
				{
					if (distance[i] >= distance[temp])
						temp = i;
				}
				//printf("��ǰ����ҳ��%d����ҳ��%d\n", page[i], phy_memory[temp]);
				phy_memory[temp] = page[i];//����ҳ��
				show_info();
			}
		}
	}
	miss = page_fault * 1.0 / ORDER_NUM;
	printf("OPT�㷨ȱҳ����Ϊ��%d, ȱҳ��Ϊ %.4lf\n", page_fault, miss);
	delete[]distance;
}
void LRU()
{
	int* used = new int[block_num+2];
	for (int i = 0; i < block_num; i++)
		used[i] = 0;
	int flag = -1;//�ڴ����Ƿ���ڸ�ҳ��
	int empty;//�����ڴ���
	int max_index = -1;//�����±�
	int max_used = 0;//����
	page_fault = 0;
	for (int i = 0; i < ORDER_NUM; i++)
	{
		flag = is_exit(page[i]);
		for (int j = 0; j < block_num; j++)
		{
			if (used[j] >= max_used)
			{
				max_used = used[j];
				max_index = j;
			}
		}
		if (flag != -1)
		{//�Ѵ��ڣ���ʹ�ô���++
			//printf("��ǰ����ҳ��%d�����ڴ���\n", page[i]);
			for (int j = 0; j < block_num; j++)
				used[j]++;
			used[flag] = 0;
		}
		else
		{
			page_fault++;
			empty = find_empty();
			if (empty != -1)//�п��ڴ��
			{
				phy_memory[empty] = page[i];
				show_info();
				used[empty] = 0;
				for (int j = 0; j < empty; j++)
					used[j]++;
			}
			else//�޿���
			{
				//printf("��ǰ����ҳ��%d���󻻳�ҳ��%d\n", page[i], phy_memory[max_index]);
				phy_memory[max_index] = page[i];
				used[max_index] = 0;
				for (int j = 0; j < block_num; j++)
					used[j]++;
				max_index = -1;
				max_used = 0;
				show_info();
			}
		}
	}
	miss = page_fault * 1.0 / ORDER_NUM;
	printf("LRU�㷨ȱҳ����Ϊ��%d, ȱҳ��Ϊ %.4lf\n", page_fault, miss);
	delete[]used;
}
void FIFO()
{
	int* fre = new int[block_num + 2];
	for (int i = 0; i < block_num; i++)
		fre[i] = 0;
	int flag = -1;//�ڴ����Ƿ���ڸ�ҳ��
	int empty;//�����ڴ���
	int max_index = -1;//�����±�
	int max_used = 0;//����
	page_fault = 0;
	for (int i = 0; i < ORDER_NUM; i++)
	{
		flag = is_exit(page[i]);
		for (int j = 0; j < block_num; j++)
		{
			if (fre[j] >= max_used)
			{
				max_used = fre[j];
				max_index = j;
			}
		}
		if (flag != -1)
		{//�Ѵ��ڣ���ʹ�ô���++
			//printf("��ǰ����ҳ��%d�����ڴ���\n", page[i]);
			for (int j = 0; j < block_num; j++)
				fre[j]++;
		}
		else
		{
			page_fault++;
			empty = find_empty();
			if (empty != -1)//�п��ڴ��
			{
				phy_memory[empty] = page[i];
				show_info();
				fre[empty] = 0;
				for (int j = 0; j < empty; j++)
					fre[j]++;
			}
			else//�޿���
			{
				//printf("��ǰ����ҳ��%d���󻻳�ҳ��%d\n", page[i], phy_memory[max_index]);
				phy_memory[max_index] = page[i];
				fre[max_index] = 0;
				for (int j = 0; j < block_num; j++)
					fre[j]++;
				max_index = -1;
				max_used = 0;
				show_info();
			}
		}
	}
	miss = page_fault * 1.0 / ORDER_NUM;
	printf("FIFO�㷨ȱҳ����Ϊ��%d, ȱҳ��Ϊ %.4lf\n", page_fault, miss);
	delete[]fre;
}
