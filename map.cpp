#include "pch.h"
#include<iostream>
#include"model.h"
#include <stack>
#include "map.h"
#include<fstream>
#include<string>

using namespace std;

Map::Map()
{
}

Map::~Map()
{
}

//��ȡROUTE_NUM��BUS_NUM��STATION_NUM
void Map::Init() {
	//��ȡ·������
	fstream FileRoutes(Map::ROUTESFILE);
	if (!FileRoutes.is_open()) {
		return;
	}
	string tmp;
	int ROUTE_NUM_TMP = 0;
	while (getline(FileRoutes, tmp)) {
		++ROUTE_NUM_TMP;
	}
	ROUTE_NUM = ROUTE_NUM_TMP;

	//��ȡ����������
	fstream FileBuses(Map::BUSESFILE);
	if (!FileBuses.is_open()) {
		return;
	}
	string name;
	int BUS_NUM_TMP = 0;
	while (getline(FileBuses, name)) {
		++BUS_NUM_TMP;
	}
	BUS_NUM = BUS_NUM_TMP / 3;

	//��ȡվ������
	fstream FileStations(Map::STATIONFILE);
	if (!FileStations.is_open()) {
		return;
	}
	string station;
	int STATION_NUM_TMP = 0;
	while (getline(FileStations, station)) {
		++STATION_NUM_TMP;
	}
	STATION_NUM = STATION_NUM_TMP;
}

//��ROUTES��BUSES��STATIONS����ռ䡢������
void Map::InitData() {
	Init();

	//ROUTES����ռ�
	ROUTES = (int**)malloc(ROUTE_NUM * sizeof(int*));
	for (int i = 0; i < ROUTE_NUM; ++i) {
		ROUTES[i] = (int*)malloc(4 * sizeof(int));
	}

	//BUSES����ռ�
	BUSES = (char***)malloc(BUS_NUM * sizeof(char**));
	for (int i = 0; i < BUS_NUM; ++i) {
		BUSES[i] = (char**)malloc(3 * sizeof(char*));
	}
	for (int i = 0; i < BUS_NUM; ++i) {
		for (int j = 0; j < 3; ++j) {
			BUSES[i][j] = (char*)malloc(MaxName * sizeof(char));
		}
	}

	//STATIONS����ռ�
	STATIONS = (char**)malloc(STATION_NUM * sizeof(char*));
	for (int i = 0; i < STATION_NUM; ++i) {
		STATIONS[i] = (char*)malloc(MaxName * sizeof(char));
	}

	//ROUTES������
	FILE* file = fopen(Map::ROUTESFILE, "r");

	int d;
	for (int i = 0; i < ROUTE_NUM; ++i) {
		for (int j = 0; j < 4; ++j) {
			fscanf(file, "%d", &d);
			ROUTES[i][j] = d;
		}
	}

	//BUSES������
	fstream FileBuses(Map::BUSESFILE);
	if (!FileBuses.is_open()) {
		return;
	}
	string name;
	int index = 0;
	while (getline(FileBuses, name)) {
		strcpy(BUSES[index / 3][index % 3], name.c_str());
		++index;
	}

	//STATIONS������
	fstream FileStations(Map::STATIONFILE);
	if (!FileStations.is_open()) {
		return;
	}
	string station;
	int stationnum = 0;
	while (getline(FileStations, station)) {
		strcpy(STATIONS[stationnum], station.c_str());
		++stationnum;
	}

	FileBuses.close();
	FileStations.close();

	//�����ݴ���g_sMap��
	LoadMapDate(g_sMap);
}

