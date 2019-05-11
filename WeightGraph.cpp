#include "WeightGraph.h"

void WeightGraph::addWeights(int x, int y, int weight)
{
	///对x和y都添加一个元素
	NodeList *rear = nullptr;
	NodeList *newNode1 = new NodeList(y, weight);
	NodeList *newNode2 = new NodeList(x, weight);
	if ( !hlist[x].head ) { hlist[x].head = newNode1; }
	else {
        for ( rear = hlist[x].head ; rear -> next ; rear = rear -> next ){}
        rear -> next = newNode1;
    }
    if ( !hlist[y].head ) { hlist[y].head = newNode2; }
    else {
        for ( rear = hlist[y].head ; rear -> next ; rear = rear -> next ){}
        rear -> next = newNode2;
    }
}

///返回一个指定起点所形成的的最短加权路径数组(向量)
std::vector<int> WeightGraph::dijkstra(int startLabel)
{
	///bool向量中元素的默认值为false
	std::vector<bool> visited(vertexSum);
	///保存路径结果的数组， 值初始化为0
	std::vector<int> pathWeight(vertexSum);
	///到自身的路径长度为0
	fill(pathWeight.begin(), pathWeight.end(), INT_MAX);
	pathWeight[startLabel] = 0;
	///在程序运行过程中维护一个优先级队列， 配合一个bool数组能够达到遍历目的
	std::priority_queue<int, std::vector<int>, std::greater<int>> pQueue;
	pQueue.push(startLabel);
	int baseLabel;
	///优先级队列为空时，算法终止
	while ( !pQueue.empty() )
	{
		///获取pivot主元
		baseLabel = pQueue.top();
		///删除该元素
		pQueue.pop();
		if ( visited[baseLabel] ) { continue; }
		for ( auto x = hlist[baseLabel].head ; x ; x = x -> next )
		{
			///如果还没有对该顶点进行访问，直接将其加入到队列中
			if ( !visited[x -> label] )
			{
				pQueue.push(x -> label);
			}
		}
			///算法核心部分
		for ( auto x = hlist[baseLabel].head ; x ; x = x -> next )
		{
			if ( pathWeight[x -> label] > pathWeight[baseLabel] + x -> weight )
			{
				pathWeight[x -> label] = pathWeight[baseLabel] + x -> weight;
			}
		}
		///修改访问标记
		visited[baseLabel] = true;
    }
    return pathWeight;
}

WeightGraph::WeightGraph(const WeightGraph &gr): vertexSum(gr.vertexSum), edgeSum(gr.edgeSum)
{
	///自赋值检测
	if ( this != &gr )
	{
		delete [] hlist;
		hlist = new HeadList[vertexSum];
	}
	NodeList *preview = nullptr;
	for ( int i = 0 ; i < vertexSum ; ++ i )
	{
		preview = hlist[i].head;
		for ( auto &x = gr.hlist[i].head ; x ; preview = x, x = x -> next )
		{
			NodeList *curNode = new NodeList(*x);
			preview -> next = curNode;
		}
	}
}

WeightGraph& WeightGraph::operator=(const WeightGraph &gr)
{
	vertexSum = gr.vertexSum;
	edgeSum   = gr.edgeSum;
	if ( this != &gr )
	{
		delete [] hlist;
		hlist = new HeadList[vertexSum];
	}
	NodeList *preview = nullptr;
	for ( int i = 0 ; i < vertexSum ; ++ i )
	{
		preview = hlist[i].head;
		for ( auto &x = hlist[i].head ; x ; preview = x, x = x -> next )
		{
			NodeList *curNode = new NodeList(*x);
			preview -> next = curNode;
		}
	}
	return *this;
}

WeightGraph::~WeightGraph()
{
    for ( int i = 0 ; i < vertexSum ; ++ i )
    {
        delete [] hlist[i].head;
    }
	delete [] hlist;
}
