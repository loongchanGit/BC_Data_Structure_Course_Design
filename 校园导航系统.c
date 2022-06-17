#include<stdio.h>
#include<string.h>
#define max 100
typedef struct
{
	int num;
	char name[20];
	char info[50];
}data;

typedef struct
{
	data vexs[max];//结点 
	int arcs[max][max];//邻接矩阵 
	int vexnum,arcnum;//结点数，边数 
}MGrapt; 
int DFSvisited[max]={0};//结点访问标记 
int DFSsave[max]={0}; 
int djsave[max];
int count;
int shortlength[max];
int primqueue[max]={0};
int s;
MGrapt TG;//理工地图
int Infinity=65536;//无穷大 
void initG();// 初始化图
void menu();//显示菜单 
void queryinfo();//景点信息查询 
void addinfo();//新增景点信息 
void modifyinfo();//修改景点和道路信息
void deleteinfo();//删除景点和道路信息
void Pathquery();//求任意两点的路径查询
void onetoallpath();//求一个到所有的最短路径
void twopath();//求两个之间的最短路径 
void netting();//最佳布网方案 
void ergodic();// 求任意一点走遍全校最短路径 
void initG()// 初始化图
{
	int i,j; 
	TG.vexnum=14;//14个结点 
 	TG.arcnum=20;//20条边
	data temp[100]={{1,"北门","这里是北门"},
					{2,"一期食堂","这里是一期食堂"}, 
					{3,"旧操场","这里是旧操场"},
					{4,"明理9","这里是明理9"},
					{5,"博学苑","这里是博学苑"},
					{6,"艺术会堂","这里是艺术会堂"},
					{7,"医务室","这里是医务室"},
					{8,"风洞实验室","这里是风洞实验室"},
					{9,"创新创业园","这里是创新创业园"},
					{10,"计算机学院","这里是计算机与信息工程学院"},
					{11,"材料学院","这里是材料科学与工程学院"},
					{12,"图书馆","这里是图书馆"},
					{13,"新操场","这里是新操场"},
					{14,"体育馆","这里是体育馆"},
				   };
	for(i=0;i<TG.vexnum;i++)
		TG.vexs[i]=temp[i];
	for(i=0;i<TG.vexnum;i++)
		TG.arcs[i][i]=Infinity;
	for(i=0;i<max;i++)//邻接矩阵所有元素初始化为无穷大 ，无路径就为无穷大 
		for(j=0;j<max;j++)
			TG.arcs[i][j]=Infinity; 
	TG.arcs[0][1]=140;
	TG.arcs[0][2]=176;
	TG.arcs[1][3]=276;
	TG.arcs[2][5]=310;
	TG.arcs[2][13]=184;
	TG.arcs[3][4]=110;
	TG.arcs[3][6]=224;
	TG.arcs[4][5]=100;
	TG.arcs[5][6]=230;
	TG.arcs[5][7]=150;
	TG.arcs[5][10]=210;
	TG.arcs[5][11]=240;
	TG.arcs[6][8]=180;
	TG.arcs[6][7]=203;
	TG.arcs[7][8]=176;
	TG.arcs[8][9]=146;
	TG.arcs[9][10]=120;
	TG.arcs[10][12]=500;
	TG.arcs[11][12]=337;
	TG.arcs[12][13]=157;
	for(i=0;i<TG.vexnum;i++)
		for(j=0;j<TG.vexnum;j++)
			TG.arcs[j][i]=TG.arcs[i][j];
}

void menu()
{
	int num; 
	do
	{
		printf("\n");
		printf("************欢迎使用厦门理工学院导游咨询系统***********");
		printf("\n");
		printf("	1.景点信息查询\n");
		printf("	2.新增景点信息\n");
		printf("	3.修改景点和道路信息\n");
		printf("	4.删除景点和道路信息\n");
		printf("	5.任意两个景点的路径查询\n");
		printf("	6.求一个景点到所有景点的最短路径\n");
		printf("	7.求任意两个景点之间的最短路径\n");
		printf("	8.最佳布网方案\n");
		printf("	0.退出系统\n");
		printf("*******************************************************\n");
		printf("请输入序号：");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8)
		{	
			system("cls"); 
			printf("请输入正确的序号！");		
		}
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8);
	switch(num)
	{
		case 0: exit(0);
		case 1: queryinfo();break;
		case 2: addinfo();break;
		case 3: modifyinfo();break;
		case 4: deleteinfo();break;
		case 5: Pathquery();break;
		case 6: onetoallpath();break;
		case 7: twopath();break;
		case 8: netting();break;
	//	case 9: 
	}
}