//�����ݼ��ص�g_sMap��
void Map::LoadMapDate(BusMap& g_sMap) {
	//���빫��������
	g_sMap.bus_num = BUS_NUM;
	g_sMap.buses = (Bus*)malloc(sizeof(Bus) * BUS_NUM);
	for (int i = 0; i < BUS_NUM; ++i) {
		g_sMap.buses[i].name = BUSES[i][0];
		g_sMap.buses[i].start = g_sMap.buses[i].end = None;
	}

	//����վ������
	g_sMap.station_num = STATION_NUM;
	g_sMap.stations = (Station*)malloc(sizeof(Station) * STATION_NUM);
	for (int i = 0; i < STATION_NUM; ++i) {
		g_sMap.stations[i].station = STATIONS[i];
		g_sMap.stations[i].routes = NULL;
	}

	//���빫���������յ�
	for (int i = 0; i < g_sMap.bus_num; ++i) {
		g_sMap.buses[i].start = FindStation(g_sMap, BUSES[i][1]);
		g_sMap.buses[i].end = FindStation(g_sMap, BUSES[i][2]);
	}

	//����·��
	for (int i = 0; i < ROUTE_NUM; ++i) {
		//·���½ڵ�
		Route* pnew = (Route*)malloc(sizeof(Route));
		if (pnew != NULL) {
			pnew->bus = ROUTES[i][0];
			pnew->station = ROUTES[i][2];
			pnew->distance = ROUTES[i][3];
			pnew->next = NULL;
		}

		//���½ڵ����
		if (g_sMap.stations[ROUTES[i][1]].routes == NULL) {
			g_sMap.stations[ROUTES[i][1]].routes = pnew;
		}
		else {
			Route* p = g_sMap.stations[ROUTES[i][1]].routes;
			if (p != NULL) {
				while (p->next != NULL) {
					p = p->next;
				}
				p->next = pnew;
			}
		}
	}
}

//ͨ�����������Ʋ��ҹ��������
int Map::FindBus(BusMap g_sMap, char* bus) {
	for (int i = 0; i < g_sMap.bus_num; ++i) {
		if (strcmp(g_sMap.buses[i].name, bus) == 0) {
			return i;
		}
	}
	return None;
}

//ͨ��վ�����Ʋ���վ����
int Map::FindStation(BusMap g_sMap, char* station) {
	for (int i = 0; i < g_sMap.station_num; ++i) {
		if (strcmp(g_sMap.stations[i].station, station) == 0) {
			return i;
		}
	}
	return None;
}

//ͨ��վ�����Ʋ���վ�㣬�������ҽ�����浽str��������
void Map::Querystation(BusMap g_sMap, char* name, string& str) {
	int nStation = FindStation(g_sMap, name);
	//վ��û��������
	if (nStation == None) {
		//printf("û�и�վ��\n");
		str.append("û�и�վ��\r\n");
	}
	else {
		//printf("��%sʻ���Ĺ�����\n", name);
		str.append("��");
		str.append(name);
		str.append("ʻ���Ĺ�����\r\n");
		//���Ҹ�վ�������·��
		Route* p = g_sMap.stations[nStation].routes;
		if (p == NULL) {
			//printf("��\n");
			str.append("��\r\n");
		}
		else {
			while (p != NULL) {
				//printf("%s\n", BUSES[p->bus][0]);
				str.append(BUSES[p->bus][0]);
				str.append("\r\n");
				p = p->next;
			}
		}

		//printf("%sʻ��Ĺ�����\n", name);
		str.append("��");
		str.append(name);
		str.append("ʻ��Ĺ�����\r\n");
		int flag = 0;
		//��������վ�㣬ͨ��վ�����в���ʻ��Ĺ�����
		for (int i = 0; i < g_sMap.station_num; ++i) {
			Route* pin = g_sMap.stations[i].routes;
			while (pin != NULL) {
				if (pin->station == nStation) {
					//printf("%s\n", BUSES[g_sMap.stations[i].routes->bus][0]);
					str.append(BUSES[g_sMap.stations[i].routes->bus][0]);
					str.append("\r\n");
					flag = 1;
				}
				pin = pin->next;
			}
		}
		if (!flag) {
			//printf("��\n");
			str.append("��\r\n");
		}
	}
}

