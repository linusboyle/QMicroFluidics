 /**************************************************************************
***
*** Copyright (c) 2018 Regents of the Tsinghua University,
***               Hailong Yao, and Weiqing Ji
***
***  Contact author(s): jwq18@mails.tinghua.edu.cn, hailongyao@mail.tsinghua.edu.cn
***  Original Affiliation:   EDA Lab., Department of Computer Science and Technology, Tsinghua University.
***
***  Permission is hereby granted, free of charge, to any person obtaining
***  a copy of this software and associated documentation files (the
***  "Software"), to deal in the Software without restriction, including
***  without limitation
***  the rights to use, copy, modify, merge, publish, distribute, sublicense,
***  and/or sell copies of the Software, and to permit persons to whom the
***  Software is furnished to do so, subject to the following conditions:
***
***  The above copyright notice and this permission notice shall be included
***  in all copies or substantial portions of the Software.
***
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
*** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
*** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
*** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
*** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***
***
***************************************************************************/

#include <cmath>
#include <tuple>
#include <vector>
#include <QVector>

#define NAX 0.000000001

#define max_size 200

struct edge
{
    qreal velocity; //流速
    qreal length; //管道长度
    int sourceNode,destNode; //边所连接的两个节点，默认从n1流向n2
}edges[max_size];

struct node
{          
    std::vector<int> edgeList;  //点所连接的边，按照顺时针的顺序存储下来

}nodes[max_size];

std::vector<std::vector<qreal>> equation(max_size);//存储方程组(行列式)

bool indicator[max_size]; //深度搜索时判断边是否遍历过

int PipeSize,EdgeSum,NodeSum;  //记录网格边长

//函数功能：确定管道中某条管道的长度
//参数含义：x，管道的编号；leng，管道的长度
void setedgelength(int x, qreal leng)
{
    edges[x].length = leng;
}

//函数功能：将方程加入到方程组中
//参数含义：tmp，新的方程
void addrect(std::vector<qreal> &tmp){
    equation.push_back(tmp);
}

//函数功能：计算节点(x,y)的dir方向的管道编号。dir为0表示上方，1表示右侧，2表示下方，3表示左侧。若管道存在(不论长度是否为0)则返回对应管道编号，不存在(即不在原始网格内)则返回EDGESUM
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，询问的节点方向。
int getdirline(int x, int y, int dir){
	int e;
    int sum = x*PipeSize+y;
	if (dir == 0){
		if (y==0){
            if (edges[EdgeSum-5].destNode == sum)
                e = EdgeSum-5;
            else if (edges[EdgeSum-4].destNode == sum)
                e = EdgeSum-4;
			else 
                e = EdgeSum;
		}
		else 
            e=(x*(PipeSize-1)+y-1);
	}else if (dir == 1){
        if (x==PipeSize-1)
            e=EdgeSum;
		else 
            e=PipeSize*PipeSize-PipeSize+x*PipeSize+y;
	}else if (dir == 2){
        if (y==PipeSize-1){
            if (edges[EdgeSum-3].sourceNode == sum)
                e = EdgeSum-3;
            else if (edges[EdgeSum-2].sourceNode == sum)
                e = EdgeSum-2;
            else if (edges[EdgeSum-1].sourceNode == sum)
                e = EdgeSum-1;
			else 
                e = EdgeSum;
		}
		else
            e=(x*(PipeSize-1)+y);
	}else if (dir == 3){
		if (x==0)
            e=EdgeSum;
		else
            e=PipeSize*PipeSize-PipeSize+(x-1)*PipeSize+y;
	}
	return e;
}

//函数功能：计算节点(x,y)的dir方向的管道是否合理，即是否在原始网络中存在。dir为0表示上方，1表示右侧，2表示下方，3表示左侧。
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，询问的节点方向。
bool existdir(int x, int y, int dir)
{
	int e = getdirline(x,y,dir);
    if (e>=EdgeSum)
		return false;
    return (edges[e].length!=0);
}