void queryinfo()//景点信息查询 
{
	int num;
	int i,j;
	int flag=0;
	char name[20];
	system("cls");
	do
	{
		printf("\n");
		printf("          1：按照景点编号查询\n");
		printf("          2：按照景点名称查询\n");
		printf("          3：列出所有景点和道路信息\n");
		printf("          0：返回上一级\n");
		printf("请输入序号：");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3 )
		{	
			system("cls"); 
			printf("请输入正确的序号！");		
		}
	}while(num!=0 && num!=1 && num!=2 && num!=3);
	if(num==1)
	{
		flag=0;
		printf("请输入景点编号：");
		scanf("%d",&num);
		for(i=0;i<TG.vexnum;i++)
		{
			if(TG.vexs[i].num==num)
			{
				flag=1;
				printf("景点编号：%d\n",TG.vexs[i].num);
				printf("景点名称：%s\n",TG.vexs[i].name);
				printf("景点介绍：%s\n",TG.vexs[i].info);
				printf("\n");
				printf("该景点路径信息：\n");
				for(j=0;j<TG.vexnum;j++)
				{
					if(TG.arcs[i][j]!=Infinity)					
						printf("到景点%d--%s的距离为%d\n",TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
				}
			}
		}
		if(flag==0)
		printf("对不起，无此编号！"); 
		getchar();
		getchar();
		system("cls");
		queryinfo();
	}
	else if(num==2)
	{
		flag=0;
		printf("请输入景点名称：");
		scanf("%s",name);
		for(i=0;i<TG.vexnum;i++)
		{
			if(strcmp(name,TG.vexs[i].name)==0)
			{
				flag=1;
				printf("景点编号：%d\n",TG.vexs[i].num);
				printf("景点名称：%s\n",TG.vexs[i].name);
				printf("景点介绍：%s\n",TG.vexs[i].info);
				printf("\n");
				printf("该景点路径信息：\n");
				for(j=0;j<TG.vexnum;j++)
				{
					if(TG.arcs[i][j]!=Infinity)					
						printf("到景点%d--%s的距离为%d\n",TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
				}
			}
		}
		if(flag==0)
		printf("对不起，无此名称！"); 
		getchar();
		getchar();
		system("cls");
		queryinfo();
	}
	else if(num==3)
	{
		printf("景点编号	景点名称	景点介绍\n");
		for(i=0;i<TG.vexnum;i++)
		printf("%-16d%-16s%s\n",TG.vexs[i].num,TG.vexs[i].name,TG.vexs[i].info);
		printf("\n");
		printf("道路信息：\n");
		for(i=0;i<TG.vexnum;i++)
		{
			for(j=i;j<TG.vexnum;j++)
			{
				if(TG.arcs[i][j]!=Infinity)
				printf("景点%d--%s和景点%d--%s存在道路，距离为%d\n",TG.vexs[i].num,TG.vexs[i].name,TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
			}
		}
		getchar();
		getchar();
		system("cls");
		queryinfo();
	}
	else if(num==0)
	{
		system("cls");
		menu();
	}
}

void addinfo()//新增景点信息 
{
	int num;
	char name[20];
	char info[50];
	int flag=0;
	int i;
	printf("请输入待新增的景点信息：\n");
	do
	{
		printf("景点编号：");
		scanf("%d",&num);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==num)	
			flag=1;				
		if(flag==1)
		{
			printf("该编号已存在！"); 
			getchar();
			getchar();
			system("cls");
			menu();
		}
	}while(flag==1); 
	printf("景点名称：");
	scanf("%s",name);
	printf("景点介绍：");
	scanf("%s",info); 
	TG.vexs[TG.vexnum].num=num;
	strcpy(TG.vexs[TG.vexnum].name,name);
	strcpy(TG.vexs[TG.vexnum].info,info);
	TG.vexnum++;
	printf("新增景点信息成功！"); 
	getchar();
	getchar();
	system("cls");
	menu();
}

void modifyinfo()//修改景点和道路信息
{
	int num;
	char name[20];
	char info[50];
	int i;
	int flag;
	int x,y;
	int first,second,length;
	system("cls");
	do
	{
		printf("\n");
		printf("          1：输入景点编号修改景点信息\n");
		printf("          2：输入景点名称修改景点信息\n");
		printf("          3：修改路径信息，如原无路径则新增\n");
		printf("          0：返回上一级\n");
		printf("请输入序号：");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3)
		{	
			system("cls"); 
			printf("请输入正确的序号！");		
		}
	}while(num!=0 && num!=1 && num!=2 && num!=3);
	if(num==0)
	{
		system("cls");
		menu();
	}
	else if(num==1)
	{
		flag=0; 
		do
		{
			printf("请输入景点编号：");
			scanf("%d",&num);
			for(i=0;i<TG.vexnum;i++)
			if(TG.vexs[i].num==num)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("对不起，无此编号！"); 
				getchar();
				getchar();
				system("cls");
				modifyinfo();
			}
		}while(flag==0); 
		printf("请输入修改后的名称：");
		scanf("%s",name);
		strcpy(TG.vexs[x].name,name);
		printf("请输入修改后的介绍："); 
		scanf("%s",info);
		strcpy(TG.vexs[x].info,info);
		printf("景点信息修改成功！"); 
		getchar();
		getchar();
		system("cls");
		modifyinfo();
	}
	else if(num==2)
	{
		flag=0; 
		do
		{
			printf("请输入景点名称：");
			scanf("%s",name);
			for(i=0;i<TG.vexnum;i++)
			if(strcmp(TG.vexs[i].name,name)==0)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("对不起，无此名称！"); 
				getchar();
				getchar();
				system("cls");
				modifyinfo();
			}
		}while(flag==0); 
		printf("请输入修改后的名称：");
		scanf("%s",name);
		strcpy(TG.vexs[x].name,name);
		printf("请输入修改后的介绍："); 
		scanf("%s",info);
		strcpy(TG.vexs[x].info,info);
		printf("景点信息修改成功！"); 
		getchar();
		getchar();
		system("cls");
		modifyinfo();
	}
	else if(num==3)
	{
		flag=0;
		printf("请输入待修改的路径信息，如无路径则新增\n");
		printf("格式形如(1-2,60),表示编号 1 2，路径长度60：\n");
		scanf("%d-%d,%d",&first,&second,&length);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==first)
		{
			x=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("输入的编号不存在！");
			getchar();
			getchar();
			system("cls");
			modifyinfo();
		}
		flag=0;
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==second)
		{
			y=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("输入的编号不存在！");
			getchar();
			getchar();
			system("cls");
			modifyinfo();
		}
		TG.arcs[x][y]=length;
		TG.arcs[y][x]=length;
		printf("修改信息成功！"); 
		getchar();
		getchar();
		system("cls");
		modifyinfo();
	}
}