//ͨ�����������Ʋ��ҹ��������������ҽ��������str��������
void Map::QueryBus(BusMap g_sMap, char* name, string& str) {
	//���ҹ��������
	int nBus = FindBus(g_sMap, name);

	//û���ҵ�
	if (nBus == None) {
		str.append("û��");
		str.append(name);
		str.append("������\r\n");
		//printf("û��%s������\n", name);
	}
	else {
		//��¼�������������յ�
		int start = g_sMap.buses[nBus].start;
		int end = g_sMap.buses[nBus].end;
		//printf("%s������:%s->%s\n", name, STATIONS[start], STATIONS[end]);
		str.append(name);
		str.append("������:");
		str.append(STATIONS[start]);
		str.append("->");
		str.append(STATIONS[end]);
		str.append("\r\n");
		//���ݹ�������Ų��䣬��������
		while (start != end) {
			//printf("%s->", STATIONS[start]);
			str.append(STATIONS[start]);
			str.append("->");
			Route* p = g_sMap.stations[start].routes;
			while (p != NULL && p->bus != nBus) {
				p = p->next;
			}
			if (p != NULL) {
				start = p->station;
			}
		}
		//printf("%s\n", STATIONS[end]);
		str.append(STATIONS[end]);
		str.append("\r\n");
	}
}

//������бߵı������
void Map::ClearVisited(BusMap& g_sMap) {
	//�����������������Һۼ�
	for (int i = 0; i < g_sMap.station_num; ++i) {
		Route* p = g_sMap.stations[i].routes;
		while (p != NULL) {
			p->visited = false;
			p = p->next;
		}
	}
}

//(char*����)�ڵ�ͼ��ͨ�����Ʋ�������վ��֮���Ƿ����·��
int Map::HasPath(BusMap g_sMap, char* pStart, char* pEnd) {
	int start = FindStation(g_sMap, pStart);
	int end = FindStation(g_sMap, pEnd);
	if (start == -1 || end == -1) {
		return None;
	}
	return HasPath(g_sMap, start, end);
}

//(int����)�ڵ�ͼ��ͨ����Ų�������վ�����Ƿ����·��
bool Map::HasPath(BusMap g_sMap, int start, int end) {
	bool* visited = (bool*)malloc(sizeof(bool) * g_sMap.station_num);
	for (int i = 0; i < g_sMap.station_num; ++i) {
		visited[i] = false;
	}

	//�������������·��
	stack<int> s;
	s.push(start);
	while (!s.empty()) {
		int n = s.top();
		s.pop();
		if (n == end) {
			return true;
		}
		if (!visited[n]) {
			visited[n] = true;
			Route* p = g_sMap.stations[n].routes;
			for (p; p != NULL; p = p->next) {
				if (!visited[p->station]) {
					s.push(p->station);
				}
			}
		}
	}
	return false;
}

//(int����)�ڵ�ͼ��ͨ��վ����Ų�������վ��֮���Ƿ����ͨ��bus��·��
bool Map::HasPath(BusMap g_sMap, int start, int end, int bus) {
	//�Ȳ��Ҵӿ�ʼ��㣬�����������busʻ��
	Route* p = g_sMap.stations[start].routes;
	int flag = 0;
	for (p; p != NULL; p = p->next) {
		if (p->bus == bus) {
			flag = 1;
			break;
		}
	}
	if (!flag) {
		return false;
	}

	//��ȡʻ���ĵ�һ����
	p = g_sMap.stations[start].routes;
	while (p != NULL) {
		//ֻ����bus·��
		if (p->bus == bus) {
			//�������յ�����ҳɹ�
			if (p->station == end) {
				return true;
			}
			else {
				p = g_sMap.stations[p->station].routes;
			}
		}
		else {
			p = p->next;
		}
	}
	return false;
}

//���ظ�վ�����еĹ�����
int Map::Busnum(BusMap g_sMap, int start) {
	int busnum = 0;
	Route* p = g_sMap.stations[start].routes;
	//��ȱ���
	while (p != NULL) {
		p = p->next;
		++busnum;
	}
	return busnum;
}

