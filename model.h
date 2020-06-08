#pragma once
#include<stdio.h>

//��������·
typedef struct Bus
{
	char* name;	//������
	int start;
	int end;
}Bus;

//��ʾվ����Ϣ
typedef struct Station
{
	char* station;	//վ����
	struct Route* routes;	//�Ӹ�վ���������������·�ߵ�����
}Station;

//��ʾ������·�е�һ��·��
typedef struct Route
{
	int station;	//ָ���վ��������
	int bus;	//����������
	int distance;	//��վ֮�乫·�ľ���
	bool visited;	//����ʱ�ı�ʶ��
	struct Route* next;	//��ʼվ����ͬ�ģ���һ������·��
}Route;

//����������ͼ����Ϣ
typedef struct BusMap
{
	Bus* buses;	//������·����
	Station* stations;	//վ������
	int station_num;	//վ����
	int bus_num;	//������·��
}BusMap;

typedef struct Path {
	int station_num;	//·���е�վ����
	int station;	//·��������վ����
	int bus;	//ͨ��վ��Ĺ��������
}Path;