void deleteinfo()//删除景点和道路信息
{
	int num;
	char name[20];
	char info[50];
	int i;
	int flag;
	int x,y;
	int first,second,length;
	system("cls");
	do
	{
		printf("\n");
		printf("          1：输入景点编号删除景点信息\n");
		printf("          2：输入景点名称删除景点信息\n");
		printf("          3：删除道路信息\n");
		printf("          0：返回上一级\n");
		printf("请输入序号：");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3)
		{	
			system("cls"); 
			printf("请输入正确的序号！");		
		}
	}while(num!=0 && num!=1 && num!=2 && num!=3);
	if(num==0)
	{
		system("cls");
		menu();
	}
	else if(num==1)
	{
		flag=0; 
		do
		{
			printf("请输入景点编号：");
			scanf("%d",&num);
			for(i=0;i<TG.vexnum;i++)
			if(TG.vexs[i].num==num)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("对不起，无此编号！"); 
				getchar();
				getchar();
				system("cls");
				deleteinfo();
			}
		}while(flag==0); 
		for(i=x;i<TG.vexnum;i++)
		TG.vexs[i]=TG.vexs[i+1];
		TG.vexnum--;
		printf("景点删除成功！");
		getchar();
		getchar();
		system("cls");
		deleteinfo();
	}
	else if(num==2)
	{
		flag=0; 
		do
		{
			printf("请输入景点名称：");
			scanf("%s",name);
			for(i=0;i<TG.vexnum;i++)
			if(strcmp(TG.vexs[i].name,name)==0)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("对不起，无此名称！"); 
				getchar();
				getchar();
				system("cls");
				deleteinfo();
			}
		}while(flag==0); 
		for(i=x;i<TG.vexnum;i++)
		TG.vexs[i]=TG.vexs[i+1];
		TG.vexnum--;
		getchar();
		getchar();
		system("cls");
		deleteinfo();
	}
	else if(num==3)
	{
		flag=0;
		printf("请输入待删除的路径信息\n");
		printf("格式形如(1-2),表示编号 1 2\n");
		scanf("%d-%d,%d",&first,&second);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==first)
		{
			x=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("输入的编号不存在！");
			getchar();
			getchar();
			system("cls");
			deleteinfo();
		}
		flag=0;
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==second)
		{
			y=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("输入的编号不存在！");
			getchar();
			getchar();
			system("cls");
			deleteinfo();
		}
		TG.arcs[x][y]=Infinity;
		TG.arcs[y][x]=Infinity;
		printf("删除成功！"); 
		getchar();
		getchar();
		system("cls");
		deleteinfo();
	}
}