//ͨ��վ���ţ���������վ��֮���·�������ת��һ�Σ�����������浽paths��
int Map::QueryRoute(BusMap g_sMap, int start, int end, Path** paths) {
	int path_num = 0;
	if (!HasPath(g_sMap, start, end)) {
		//printf("%s->%s:������·������\n", STATIONS[start], STATIONS[end]);
		return 0;
	}
	else {
		int bus_num = Busnum(g_sMap, start);	//��ȡͨ����ʼ���Ĺ�������
		int* bus = (int*)malloc(sizeof(int) * bus_num);	//��¼���������
		Route* p;
		p = g_sMap.stations[start].routes;
		int index = 0;
		while (p != NULL) {	//����������Ŵ���bus����
			bus[index] = p->bus;
			++index;
			p = p->next;
		}
		if (index != bus_num) {
			printf("û�м�����ȫ\n");
		}

		//����������������ʼ������Ĺ�����
		for (int i = 0; i < bus_num; ++i) {
			ClearVisited(g_sMap);
			//��ͨ�����������������վ����ջ
			bool* visited = (bool*)malloc(sizeof(bool) * g_sMap.station_num);
			for (int i = 0; i < g_sMap.station_num; ++i) {
				visited[i] = false;
			}
			stack<int> s;
			s.push(start);
			visited[start] = true;
			p = g_sMap.stations[start].routes;
			while (p != NULL) {
				if (p->bus == bus[i]) {
					s.push(p->station);
					visited[p->station] = true;
					p->visited = true;
					p = g_sMap.stations[p->station].routes;
				}
				else {
					p = p->next;
				}
			}

			//��ջ����ȡվ�㣬�������һ�ε�ת��·��
			while (!s.empty()) {
				int n = s.top();
				p = g_sMap.stations[n].routes;
				while (p != NULL) {
					//����·���ɵ���
					if (HasPath(g_sMap, n, end, p->bus)) {
						//��������������˳�
						if (p->bus == bus[i] || p->visited == true) {
							p = p->next;
							continue;
						}
						//printf("n = %d\n", n);
						//��ȡ��ʱ·��
						Route* ptmp = p;
						//��������վ��
						stack<int> stmp = s;
						while (ptmp != NULL) {
							int flag = 0;
							if (ptmp->bus == p->bus) {
								stmp.push(ptmp->station);
								visited[ptmp->station] = true;
								ptmp->visited = true;
								if (ptmp->station == end) {
									//��ջ�����ݴ���paths
									stack<int> stmp2;
									//��ջ����
									while (!stmp.empty()) {
										stmp2.push(stmp.top());
										stmp.pop();
									}
									//printf("��%d��·\n", path_num + 1);
									int t = 0;
									int length = 0;
									//���ν���������paths
									while (!stmp2.empty()) {
										if (paths[path_num] == NULL) {
											//printf("�ڴ����ʧ��\n");
											break;
										}
										if (t == 0) {
											if (stmp2.top() == n) {
												paths[path_num][length].bus = p->bus;
												//printf("bus : %d ", p->bus);
												t = 1;
											}
											if (t == 0) {
												paths[path_num][length].bus = bus[i];
												//printf("bus : %d ", bus[i]);
											}
										}
										else {
											paths[path_num][length].bus = p->bus;
											//printf("bus : %d ", p->bus);
										}
										paths[path_num][length].station = stmp2.top();
										//printf("%d\n", stmp2.top());
										stmp2.pop();
										++length;
									}
									//��paths�ĳ��ȱ���
									for (int i = 0; i < length; ++i) {
										paths[path_num][i].station_num = length;
									}
									flag = 1;
								}
								else {
									ptmp = g_sMap.stations[ptmp->station].routes;
								}
							}
							else {
								ptmp = ptmp->next;
							}
							if (flag) {
								break;
							}
						}

						++path_num;
					}
					p = p->next;
				}
				s.pop();
			}
		}
	}
	return path_num;
}

//ͨ��վ�����ƣ���������վ��֮���·�������ת��һ�Σ�����������浽paths��
int Map::QueryRoute(BusMap g_sMap, char* start, char* end, Path** paths) {
	int s = FindStation(g_sMap, start);
	int e = FindStation(g_sMap, end);
	return Map::QueryRoute(g_sMap, s, e, paths);
}