//函数功能：从(x,y)沿着dir方向遍历闭环，遍历到end时，遍历结束。
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，下一步遍历的节点方向；tmp，存储的方程系数；end，遍历停止的管道。
void recursionline(int x, int y, int dir, std::vector<qreal> &tmp,int end){
	int e = getdirline(x,y,dir);
    if (e>EdgeSum-6)
		return;
    int nodeno = x*PipeSize+y;
    if (edges[e].sourceNode == nodeno){
        tmp[e] = edges[e].length;
	}
	else{
        tmp[e] = -edges[e].length;
	}

	if (e == end){
		addrect(tmp);
		return;
	}
	if (dir == 0){
		y--;
	}else if (dir == 1){
		x++;
	}else if (dir == 2){
		y++;
	}else if (dir == 3){
		x--;
	}
	for(int i=0; i<4; i++)
	{
		int newdir = dir+1-i;
		newdir = (newdir+4)%4;
		if (existdir(x,y,newdir))
		{
			recursionline(x,y,newdir,tmp,end);
			break;
		}
	}
}

//函数功能：从(x,y)位置进行深度优先搜索，直到到达边end结束
//参数含义：x，节点的横坐标；y节点的纵坐标；tmp，存储的方程系数；end，遍历停止的管道。
bool recursionrect(int x, int y, std::vector<qreal> &tmp,int end){
	int xx,yy;
	for(int i=1; i<5; i++)
	{
		int e =  getdirline(x,y,i%4);
		int dir = i%4;
		// cout<<"recursionrect  "<<x<<" "<<y<<" "<<e<<"  "<<i%4<<endl;
        if (e>=EdgeSum)
			continue;
        if (indicator[e])
			continue;
        if (edges[e].length==0)
			continue;
        indicator[e] = true;
        int nodeno = x*PipeSize+y;
        if (edges[e].sourceNode == nodeno){
            tmp[e] = edges[e].length;
		}
		else{
            tmp[e] = -edges[e].length;
		}
		if (e == end){
			// cout<<"alsdhjkagjkdhasdhasjkld"<<endl;
			return true;
		}
        if (e>EdgeSum-6){
			tmp[e] = 0;
			continue;
		}

		if (dir == 0){
			xx=x;yy=y-1;
		}else if (dir == 1){
			xx=x+1;yy=y;
		}else if (dir == 2){
			xx=x;yy=y+1;
		}else if (dir == 3){
			xx=x-1;yy=y;
		}
		if (recursionrect(xx,yy,tmp,end))
			return true;
		tmp[e] = 0;
	}
	return false;
}

//函数功能：从(x,y)位置开始向右寻找闭环路径，直到到达(x,y)下方的边t结束
//参数含义：x，节点的横坐标；y节点的纵坐标；t，遍历停止的管道编号。
void findline(int x, int y,int t){
    std::vector<qreal> tmp(EdgeSum+1,0);
	recursionline(x,y,1,tmp,t);
}

//函数功能：计算从一个输入端口，到三个输出管道的“电压降”，从而计算得到输出管道两两之间的“电势差”，根据电势差为0，加入方程组
//参数含义：x1，输入管道编号。
void findrect(int x1){
    std::vector<qreal> tmp(EdgeSum+1,0);
    for (int i=0; i<EdgeSum; i++)
        indicator[i] = false;
    recursionrect(edges[x1].destNode/PipeSize,0,tmp,EdgeSum-1);
    std::vector<qreal> temp(EdgeSum+1,0);
    for (int i=0; i<EdgeSum; i++)
        indicator[i] = false;
    recursionrect(edges[x1].destNode/PipeSize,0,temp,EdgeSum-2);
    std::vector<qreal> tep(EdgeSum+1,0);
    for (int i=0; i<EdgeSum; i++)
        indicator[i] = false;
    recursionrect(edges[x1].destNode/PipeSize,0,tep,EdgeSum-3);
    std::vector<qreal> emp(EdgeSum+1,0);
    for (int i=0; i<EdgeSum+1; i++)
		emp[i] = tmp[i]-temp[i];
    equation.push_back(emp);
    std::vector<qreal> tem(EdgeSum+1,0);
    for (int i=0; i<EdgeSum+1; i++)
		tem[i] = tep[i]-temp[i];
    equation.push_back(tem);
}