void DFS(int m,int start, int end)//深搜 
{
    int i,j; 
    for(i = 0; i < TG.vexnum; i++)
	{
        if(TG.arcs[start][i] !=Infinity && DFSvisited[i] == 0)//起始结点到i存在路径且i未被访问 
		{
            DFSvisited[i] = 1;
            if(i == end)//等于目标结点时打印 
			{
                count++;
                printf("★%d.",count);
                for(j = 0; j < m; j++) 
				{
                    printf("%s->", TG.vexs[DFSsave[j]].name);
                }
                printf("%s\n", TG.vexs[end].name);
                DFSvisited[i] = 0;
            }
            else //不等则存储结点 
			{
                DFSsave[m] = i;
                m++;
                DFS(m,i, end);
                m--;
                DFSvisited[i] = 0;//递归把这条路径上所有结点初始化为未访问 
            }
        }
    }
}

void Pathquery()//求任意两点的路径查询
{
	int flag=0; 
	int start,end;
	int x,y;
	int i;
	for(i=0;i<TG.vexnum;i++)//初始化访问 
	{
		DFSvisited[i]=0;
		DFSsave[i]=0;	
	}
	printf("请输入起始景点编号和终点景点编号，用空格隔开：");
	scanf("%d %d",&start,&end);
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==start)
	{
		flag=1;
		x=i;
	}
	if(flag==0)
	{
		printf("输入的编号不存在！");
		getchar();
		getchar();
		system("cls");
		menu(); 
	}
	flag=0;
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==end)
	{
		flag=1;
		y=i;
	}
	if(flag==0)
	{
		printf("输入的编号不存在！");
		getchar();
		getchar();
		system("cls");
		menu(); 
	}
	DFSsave[0]=x;//开始结点 
	DFSvisited[x]=1;
	DFS(1,x,y);
	getchar();
	getchar();
	system("cls");
	menu(); 
}



void onetoallpath()//求一个到所有的最短路径
{
	int start;
	int i,j;
	int flag=0;
	int x=0;
	int stack[max]={-1};
	int s=0;
	printf("请输入起始景点编号：");
	scanf("%d",&start);
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==start)
	{
		flag=1;
		x=i;
	}
	if(flag==0)
	{
		printf("输入的编号不存在！"); 
		getchar();
		getchar();
		system("cls");
		menu();
	}
	Dijkstra(x);
	printf("%s到其他各景点的最短距离如下：\n",TG.vexs[x].name);
	for(i=0;i<TG.vexnum;i++)
	{
		if(i!=x)
		{
			s=0;
			stack[0]=djsave[i]; //终点的前一个结点下标值放入数组 
			printf("%s->",TG.vexs[x].name);
			/*for(i=0;i<TG.vexnum;i++)
			printf("%d、",djsave[i]);*/
			for(j=1;j<TG.vexnum;j++)
			{
			stack[j]=djsave[stack[j-1]];//每次存储上一个结点的前一个结点下标 
			}
			for(j=0;j<TG.vexnum;j++)
			{
			if(stack[j]==-1) 
			break;
			s++;//计算共有多少结点（不包括开始和结束）
			}
			for(j=s-1;j>=0;j--)
			printf("%s->",TG.vexs[stack[j]].name);
			printf("%s\n",TG.vexs[i].name);
			printf("距离为：%dm\n",shortlength[i]);
		}		
	}
	getchar();
	getchar();
	system("cls");
	menu();		
}

int Dijkstra(int start)
{
	int visited[max]={0};
	int min,i,j,k;
	int s=0;
	for(i=0;i<TG.vexnum;i++)//记录起点所有邻接结点权值 
	{
		shortlength[i]=TG.arcs[start][i];
		visited[i]=0;//初始化为未访问 
		djsave[i]=-1;
	}
	shortlength[start]=0;
	visited[start]=1;//开始结点标记已访问 
	for(i=0;i<TG.vexnum;i++)
	{
		k=-1;
		min=Infinity;
		for(j=0;j<TG.vexnum;j++)//找出最短路径 
		{
			if(visited[j]==0 && shortlength[j]<min)//j结点未被访问，起点到j结点的权值小于最小值 
			{
				min=shortlength[j];
				k=j;	
			}
		}
		visited[k]=1;
		
		for(j=0;j<TG.vexnum;j++)
		{
			if(visited[j]==0 && TG.arcs[k][j]+shortlength[k]<shortlength[j])//修正最短路径 
			{
				shortlength[j]=TG.arcs[k][j]+shortlength[k];
				djsave[j]=k;
			}
			
		} 
	}
}