//�����ҳ�����·��������ʽ���浽str��
void Map::QueryRoute(BusMap g_sMap, char* start, char* end, string& str) {
	Path** paths = (Path**)malloc(sizeof(Path*) * Map::MaxPath);
	for (int i = 0; i < Map::MaxPath; ++i) {
		paths[i] = (Path*)malloc(sizeof(Path) * Map::MaxLength);
	}

	//���ҿɵ���·������
	int path_num = QueryRoute(g_sMap, start, end, paths);
	//������·��
	if (path_num == 0) {
		str.append("������·������\r\n");
	}
	//����·���������ݰ���ʽ�����str
	for (int i = 0; i < path_num; ++i) {
		str.append("��");
		str += to_string(i + 1);
		str.append("��·\r\n");
		int bus = paths[i][0].bus;
		int num = 1;
		int end = 0;
		str.append(Map::g_sMap.buses[paths[i][0].bus].name);
		str.append(":");
		str.append(Map::g_sMap.stations[paths[i][0].station].station);
		for (int j = 1; j < paths[i][0].station_num; ++j) {
			if (paths[i][paths[i][0].station_num - 1].bus == bus) {
				str.append("->");
				str.append(Map::g_sMap.stations[paths[i][j].station].station);
			}
			else {
				str.append("->");
				str.append(Map::g_sMap.stations[paths[i][j].station].station);
				if (paths[i][j].bus != bus && num == 1) {
					str.append("\r\n");
					++num;
				}
				if (num == 2) {
					str.append(Map::g_sMap.buses[paths[i][j].bus].name);
					str.append(":");
					str.append(Map::g_sMap.stations[paths[i][j].station].station);
					++num;
				}

			}
		}
		str.append("\r\n");
	}
}

//����0����ɹ�,���ļ���ɾ��վ����Ϣ
int Map::DeleteStation(const char* FILENAME, char* station) {
	//�򿪶�Ӧ�ļ�
	fstream file(FILENAME);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string name;
		//���λ�ȡ����
		while (getline(file, name)) {
			if (strcmp(name.c_str(), station) == 0) {
				flag = 0;
				continue;
			}
			ofile << name << endl;
		}
		file.close();
		ofile.close();
		remove(FILENAME);
		rewind(stdin);

		//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
		fstream file1(Map::filename);
		ofstream ofile1(FILENAME);
		if (file1.is_open() && ofile1.is_open()) {
			while (getline(file1, name)) {
				ofile1 << name << endl;
			}
			file1.close();
			ofile1.close();
			rewind(stdin);
			remove(Map::filename);
		}
	}
	return flag;
}

//���ļ������վ����Ϣ
int Map::AddStation(const char* FILENAME, char* station) {
	fstream file(FILENAME, ios::app);
	file << station << endl;
	return 0;
}

//���ļ��и���վ����Ϣ
int Map::UpdateStation(const char* FILENAME, char* oldname, char* newname) {
	fstream file(FILENAME);
	ofstream ofile(Map::filename);

	int flag = -1;
	string name;
	//���λ�ȡ����
	while (getline(file, name)) {
		if (strcmp(oldname, name.c_str()) == 0) {
			ofile << newname << endl;
			flag = 0;
			continue;
		}
		ofile << name << endl;
	}
	file.close();
	ofile.close();
	remove(FILENAME);
	rewind(stdin);

	//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
	fstream file1(Map::filename);
	ofstream ofile1(FILENAME);
	while (getline(file1, name)) {
		ofile1 << name << endl;
	}
	file1.close();
	ofile1.close();
	rewind(stdin);
	remove(Map::filename);
	return flag;
}