//函数功能：初始化方程组（行列式）的值
void initrect(){    
    for (int i=0;i<EdgeSum-5; i++)	//不存在的管道液体流速为0
        if (edges[i].length == 0)
		{
			// cout<<"exist  "<<i<<endl;
            std::vector<qreal> tmp(EdgeSum+1,0);
			tmp[i]=1;
			addrect(tmp);
		}
	// cout<<rect.size()<<endl;
    for (int i=0; i<NodeSum-2; i++)  //首先根据基尔霍夫定律，统计所有的电流的相等关系
	{
		int number = 0;
        std::vector<qreal> tmp(EdgeSum+1,0);
        for (int j=0; j<(int)nodes[i].edgeList.size(); j++)
            if (edges[nodes[i].edgeList[j]].length!=0)
            {
                number++;
                if (edges[nodes[i].edgeList[j]].sourceNode == i)
                    tmp[nodes[i].edgeList[j]] = 1;
                else
                    tmp[nodes[i].edgeList[j]] = -1;
            }
        tmp[EdgeSum] = 0;
		if (number>0)
			addrect(tmp);
	}
	// cout<<rect.size()<<endl;
    for (int i=0; i<PipeSize-1; i++)	//寻找电路中的最小环,对于每个环路径电势差为0
        for (int j=0; j<PipeSize-1; j++)
		{
            int t = i*(PipeSize-1)+j;
            int m = PipeSize*PipeSize-PipeSize+i*PipeSize+j;
            if (edges[t].length !=0 && edges[m].length !=0)
					findline(i,j,t);
		}
	// cout<<rect.size()<<endl;

	//三个输出端口之间的电势差为0
    findrect(EdgeSum-4);
	//两个输入端口的流速相同且已知，构成两个方程
    std::vector<qreal> tmp(EdgeSum+1,0);
    tmp[EdgeSum-5] = 1;
    tmp[EdgeSum] = 200;
	addrect(tmp);
    std::vector<qreal> temp(EdgeSum+1,0);
    temp[EdgeSum-4] = 1;
    temp[EdgeSum] = 200;
	addrect(temp);

	// cout<<rect.size()<<endl;
}


template<class T>
inline T&& min(T&& a , T&& b) noexcept {
    return a < b ? a : b;
}

//函数功能：计算a和b的最大公约数。
//参数含义：。
qreal GreatestCommonDivisor(qreal a, qreal b)
{
    qreal t;
    if (a < b)
    {
        t = a;
        a = b;
        b = t;
    }    
    if (b==1)
    	return 1;
    while (std::fabs(b) >= NAX)
    {
        t = fmod(a , b);
        a = b;
        b = t;
    }
    return a;
}

//函数功能：计算a和b的最小公倍数。
//参数含义：。
qreal LeastCommonMultiple (qreal a, qreal b)

{
    qreal c = GreatestCommonDivisor(a,b);
    qreal t = a  /c * b;
    return t;

}

//函数功能：使用行列式计算方程组rect的解。
void getans()    
{
    int n = equation.size();

	for (int i=0; i<n; i++)
        for (int j=0; j<EdgeSum+1; j++)
            if (std::fabs(equation[i][j])<NAX)
                equation[i][j] = 0;

	int num = 0;
	for (int i=0; i<n; i++){
        if (std::fabs(equation[i][num]) <NAX){
			int mjj = 0;
			for (int j=i+1; j<n; j++)
                if ( !(std::fabs(equation[j][num])<NAX))
				{
					mjj++;
                    for (int k=0; k<EdgeSum+1; k++)
					{
                        qreal t = equation[j][k];
                        equation[j][k] = equation[i][k];
                        equation[i][k] = t;
					}
					break;
				}
		}
		for (int j=0; j<n; j++)
            if (i!=j && (std::fabs(equation[j][num])>NAX))
            {
                qreal ml = LeastCommonMultiple(std::fabs(equation[j][num]),std::fabs(equation[i][num]));
                qreal t = ml/equation[j][num];
                qreal kt = ml/equation[i][num];
                for (int k=EdgeSum; k>=0; k--){
                    equation[j][k] = equation[j][k]*t;
                    equation[j][k] = (std::fabs(equation[j][k])<NAX)?0:equation[j][k];
                }
                for (int k=EdgeSum; k>=num; k--)
                {
                    equation[j][k] -= kt*equation[i][k];
                    equation[j][k] = (std::fabs(equation[j][k])<NAX)?0:equation[j][k];
                }
            }
			
        num ++;
        for (int j=0; j<n; j++){
            qreal common = 0;
            for (int k=0; k<EdgeSum+1; k++)
            if ((std::fabs(equation[j][k]) > NAX)){
                if (std::fabs(common) < NAX)
                    common = std::fabs(equation[j][k]);
                else
                    common = GreatestCommonDivisor(common,std::fabs(equation[j][k]));
            }
            if (common!=0)
                for (int k=0; k<EdgeSum+1; k++){
                    equation[j][k] = equation[j][k]/common;
                    equation[j][k] = (std::fabs(equation[j][k])<NAX)?0:equation[j][k];
                }
        }
        if (num==EdgeSum)
			break;
	}
	
	num = 0;
    for (int i=0; i<EdgeSum; i++)
	{
        edges[num].velocity = qreal(equation[i][EdgeSum])/qreal(equation[i][num]);
        if (edges[num].velocity<0)
		{
            edges[num].velocity = -edges[num].velocity;
            int tm = edges[num].sourceNode;
            edges[num].sourceNode = edges[num].destNode;
            edges[num].destNode = tm;
		}
		num++;
        if (num==EdgeSum)
			break;
	}

}