void twopath()//求两个之间的最短路径 
{
	int flag=0; 
	int start,end;
	int x=0,y=0;
	int i=0;
	int stack[max]={-1};
	int s=0;
	printf("请输入起始景点编号和终点景点编号，用空格隔开：");
	scanf("%d %d",&start,&end);
	if(start==end)
	{
		printf("起点和终点不能相同！");
		getchar();
		getchar();
		system("cls");
		menu(); 
	}
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==start)
	{
		x=i;
		flag=1;
	}	
	if(flag==0)
	{
		printf("输入的编号不存在！");
		getchar();
		getchar();
		system("cls");
		menu();
	}
	flag=0; 
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==end)
	{
		y=i;
		flag=1;
	}
	if(flag==0)
	{
		printf("输入的编号不存在！");
		getchar();
		getchar();
		system("cls");
		menu();
	}
	Dijkstra(x);
	printf("从%s到%s的最短路径是：\n",TG.vexs[x].name,TG.vexs[y].name);
	stack[0]=djsave[y]; //终点的前一个结点下标值放入数组 
	printf("%s->",TG.vexs[x].name);
	/*for(i=0;i<TG.vexnum;i++)
	printf("%d、",djsave[i]);*/
	for(i=1;i<TG.vexnum;i++)
	{
		stack[i]=djsave[stack[i-1]];//每次存储上一个结点的前一个结点下标 
	}
	for(i=0;i<TG.vexnum;i++)
	{
		if(stack[i]==-1) 
		break;
		s++;//计算共有多少结点（不包括开始和结束） 
	}
	for(i=s-2;i>=0;i--)
	printf("%s->",TG.vexs[stack[i]].name);
	printf("%s\n",TG.vexs[y].name);
	printf("距离为：%dm",shortlength[y]);
	getchar();
	getchar();
	system("cls");
	menu();
}

int prim(int start)
{
	int lowcost[max]={0};
    int min;
    int i,k,j;
    int cost=0;
    s=0;//全局变量 
    for(i=0;i<TG.vexnum;i++)
    {
    	if(i!=start)
    	{
    		primqueue[i]=start;
    		lowcost[i]=TG.arcs[start][i];//把1结点的邻接结点对应的权值记录下来
		}
	}
        
    //lowcost[start]=0;//1结点赋值为0表示已访问
    for(i=0;i<TG.vexnum-1;i++)
    {
        min=99999;
        j=0;
        k=0;
        while(j<TG.vexnum)
        {
            if(lowcost[j]!=0 && lowcost[j]<min)//找出权值最下的且记录该下标
            {
                min=lowcost[j];
                k=j;
            }
            j++;
        }
        cost=cost+min;//把最小结点权值加入
        printf("	从%s---%s:%d m\n", TG.vexs[primqueue[k]].name,TG.vexs[k].name,lowcost[k]);
        //printf("%d\n",cost);
        lowcost[k]=0;//该结点标记为已访问
       // primqueue[s++]=k;
        for(j=0;j<TG.vexnum;j++)//更新顶点集到其他结点的路径
        {
            if(j!=k && lowcost[j]!=0 && TG.arcs[k][j]<lowcost[j])//已访问的结点就不需要找到该结点的最短路径
            {
            	lowcost[j]=TG.arcs[k][j];
            	primqueue[j]=k;
			}
                
        }
    }
    return cost;
}

void netting()// 求任意一点走遍全校最短路径
{
	int start; 
	int i;
	int x;
	int flag=0;
	int length=0;
	printf("请输入景点编号：");
	scanf("%d",&start);
	for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==start)
		{
			flag=1;
			x=i;
		}
	if(flag==0)
	{
		printf("输入的编号不存在！");
		getchar();
		getchar();
		system("cls");
		menu();
	}
	length=prim(x);
	printf("	总长度为：%dm ",length);
	getchar();
	getchar();
	system("cls");
	menu();
}


int main()
{
	initG();
	menu();
	return 0; 
}