//���ļ���ɾ��·����Ϣ
int Map::DeleteRoute(const char* FILENAME, int bus, int start, int end, int meter) {
	FILE* file = fopen(FILENAME, "r");
	FILE* ofile = fopen(Map::filename, "w+");

	int flag = -1;
	int b, s, e, m;
	//���λ�ȡ����
	while (fscanf(file, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		if (b == bus && s == start && e == end && m == meter) {
			flag = 0;
			continue;
		}
		fprintf(ofile, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file);
	fclose(ofile);

	remove(FILENAME);
	rewind(stdin);

	FILE* ofile1 = fopen(FILENAME, "w+");
	FILE* file1 = fopen(Map::filename, "r");

	//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
	while (fscanf(file1, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		fprintf(ofile1, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file1);
	fclose(ofile1);
	rewind(stdin);
	remove(Map::filename);
	return flag;
}

//���ļ������·����Ϣ
int Map::AddRoute(const char* FILENAME, int bus, int start, int end, int meter) {
	//FILE* file = fopen(FILENAME, "a+");
	//fprintf(file, "%d\t%d\t%d\t%d\n", bus, start, end, meter);
	//return 0;

	fstream file(FILENAME, ios::app);
	file << bus << "\t" << start << "\t" << end << "\t" << meter << endl;
	return 0;
}

//���ļ��и���·����Ϣ
int Map::UpdateRoute(const char* FILENAME, int oldbus, int oldstart, int oldend, int oldmeter, int newbus, int newstart, int newend, int newmeter) {
	FILE* file = fopen(FILENAME, "r");
	FILE* ofile = fopen(Map::filename, "w+");

	int b, s, e, m;
	int flag = -1;
	//���λ�ȡ����
	while (fscanf(file, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		if (b == oldbus && s == oldstart && e == oldend && m == oldmeter) {
			fprintf(ofile, "%d\t%d\t%d\t%d\n", newbus, newstart, newend, newmeter);
			flag = 0;
			continue;
		}
		fprintf(ofile, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file);
	fclose(ofile);

	remove(FILENAME);
	rewind(stdin);

	FILE* ofile1 = fopen(FILENAME, "w+");
	FILE* file1 = fopen(Map::filename, "r");

	//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
	while (fscanf(file1, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		fprintf(ofile1, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file1);
	fclose(ofile1);
	rewind(stdin);
	remove(Map::filename);
	return flag;
}

//���ļ���ɾ����������Ϣ
int Map::DeleteBuses(const char* f, char* bus) {
	fstream file(f);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string name;
		//���λ�ȡ����
		while (getline(file, name)) {
			if (strcmp(name.c_str(), bus) == 0) {
				getline(file, name);
				getline(file, name);
				flag = 0;
				continue;
			}
			ofile << name << endl;
		}
		file.close();
		ofile.close();
		remove(f);
		rewind(stdin);

		//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
		fstream file1(Map::filename);
		ofstream ofile1(f);
		if (file1.is_open() && ofile1.is_open()) {
			while (getline(file1, name)) {
				ofile1 << name << endl;
			}
			file1.close();
			ofile1.close();
			rewind(stdin);
			remove(Map::filename);
		}
	}
	return flag;
}

//���ļ��и��¹�������Ϣ
int Map::UpdateBuses(const char* f, char* bus, char* start, char* end, char* nbus, char* nstart, char* nend) {
	fstream file(f);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string t1, t2, t3;
		//���λ�ȡ����
		while (getline(file, t1)) {
			if (strcmp(t1.c_str(), bus) == 0) {
				getline(file, t2);
				if (strcmp(t2.c_str(), start) == 0) {
					getline(file, t3);
					if (strcmp(t3.c_str(), end) == 0) {
						ofile << nbus << endl;
						ofile << nstart << endl;
						ofile << nend << endl;
						flag = 0;
						continue;
					}
					else {
						ofile << t1 << endl;
						ofile << t2 << endl;
						ofile << t3 << endl;
					}
				}
				else {
					ofile << t1 << endl;
					ofile << t2 << endl;
				}
			}
			else {
				ofile << t1 << endl;
			}
		}
		file.close();
		ofile.close();
		remove(f);
		rewind(stdin);

		//����ʱ�ļ�ɾ�������ݴ���ԭ���ļ�
		fstream file1(Map::filename);
		ofstream ofile1(f);
		string name;
		if (file1.is_open() && ofile1.is_open()) {
			while (getline(file1, name)) {
				ofile1 << name << endl;
			}
			file1.close();
			ofile1.close();
			rewind(stdin);
			remove(Map::filename);
		}
	}
	return flag;
}

//���ļ�����ӹ�������Ϣ
int Map::AddBuses(const char* FILENAME, char* bus, char* start, char* end) {
	fstream file(FILENAME, ios::app);
	file << bus << endl;
	file << start << endl;
	file << end << endl;
	return 0;
}