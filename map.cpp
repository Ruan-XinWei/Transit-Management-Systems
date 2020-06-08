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

//获取ROUTE_NUM、BUS_NUM、STATION_NUM
void Map::Init() {
	//获取路径数量
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

	//获取公交车数量
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

	//获取站点数量
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

//给ROUTES、BUSES、STATIONS申请空间、填数据
void Map::InitData() {
	Init();

	//ROUTES申请空间
	ROUTES = (int**)malloc(ROUTE_NUM * sizeof(int*));
	for (int i = 0; i < ROUTE_NUM; ++i) {
		ROUTES[i] = (int*)malloc(4 * sizeof(int));
	}

	//BUSES申请空间
	BUSES = (char***)malloc(BUS_NUM * sizeof(char**));
	for (int i = 0; i < BUS_NUM; ++i) {
		BUSES[i] = (char**)malloc(3 * sizeof(char*));
	}
	for (int i = 0; i < BUS_NUM; ++i) {
		for (int j = 0; j < 3; ++j) {
			BUSES[i][j] = (char*)malloc(MaxName * sizeof(char));
		}
	}

	//STATIONS申请空间
	STATIONS = (char**)malloc(STATION_NUM * sizeof(char*));
	for (int i = 0; i < STATION_NUM; ++i) {
		STATIONS[i] = (char*)malloc(MaxName * sizeof(char));
	}

	//ROUTES填数据
	FILE* file = fopen(Map::ROUTESFILE, "r");

	int d;
	for (int i = 0; i < ROUTE_NUM; ++i) {
		for (int j = 0; j < 4; ++j) {
			fscanf(file, "%d", &d);
			ROUTES[i][j] = d;
		}
	}

	//BUSES填数据
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

	//STATIONS填数据
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

	//将数据存入g_sMap中
	LoadMapDate(g_sMap);
}

//将数据加载到g_sMap中
void Map::LoadMapDate(BusMap& g_sMap) {
	//存入公交车名称
	g_sMap.bus_num = BUS_NUM;
	g_sMap.buses = (Bus*)malloc(sizeof(Bus) * BUS_NUM);
	for (int i = 0; i < BUS_NUM; ++i) {
		g_sMap.buses[i].name = BUSES[i][0];
		g_sMap.buses[i].start = g_sMap.buses[i].end = None;
	}

	//存入站点名称
	g_sMap.station_num = STATION_NUM;
	g_sMap.stations = (Station*)malloc(sizeof(Station) * STATION_NUM);
	for (int i = 0; i < STATION_NUM; ++i) {
		g_sMap.stations[i].station = STATIONS[i];
		g_sMap.stations[i].routes = NULL;
	}

	//存入公交车起点和终点
	for (int i = 0; i < g_sMap.bus_num; ++i) {
		g_sMap.buses[i].start = FindStation(g_sMap, BUSES[i][1]);
		g_sMap.buses[i].end = FindStation(g_sMap, BUSES[i][2]);
	}

	//存入路径
	for (int i = 0; i < ROUTE_NUM; ++i) {
		//路径新节点
		Route* pnew = (Route*)malloc(sizeof(Route));
		if (pnew != NULL) {
			pnew->bus = ROUTES[i][0];
			pnew->station = ROUTES[i][2];
			pnew->distance = ROUTES[i][3];
			pnew->next = NULL;
		}

		//将新节点接入
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

//通过公交车名称查找公交车编号
int Map::FindBus(BusMap g_sMap, char* bus) {
	for (int i = 0; i < g_sMap.bus_num; ++i) {
		if (strcmp(g_sMap.buses[i].name, bus) == 0) {
			return i;
		}
	}
	return None;
}

//通过站点名称查找站点编号
int Map::FindStation(BusMap g_sMap, char* station) {
	for (int i = 0; i < g_sMap.station_num; ++i) {
		if (strcmp(g_sMap.stations[i].station, station) == 0) {
			return i;
		}
	}
	return None;
}

//通过站点名称查找站点，并将查找结果保存到str里，便于输出
void Map::Querystation(BusMap g_sMap, char* name, string& str) {
	int nStation = FindStation(g_sMap, name);
	//站点没有搜索到
	if (nStation == None) {
		//printf("没有该站点\n");
		str.append("没有该站点\r\n");
	}
	else {
		//printf("从%s驶出的公交车\n", name);
		str.append("从");
		str.append(name);
		str.append("驶出的公交车\r\n");
		//查找该站点的下行路线
		Route* p = g_sMap.stations[nStation].routes;
		if (p == NULL) {
			//printf("无\n");
			str.append("无\r\n");
		}
		else {
			while (p != NULL) {
				//printf("%s\n", BUSES[p->bus][0]);
				str.append(BUSES[p->bus][0]);
				str.append("\r\n");
				p = p->next;
			}
		}

		//printf("%s驶入的公交车\n", name);
		str.append("从");
		str.append(name);
		str.append("驶入的公交车\r\n");
		int flag = 0;
		//遍历所有站点，通过站点下行查找驶入的公交车
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
			//printf("无\n");
			str.append("无\r\n");
		}
	}
}

//通过公交车名称查找公交车，并将查找结果保存在str里，便于输出
void Map::QueryBus(BusMap g_sMap, char* name, string& str) {
	//查找公交车编号
	int nBus = FindBus(g_sMap, name);

	//没有找到
	if (nBus == None) {
		str.append("没有");
		str.append(name);
		str.append("公交车\r\n");
		//printf("没有%s公交车\n", name);
	}
	else {
		//记录公交车的起点和终点
		int start = g_sMap.buses[nBus].start;
		int end = g_sMap.buses[nBus].end;
		//printf("%s公交车:%s->%s\n", name, STATIONS[start], STATIONS[end]);
		str.append(name);
		str.append("公交车:");
		str.append(STATIONS[start]);
		str.append("->");
		str.append(STATIONS[end]);
		str.append("\r\n");
		//依据公交车编号不变，进行搜索
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

//清除所有边的遍历情况
void Map::ClearVisited(BusMap& g_sMap) {
	//广度搜索将边清除查找痕迹
	for (int i = 0; i < g_sMap.station_num; ++i) {
		Route* p = g_sMap.stations[i].routes;
		while (p != NULL) {
			p->visited = false;
			p = p->next;
		}
	}
}

//(char*类型)在地图中通过名称查找两个站点之间是否存在路径
int Map::HasPath(BusMap g_sMap, char* pStart, char* pEnd) {
	int start = FindStation(g_sMap, pStart);
	int end = FindStation(g_sMap, pEnd);
	if (start == -1 || end == -1) {
		return None;
	}
	return HasPath(g_sMap, start, end);
}

//(int类型)在地图中通过序号查找两个站点中是否存在路径
bool Map::HasPath(BusMap g_sMap, int start, int end) {
	bool* visited = (bool*)malloc(sizeof(bool) * g_sMap.station_num);
	for (int i = 0; i < g_sMap.station_num; ++i) {
		visited[i] = false;
	}

	//深度搜索，查找路径
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

//(int类型)在地图中通过站点序号查找两个站点之间是否存在通过bus的路径
bool Map::HasPath(BusMap g_sMap, int start, int end, int bus) {
	//先查找从开始起点，广度搜索有无bus驶出
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

	//获取驶出的第一条边
	p = g_sMap.stations[start].routes;
	while (p != NULL) {
		//只查找bus路线
		if (p->bus == bus) {
			//若到达终点则查找成功
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

//返回该站点下行的公交数
int Map::Busnum(BusMap g_sMap, int start) {
	int busnum = 0;
	Route* p = g_sMap.stations[start].routes;
	//广度遍历
	while (p != NULL) {
		p = p->next;
		++busnum;
	}
	return busnum;
}

//通过站点编号，查找两个站点之间的路径，最多转车一次，并将结果保存到paths中
int Map::QueryRoute(BusMap g_sMap, int start, int end, Path** paths) {
	int path_num = 0;
	if (!HasPath(g_sMap, start, end)) {
		//printf("%s->%s:不存在路径到达\n", STATIONS[start], STATIONS[end]);
		return 0;
	}
	else {
		int bus_num = Busnum(g_sMap, start);	//获取通过开始结点的公交车数
		int* bus = (int*)malloc(sizeof(int) * bus_num);	//记录公交车序号
		Route* p;
		p = g_sMap.stations[start].routes;
		int index = 0;
		while (p != NULL) {	//将公交车编号存入bus数组
			bus[index] = p->bus;
			++index;
			p = p->next;
		}
		if (index != bus_num) {
			printf("没有加载完全\n");
		}

		//依次搜索各个从起始点出发的公交车
		for (int i = 0; i < bus_num; ++i) {
			ClearVisited(g_sMap);
			//将通过公交车到达的所有站点入栈
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

			//从栈顶获取站点，查找最多一次的转车路径
			while (!s.empty()) {
				int n = s.top();
				p = g_sMap.stations[n].routes;
				while (p != NULL) {
					//存在路径可到达
					if (HasPath(g_sMap, n, end, p->bus)) {
						//如果搜索过，则退出
						if (p->bus == bus[i] || p->visited == true) {
							p = p->next;
							continue;
						}
						//printf("n = %d\n", n);
						//获取此时路径
						Route* ptmp = p;
						//保存所有站点
						stack<int> stmp = s;
						while (ptmp != NULL) {
							int flag = 0;
							if (ptmp->bus == p->bus) {
								stmp.push(ptmp->station);
								visited[ptmp->station] = true;
								ptmp->visited = true;
								if (ptmp->station == end) {
									//将栈中数据存入paths
									stack<int> stmp2;
									//将栈逆置
									while (!stmp.empty()) {
										stmp2.push(stmp.top());
										stmp.pop();
									}
									//printf("第%d条路\n", path_num + 1);
									int t = 0;
									int length = 0;
									//依次将数据填入paths
									while (!stmp2.empty()) {
										if (paths[path_num] == NULL) {
											//printf("内存分配失败\n");
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
									//将paths的长度保存
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

//通过站点名称，查找两个站点之间的路径，最多转车一次，并将结果保存到paths中
int Map::QueryRoute(BusMap g_sMap, char* start, char* end, Path** paths) {
	int s = FindStation(g_sMap, start);
	int e = FindStation(g_sMap, end);
	return Map::QueryRoute(g_sMap, s, e, paths);
}

//将查找出来的路径，按格式保存到str中
void Map::QueryRoute(BusMap g_sMap, char* start, char* end, string& str) {
	Path** paths = (Path**)malloc(sizeof(Path*) * Map::MaxPath);
	for (int i = 0; i < Map::MaxPath; ++i) {
		paths[i] = (Path*)malloc(sizeof(Path) * Map::MaxLength);
	}

	//查找可到达路径数量
	int path_num = QueryRoute(g_sMap, start, end, paths);
	//不存在路径
	if (path_num == 0) {
		str.append("不存在路径到达\r\n");
	}
	//存在路径，将数据按格式保存进str
	for (int i = 0; i < path_num; ++i) {
		str.append("第");
		str += to_string(i + 1);
		str.append("条路\r\n");
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

//返回0代表成功,在文件中删除站点信息
int Map::DeleteStation(const char* FILENAME, char* station) {
	//打开对应文件
	fstream file(FILENAME);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string name;
		//依次获取数据
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

		//将临时文件删除，数据存入原来文件
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

//在文件中添加站点信息
int Map::AddStation(const char* FILENAME, char* station) {
	fstream file(FILENAME, ios::app);
	file << station << endl;
	return 0;
}

//在文件中更新站点信息
int Map::UpdateStation(const char* FILENAME, char* oldname, char* newname) {
	fstream file(FILENAME);
	ofstream ofile(Map::filename);

	int flag = -1;
	string name;
	//依次获取数据
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

	//将临时文件删除，数据存入原来文件
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

//在文件中删除路径信息
int Map::DeleteRoute(const char* FILENAME, int bus, int start, int end, int meter) {
	FILE* file = fopen(FILENAME, "r");
	FILE* ofile = fopen(Map::filename, "w+");

	int flag = -1;
	int b, s, e, m;
	//依次获取数据
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

	//将临时文件删除，数据存入原来文件
	while (fscanf(file1, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		fprintf(ofile1, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file1);
	fclose(ofile1);
	rewind(stdin);
	remove(Map::filename);
	return flag;
}

//在文件中添加路径信息
int Map::AddRoute(const char* FILENAME, int bus, int start, int end, int meter) {
	//FILE* file = fopen(FILENAME, "a+");
	//fprintf(file, "%d\t%d\t%d\t%d\n", bus, start, end, meter);
	//return 0;

	fstream file(FILENAME, ios::app);
	file << bus << "\t" << start << "\t" << end << "\t" << meter << endl;
	return 0;
}

//在文件中更新路径信息
int Map::UpdateRoute(const char* FILENAME, int oldbus, int oldstart, int oldend, int oldmeter, int newbus, int newstart, int newend, int newmeter) {
	FILE* file = fopen(FILENAME, "r");
	FILE* ofile = fopen(Map::filename, "w+");

	int b, s, e, m;
	int flag = -1;
	//依次获取数据
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

	//将临时文件删除，数据存入原来文件
	while (fscanf(file1, "%d%d%d%d", &b, &s, &e, &m) != EOF) {
		fprintf(ofile1, "%d\t%d\t%d\t%d\n", b, s, e, m);
	}
	fclose(file1);
	fclose(ofile1);
	rewind(stdin);
	remove(Map::filename);
	return flag;
}

//在文件中删除公交车信息
int Map::DeleteBuses(const char* f, char* bus) {
	fstream file(f);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string name;
		//依次获取数据
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

		//将临时文件删除，数据存入原来文件
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

//在文件中更新公交车信息
int Map::UpdateBuses(const char* f, char* bus, char* start, char* end, char* nbus, char* nstart, char* nend) {
	fstream file(f);
	ofstream ofile(Map::filename);
	int flag = -1;
	if (file.is_open() && ofile.is_open()) {
		string t1, t2, t3;
		//依次获取数据
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

		//将临时文件删除，数据存入原来文件
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

//在文件中添加公交车信息
int Map::AddBuses(const char* FILENAME, char* bus, char* start, char* end) {
	fstream file(FILENAME, ios::app);
	file << bus << endl;
	file << start << endl;
	file << end << endl;
	return 0;
}