//函数功能：计算芯片所有管道的液体流速
//参数含义：num，正方形网格的边长（即网格一行的节点数量，比如8X8的网格，一行有8个节点，num为8）；length，存储网格中每个管道的长度，若管道不存在用0表示；i1,i2,o1,o2,o3
//分别表示两个输入管道与三个输出管道在第几列。
QVector<qreal> caluconspeed(int num, const QVector<qreal>&length, int i1, int i2, int o1, int o2, int o3)
{
    equation.clear();
    PipeSize = num;
    EdgeSum = 2*PipeSize*PipeSize-2*PipeSize+5;
    NodeSum = PipeSize*PipeSize+2;
    for (int i=0; i<NodeSum; i++){
        nodes[i].edgeList.clear();
    }

	int n1 = 0;
	int n2 = 1;

    for (int i=0; i<PipeSize*PipeSize-PipeSize; i++)
	{
        edges[i].sourceNode = n1;
        edges[i].destNode = n2;
        nodes[n1].edgeList.push_back(i);
        nodes[n2].edgeList.push_back(i);
		n1++;n2++;
        if (n2%PipeSize==0)
		{
			n1++;n2++;
		}
	}
	n1 = 0;
    n2 = n1+PipeSize;
    for (int i=PipeSize*PipeSize-PipeSize; i<2*PipeSize*PipeSize-2*PipeSize; i++)
	{
        edges[i].sourceNode = n1;
        edges[i].destNode = n2;
        nodes[n1].edgeList.push_back(i);
        nodes[n2].edgeList.push_back(i);
		n1++;n2++;
	}

    edges[2*PipeSize*PipeSize-2*PipeSize+0].sourceNode = PipeSize*PipeSize;
    edges[2*PipeSize*PipeSize-2*PipeSize+0].destNode = (i1)*PipeSize;
    nodes[PipeSize*PipeSize].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+0);
    nodes[(i1)*PipeSize].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+0);

    edges[2*PipeSize*PipeSize-2*PipeSize+1].sourceNode = PipeSize*PipeSize;
    edges[2*PipeSize*PipeSize-2*PipeSize+1].destNode = (i2)*PipeSize;
    nodes[PipeSize*PipeSize].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+1);
    nodes[(i2)*PipeSize].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+1);

    edges[2*PipeSize*PipeSize-2*PipeSize+2].sourceNode = (o1+1)*PipeSize-1;
    edges[2*PipeSize*PipeSize-2*PipeSize+2].destNode = PipeSize*PipeSize+1;
    nodes[(o1+1)*PipeSize-1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+2);
    nodes[PipeSize*PipeSize+1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+2);

    edges[2*PipeSize*PipeSize-2*PipeSize+3].sourceNode = (o2+1)*PipeSize-1;
    edges[2*PipeSize*PipeSize-2*PipeSize+3].destNode = PipeSize*PipeSize+1;
    nodes[(o2+1)*PipeSize-1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+3);
    nodes[PipeSize*PipeSize+1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+3);

    edges[2*PipeSize*PipeSize-2*PipeSize+4].sourceNode = (o3+1)*PipeSize-1;
    edges[2*PipeSize*PipeSize-2*PipeSize+4].destNode = PipeSize*PipeSize+1;
    nodes[(o3+1)*PipeSize-1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+4);
    nodes[PipeSize*PipeSize+1].edgeList.push_back(2*PipeSize*PipeSize-2*PipeSize+4);
	
    for (int i=0; i<EdgeSum; i++)
	{
		setedgelength(i,length[i]);
	}
    edges[EdgeSum-4].velocity = 200;
    edges[EdgeSum-5].velocity = 200;

	initrect();
	getans();

    QVector<qreal> retval;
    for(int i=0;i<EdgeSum;++i)
        retval.push_back(edges[i].velocity);

    return retval;
}
