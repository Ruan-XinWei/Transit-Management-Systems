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

	//路径数量
	int ROUTE_NUM = -1;
	//公交车数量
	int BUS_NUM = -1;
	//站点数量
	int STATION_NUM = -1;
	//最多查询路径数量
	int MaxPath = 5;
	//每条路径最大长度
	int MaxLength = 20;
	//最长名称
	int MaxName = 100;

	//路径数组，用来将读取出来的路径数据存入
	int** ROUTES;
	//公交车数组，用来将读取出来的公交车数据存入
	char*** BUSES;
	//站点数组，用来将读取出来的站点数据存入
	char** STATIONS;

	//文件中转名
	const char* filename = "./tmptmptmp.txt";
	//BUSES文件位置
	const char* BUSESFILE = "./BUSES.txt";
	//ROUTES文件位置
	const char* ROUTESFILE = "./ROUTES.txt";
	//STATIONS文件位置
	const char* STATIONFILE = "./STATIONS.txt";

	//保存全图数据
	BusMap g_sMap;

	Map();
	~Map();

	//获取ROUTE_NUM、BUS_NUM、STATION_NUM
	void Init();

	//给ROUTES、BUSES、STATIONS申请空间、填数据
	void InitData();

	//将数据加载到g_sMap中
	void LoadMapDate(BusMap& g_sMap);

	//通过公交车名称查找公交车编号
	int FindBus(BusMap g_sMap, char* bus);

	//通过站点名称查找站点编号
	int FindStation(BusMap g_sMap, char* station);

	//通过站点名称查找站点，并将查找结果保存到str里，便于输出
	void Querystation(BusMap g_sMap, char* name, string& str);

	//通过公交车名称查找公交车，并将查找结果保存在str里，便于输出
	void QueryBus(BusMap g_sMap, char* name, string& str);

	//清除所有边的遍历情况
	void ClearVisited(BusMap& g_sMap);

	//通过名称，查找两个站点之间是否存在路径
	int HasPath(BusMap g_sMap, char* pStart, char* pEnd);

	//通过站点编号，查找两个站点之间是否存在路径
	bool HasPath(BusMap g_sMap, int start, int end);

	//(int类型)在地图中通过站点序号查找两个站点之间是否存在通过bus的路径
	bool HasPath(BusMap g_sMap, int start, int end, int bus);

	//返回该站点下行的公交数
	int Busnum(BusMap g_sMap, int start);

	//通过站点名称，查找两个站点之间的路径，最多转车一次，并将结果保存到paths中
	int QueryRoute(BusMap g_sMap, char* start, char* end, Path** paths);

	//通过站点编号，查找两个站点之间的路径，最多转车一次，并将结果保存到paths中
	int QueryRoute(BusMap g_sMap, int start, int end, Path** paths);

	//将查找出来的路径，按格式保存到str中
	void QueryRoute(BusMap g_sMap, char* start, char* end, string& str);

	//在文件中删除站点信息
	int DeleteStation(const char* FILENAME, char* station);

	//在文件中添加站点信息
	int AddStation(const char* FILENAME, char* station);

	//在文件中更新站点信息
	int UpdateStation(const char* FILENAME, char* oldname, char* newname);

	//在文件中删除路径信息
	int DeleteRoute(const char* FILENAME, int bus, int start, int end, int meter);

	//在文件中添加路径信息
	int AddRoute(const char* FILENAME, int bus, int start, int end, int meter);

	//在文件中更新路径信息
	int UpdateRoute(const char* FILENAME, int oldbus, int oldstart, int oldend, int oldmeter, int newbus, int newstart, int newend, int newmeter);

	//在文件中删除公交车信息
	int DeleteBuses(const char* fliename, char* bus);

	//在文件中更新公交车信息
	int UpdateBuses(const char* f, char* bus, char* start, char* end, char* nbus, char* nstart, char* nend);

	//在文件中添加公交车信息
	int AddBuses(const char* FILENAME, char* bus, char* start, char* end);

};