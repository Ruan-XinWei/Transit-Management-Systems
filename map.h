//#pragma once
#include "model.h"
#include <string>

using namespace std;

#define None -1
#define Status int
#define ST_FALL 0
#define ST_OK 1

class Map
{
public:

	//·������
	int ROUTE_NUM = -1;
	//����������
	int BUS_NUM = -1;
	//վ������
	int STATION_NUM = -1;
	//����ѯ·������
	int MaxPath = 5;
	//ÿ��·����󳤶�
	int MaxLength = 20;
	//�����
	int MaxName = 100;

	//·�����飬��������ȡ������·�����ݴ���
	int** ROUTES;
	//���������飬��������ȡ�����Ĺ��������ݴ���
	char*** BUSES;
	//վ�����飬��������ȡ������վ�����ݴ���
	char** STATIONS;

	//�ļ���ת��
	const char* filename = "./tmptmptmp.txt";
	//BUSES�ļ�λ��
	const char* BUSESFILE = "./BUSES.txt";
	//ROUTES�ļ�λ��
	const char* ROUTESFILE = "./ROUTES.txt";
	//STATIONS�ļ�λ��
	const char* STATIONFILE = "./STATIONS.txt";

	//����ȫͼ����
	BusMap g_sMap;

	Map();
	~Map();

	//��ȡROUTE_NUM��BUS_NUM��STATION_NUM
	void Init();

	//��ROUTES��BUSES��STATIONS����ռ䡢������
	void InitData();

	//�����ݼ��ص�g_sMap��
	void LoadMapDate(BusMap& g_sMap);

	//ͨ�����������Ʋ��ҹ��������
	int FindBus(BusMap g_sMap, char* bus);

	//ͨ��վ�����Ʋ���վ����
	int FindStation(BusMap g_sMap, char* station);

	//ͨ��վ�����Ʋ���վ�㣬�������ҽ�����浽str��������
	void Querystation(BusMap g_sMap, char* name, string& str);

	//ͨ�����������Ʋ��ҹ��������������ҽ��������str��������
	void QueryBus(BusMap g_sMap, char* name, string& str);

	//������бߵı������
	void ClearVisited(BusMap& g_sMap);

	//ͨ�����ƣ���������վ��֮���Ƿ����·��
	int HasPath(BusMap g_sMap, char* pStart, char* pEnd);

	//ͨ��վ���ţ���������վ��֮���Ƿ����·��
	bool HasPath(BusMap g_sMap, int start, int end);

	//(int����)�ڵ�ͼ��ͨ��վ����Ų�������վ��֮���Ƿ����ͨ��bus��·��
	bool HasPath(BusMap g_sMap, int start, int end, int bus);

	//���ظ�վ�����еĹ�����
	int Busnum(BusMap g_sMap, int start);

	//ͨ��վ�����ƣ���������վ��֮���·�������ת��һ�Σ�����������浽paths��
	int QueryRoute(BusMap g_sMap, char* start, char* end, Path** paths);

	//ͨ��վ���ţ���������վ��֮���·�������ת��һ�Σ�����������浽paths��
	int QueryRoute(BusMap g_sMap, int start, int end, Path** paths);

	//�����ҳ�����·��������ʽ���浽str��
	void QueryRoute(BusMap g_sMap, char* start, char* end, string& str);

	//���ļ���ɾ��վ����Ϣ
	int DeleteStation(const char* FILENAME, char* station);

	//���ļ������վ����Ϣ
	int AddStation(const char* FILENAME, char* station);

	//���ļ��и���վ����Ϣ
	int UpdateStation(const char* FILENAME, char* oldname, char* newname);

	//���ļ���ɾ��·����Ϣ
	int DeleteRoute(const char* FILENAME, int bus, int start, int end, int meter);

	//���ļ������·����Ϣ
	int AddRoute(const char* FILENAME, int bus, int start, int end, int meter);

	//���ļ��и���·����Ϣ
	int UpdateRoute(const char* FILENAME, int oldbus, int oldstart, int oldend, int oldmeter, int newbus, int newstart, int newend, int newmeter);

	//���ļ���ɾ����������Ϣ
	int DeleteBuses(const char* fliename, char* bus);

	//���ļ��и��¹�������Ϣ
	int UpdateBuses(const char* f, char* bus, char* start, char* end, char* nbus, char* nstart, char* nend);

	//���ļ�����ӹ�������Ϣ
	int AddBuses(const char* FILENAME, char* bus, char* start, char* end);

};