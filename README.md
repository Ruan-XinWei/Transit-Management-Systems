# Transit-Management-Systems
## 数据格式

### ROUTES.txt

每一行记录路径信息，总共有四列，分别对应着公交车编号，起点编号，终点编号以及路段的长度
文件格式如下：  
公交车编号|起点编号|终点编号|路段长度  
![1.1](https://gitee.com/ruanxinwei/image/raw/master/image/1.1.png)

### BUSES.txt

每三行记录一个公交车信息  
第一行：公交车名称  
第二行：公交车起始站点  
第三行：公交车终止站点  
文件格式如下：  
![1.2](https://gitee.com/ruanxinwei/image/raw/master/image/1.2.png)

### STATIONS.txt

每一行记录一个站点名称，其位次为站点的编号+1  
文件格式如下：  
![1.3](https://gitee.com/ruanxinwei/image/raw/master/image/1.3.png)

## 整体算法描述

### 自然语言描述
#### 查询公交
1. 根据公交名查找公交的编号
2. 通过公交编号，确定公交的起点和终点
3. 再使用深度搜索方式，查找到对应公交车的线路信息

#### 查询站点
1. 确定站点的编号
2. 先将该站点的下行路线遍历，确定从该站点驶出的公交车
3. 对所有站点的下行路线进行查找，查看是否有下一站为该站点，如果是，这条线路的公交车则会驶入该站点

#### 查询线路
1. 先查询两个站点之间是否存在路径
   1. 将所有站点标志为未访问，起始站点存入栈中，起始站点标志为已访问
   2. 采用使用深度搜索的方式，取出栈顶站点搜索下一个站点，如果站点已访问，则将此忽略
   3. 直到找到终止站点，或全部站点都已访问都未能找到终止站点
2. 如果两个站点间存在路径，则查询路线，否则，将结果输出为“两站点间不存在路径”
   1. 通过搜索，先将起始站点的各个下行路线保存至数组中
   2. 对于每个下行路线，进行深度搜索，每次将能通过此路线的公交车到达的所有站点入栈，并将站点标志为已访问
   3. 每次取出栈顶站点，搜索通过此站点，能否通过最多一次换乘，而到达终止站点，如果能到达，则将该路线数据保存

#### 修改信息
因为文件修改类似，所以其修改方式也类似，主要将9种用于修改的函数分为三类，添加，删除和更新，而这三类修改的主要原理我使用的是通过副本来进行修改，以下为主要修改步骤

1. 创建一个副本
2. 扫描需要更新的文件，当遇到需要修改的地方，进行适当修改，同时把数据输入进副本中
3. 删除原文件，将副本重命名为原文件格式，删除副本

## 数据结构
1. 存储结构：邻接表

2. 主要操作：
   1. 读取文件数据，获取数量信息
   2. 依据数量分配内存空间
   3. 将数据加载到图中
3. 主要存储结构源代码如下：

```c++
//整个公交地图的信息
typedef struct BusMap
{
	Bus* buses;	//公交线路数组
	Station* stations;	//站点数组
	int station_num;	//站点数
	int bus_num;	//公交线路数
}BusMap;
```

## 查询信息
### 公交线路
1. 选择对应公交名
2. 点击确定后，文本框中立马显示数据
3. 查询公交线路运行结果
4. 程序运行结果截图
   ![4.1](https://gitee.com/ruanxinwei/image/raw/master/image/4.1.png)

### 站点信息
1. 选择对应站点名
2. 点击确定后，文本框中立马显示数据
3. 查询站点信息运行结果：
4. 程序运行结果截图
   ![4.2](https://gitee.com/ruanxinwei/image/raw/master/image/4.2.png)

## 查询路线

找到至多换乘1次的路线，并输出结果。

1. 选择起点和终点
2. 点击确定后，文本框中立马显示数据
3. 查询路线信息截图
   ![5](https://gitee.com/ruanxinwei/image/raw/master/image/5.png)

## 修改信息

修改公交车、公交线路和站点信息，保存文件（测试顺序为增加->更新->删除）

### 修改公交车信息
#### 增加公交车
1. 填写公交名、起点和终点在添加操作框中
2. 点击确定后，会弹出消息框显示添加操作是否成功
3. 增加公交车截图以及文件内截图
   ![6.1.1.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.1.1.png)
   ![6.1.1.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.1.2.png)

#### 删除公交车
1. 选择公交名
2. 点击确定后，会弹出消息框显示添加操作是否成功
3. 删除公交车截图以及文件内截图
   ![6.1.2.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.2.1.png)
   ![6.1.2.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.2.2.png)

#### 更新公交车
1. 填写原来的和想修改的公交名、起点和终点在操作框中
2. 点击确定后，会弹出消息框显示更新操作是否成功
3. 更新公交车截图以及文件内截图
   ![6.1.3.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.3.1.png)
   ![6.1.3.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.1.3.2.png)

### 修改公交线路信息
#### 增加公交线路
1. 填写路径对应数据
2. 点击确定后，会弹出消息框显示添加操作是否成功
3. 增加公交线路截图以及文件内截图
   ![6.2.1.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.1.1.png)
   ![6.2.1.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.1.2.png)

#### 删除公交线路
1. 填写需要删除路径对应数据
2. 点击确定后，会弹出消息框显示删除操作是否成功
3. 删除公交线路截图以及文件内截图
   ![6.2.2.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.2.1.png)
   ![6.2.2.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.2.2.png)

#### 更新公交线路
1. 填写需要更新的原路径和新路径数据
2. 点击确定后，会弹出消息框显示更新操作是否成功
3. 更新公交线路截图以及文件内截图
   ![6.2.3.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.3.1.png)
   ![6.2.3.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.2.3.2.png)

### 修改站点信息
#### 增加站点信息
1. 填写需要添加的站点名称
2. 点击确定后，会弹出消息框显示添加操作是否成功
3. 添加站点信息截图以及文件内截图
   ![6.3.1.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.1.1.png)
   ![6.3.1.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.1.2.png)

#### 删除站点信息
1. 选择需要删除的站点名称
2. 点击确定后，会弹出消息框显示删除操作是否成功
3. 删除站点信息截图以及文件内截图
   ![6.3.2.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.2.1.png)
   ![6.3.2.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.2.2.png)

#### 更新站点信息
1. 选择需要更新的站点名称，填写新站点名称
2. 点击确定后，会弹出消息框显示更新操作是否成功
3. 更新站点信息截图以及文件内截图
   ![6.3.3.1](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.3.1.png)
   ![6.3.3.2](https://gitee.com/ruanxinwei/image/raw/master/image/6.3.3.2.png)

## 流程图
### 总流程图

![7.1](https://gitee.com/ruanxinwei/image/raw/master/image/7.1.png)

### 查询路径流程图

![7.2](https://gitee.com/ruanxinwei/image/raw/master/image/7.2.png)

## 设计总结
&nbsp;&nbsp;这次的数据结构课程设计，是我第一次使用MFC构造公交线路图的图形化界面，虽然在实现过程中遇到了很多坎坷，但是在摸索中不断学习，不断进步，同时掌握了很多关于构建图形化界面的知识。在使用一些控件的时候，从不了解到掌握，慢慢地学会之间的一些函数，然后用这些函数去实现一些自己想要实现的功能，这真的是种很开心的事情。    
&nbsp;&nbsp;同时，这次的主要使用的数据结构是图，然后也算重新复习了上学期《数据结构》中学习到的图的知识，利用其中的一些算法，去完成本次课程设计，让自己的程序尽可能地完美，不出现太多的漏洞。   
&nbsp;&nbsp;然后，这次也要求使用文件读写功能，让程序和数据分割开来。虽然文件读写在大一就已经学过了，但是在这次课程设计之后，我发现其中还是有很多自己不懂的部分，也通过这次课程设计系统地学习了文件读写功能，也争取在下次想要实现一些系统的时候，也能将这种思想很好地利用。