#pragma once
#include<stdio.h>

//公交车线路
typedef struct Bus
{
	char* name;	//公交名
	int start;
	int end;
}Bus;

//表示站点信息
typedef struct Station
{
	char* station;	//站点名
	struct Route* routes;	//从该站点出发的所有下行路线的链域
}Station;

//表示公交线路中的一个路段
typedef struct Route
{
	int station;	//指向的站点索引号
	int bus;	//公交索引号
	int distance;	//两站之间公路的距离
	bool visited;	//遍历时的标识符
	struct Route* next;	//起始站点相同的，下一条下行路线
}Route;

//整个公交地图的信息
typedef struct BusMap
{
	Bus* buses;	//公交线路数组
	Station* stations;	//站点数组
	int station_num;	//站点数
	int bus_num;	//公交线路数
}BusMap;

typedef struct Path {
	int station_num;	//路径中的站点数
	int station;	//路径经过的站点编号
	int bus;	//通过站点的公交车编号
}Path;