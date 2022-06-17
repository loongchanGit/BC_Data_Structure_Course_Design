#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parkcount=0;//车位数量 
char vipcar[100][10];//存放vip车牌号 
int vipcount;//vip数量 
int tick=5;
typedef struct Node   //数据
{
    char number[10];
    char time[10]; 
}Node;

typedef struct QueueNode   //队列结点
{
    struct Node data; //数据域 
    struct QueueNode * next;//指针域 
}*QueueNode;

typedef struct LinkQueue    //链队列
{
    struct QueueNode * front;//头 
    struct QueueNode * rear;//尾 
}LinkQueue;

typedef struct stack         //栈结点
{
    struct Node data;
    struct stack *next;
}*StackNode;

typedef struct LinkStack     //链栈
{
    StackNode top;//栈顶 
    int count;//栈总容量 
}LinkStack;
void menu(LinkQueue *road,LinkStack *park,LinkStack *move,char num[],char t[]);//菜单
int init(LinkQueue *road,LinkStack *park,LinkStack *move);//初始化 
int linklength(LinkQueue q);//计算队列长度 
int inqueue(LinkQueue *q,char num[],char t[]);//入队 
int outqueue(LinkQueue *q,char *num,char *t);//出队 
int push(LinkStack *s,char num[],char t[]);//入栈 
int pop(LinkStack *s,char *num,char *t);//出栈 
void inpark(LinkQueue *road,LinkStack *park,LinkStack *move);//停车场入车 
void outpark(LinkQueue *road,LinkStack *park,LinkStack *move);//停车场出车
void view(LinkQueue *road,LinkStack *park,LinkStack *move);//查看停车场状态 
void query(LinkQueue *road,LinkStack *park,LinkStack *move);//查询车辆入场时间 
void add(LinkQueue *road,LinkStack *park,LinkStack *move);//新增停车场车位 
void vip(LinkQueue *road,LinkStack *park,LinkStack *move);//vip模块 
void money(LinkQueue *road,LinkStack *park,LinkStack *move);
void menu(LinkQueue *road,LinkStack *park,LinkStack *move,char num[],char t[])//菜单
{
	int s;
	do
	{
	printf("                  ** 停车场管理程序 **\n");
	printf("=========================================================\n");
	printf("**                                                     **\n");
	printf("**       1 --- 汽车进车场       2 --- 汽车出车场       **\n");
	printf("**       3 --- 查看停车场状态   4 --- 查询汽车入场时间 **\n");
	printf("**       5 --- 新增停车场车位   6 --- vip              **\n");
	printf("**       7 --- 修改价格         0 --- 退出程序         **\n");
	printf("**                                                     **\n");
	printf("**           停车场剩余%-1d车位，每小时收费%d元            **\n",parkcount-park->count,tick);
	printf("=========================================================\n");
	printf("请输入序号：");
	scanf("%d",&s);
	if(s==0)
	{
		exit(1);
	}
	else if(s==1)
	{
		inpark(road,park,move);
	}
	else if(s==2)
	{
		outpark(road,park,move);
	} 
	else if(s==3)
	{
		view(road,park,move);
	}
	else if(s==4)
	{
		query(road,park,move);
	} 
	else if(s==5)
	{
		add(road,park,move);
	} 
	else if(s==6)
	{
		vip(road,park,move);
	}
	else if(s==7)
	{
		money(road,park,move);
	}
	else
	{
		system("cls");
		printf("请输入正确的序号！\n");
	}
	}while(s!=1 && s!=2 && s!=3 && s!=4 && s!=5 && s!=6 && s!=7);
	
}
int init(LinkQueue *road,LinkStack *park,LinkStack *move)
{
    QueueNode node = (QueueNode)malloc(sizeof(struct QueueNode));
    if(node==NULL)
    {
        return 0;
    }
    node->next = NULL;//初始化等待队列 
    road->front = node;
    road->rear = node;

    move->top = NULL;//初始化移动车辆栈 
    move->count = 0;	
    park->top=NULL;//初始化停车栈 
    park->count=0;
}
int linklength(LinkQueue q)//计算队列长度 
{
    int i = 0;
    while(q.front != q.rear)
    {
        i++;
        q.front = q.front->next;
    }
    return i;
}
int inqueue(LinkQueue *q,char num[],char t[])//入队 
{
    QueueNode node = (QueueNode)malloc(sizeof(struct QueueNode));
    if(NULL == node)
    {
        return 0;
    }
    strcpy(node->data.number,num);
    strcpy(node->data.time,t);
    node->next = NULL;
    q->rear->next = node;
    q->rear = node;
    return 1;
}

int outqueue(LinkQueue *q,char *num,char *t)//出队 
{
    if(q->front == q->rear)
    {
        return 0;
    }
    strcpy(num,q->front->next->data.number);
    strcpy(t,q->front->next->data.time);
    QueueNode temp = q->front->next;//存放待删除结点的地址 
    q->front->next = q->front->next->next;
    if(temp->next == NULL)//只剩下头尾两个结点的情况，删除尾结点，把头尾指针都指向头结点 
    {
        q->rear = q->front;
    }
    free(temp);
    return 1;
}
int push(LinkStack *s,char num[],char t[])//入栈 
{
    StackNode node = (StackNode)malloc(sizeof(struct stack));
    if(node==NULL)
    {
        return 0;
    }
    strcpy(node->data.number,num);
    strcpy(node->data.time,t);
    node->next = s->top;
    s->top = node;
    s->count++;
    return 1;
}

int pop(LinkStack *s,char *num,char *t)//出栈 
{
    if(s->count==0)
    {
        return 0;
    }
    strcpy(num,s->top->data.number);
    strcpy(t,s->top->data.time);
    StackNode temp = s->top;
    s->top = s->top->next;
    free(temp);
    s->count--;
    return 1;
}
void inpark(LinkQueue *road,LinkStack *park,LinkStack *move)//停车场入车 
{
	int s=0;
	char num[10];
	char t[10];
	int flag;
	StackNode p;
	QueueNode r;
	do
	{
		flag=0;
		p=park->top;
		r=road->front;
		printf("请输入入场车辆的车牌号：");
		scanf("%s",num);
		while(p!=NULL)
		{	
			if(strcmp(p->data.number,num)==0)//检查停车场里是否已存在相同车牌号的汽车 
			{
				flag=1;
				printf("停车场已存在相同车牌号的汽车，请检查车牌号输入是否正确！\n");
			}
			p=p->next;
		}
		while(r->next!=NULL)
		{
			if(strcmp(r->next->data.number,num)==0)//检查停车场里是否已存在相同车牌号的汽车 
			{
				flag=1;
				printf("等候区已存在相同车牌号的汽车，请检查车牌号输入是否正确！\n");
			}
			r=r->next;
		}
	}while(flag==1);
		while(1)
			{
				printf("请输入汽车入场时间(格式hh:ss)：");
				scanf("%s",t);
				if((t[0]-'0')>=2 && (t[1]-'0')>3 || t[2]!=':' || (t[3]-'0')>=6&& (t[4]-'0')>=0)
					printf("请按正确的格式输入入场时间！\n");
				else
					break;
			}
	if( park->count >=parkcount)//停车场内车已停满 
    {
        printf("停车场已满，进入等待区！\n");
        inqueue(road,num,t);//进入便道等候区 
    	printf("请按任意键继续..."); 
       	getchar();
       	getchar();
      	system("cls");
       	menu(road,park,move,num,t);
    }
    else
    {
       push(park,num,t);//入栈 
       printf("该车已进入停车场%d号车道\n",park->count); 
       printf("请按回车键继续..."); 
       getchar();
       getchar();
       system("cls");
       menu(road,park,move,num,t);
    }
}
void outpark(LinkQueue *road,LinkStack *park,LinkStack *move)//停车场出车
{ 
	char num[10],snum[10];
	char t[10],st[10];
	StackNode p=park->top;
	StackNode m=move->top;
	int stay;
	int flag=0;//标记 
	int f=0;//标记 
	int i;
	do
	{	
		flag=0; 
		p=park->top;
		printf("请输入出场汽车车牌：");
		scanf("%s",num);
		while(p!=NULL)
		{	
			if(strcmp(p->data.number,num)==0)//检查停车场里是否已存在相同车牌号的汽车 
				flag=1;
			p=p->next;
		}
		if(flag==0)
		{
			printf("停车场内不存在该车牌，请确认输入的车牌号是否正确！\n");
			printf("按回车键继续...");
			getchar();
			getchar();
			system("cls");
			menu(road,park,move,num,t);
		}
	}while(flag==0);
	while(park->top!=NULL)
	{
		pop(park,snum,st);
		push(move,snum,st);
		if(strcmp(snum,num)==0) 
		{
			pop(move,snum,st);	
			while(1)
			{
				printf("请输入汽车出场时间(格式hh:ss)：");
				scanf("%s",t);
				if((t[0]-'0')>=2 && (t[1]-'0')>3 || t[2]!=':' || (t[3]-'0')>=6 && (t[4]-'0')>=0)
					printf("请按正确的格式输入出场时间！\n");
				else if((t[0]-'0')*10+(t[1]-'0')<=(st[0]-'0')*10+(st[1]-'0') && (t[3]-'0')*10+(t[4]-'0')<(st[3]-'0')*10+(st[4]-'0'))//当出场时间大于入场时间 
					printf("出场时间不得早与入场时间！\n");
				else
					break;
			}
			for(i=0;i<=strlen(vipcar);i++)
			{
				if(strcmp(num,vipcar[i])==0)
				f=1; 
			}
			if(f==1)
			{
				printf("该车为vip车辆，享受八折优惠!\n");
				stay=((t[0]-'0')*10+(t[1]-'0')-(st[0]-'0')*10-(st[1]-'0'))*60+((t[3]-'0')*10+(t[4]-'0')-(st[3]-'0')*10-(st[4]-'0'));//停留时间 
				printf("                          收              据\n");
				printf("================================ 车牌号: %s===============================\n",num);
				printf("=========================================================================\n");
				printf("|进车场时刻         | 出车场时刻         | 停留时间(分钟)    | 应付（元）|\n");
				printf("|    %s          |     %s          |     %d           |       %d\n",st,t,stay,(stay%60?(stay/60)*tick+tick:(stay/60)*tick)*4/5);
				printf("注：不足一小时按一小时计算\n");
				printf("=========================================================================\n");
			}
			else
			{
				stay=((t[0]-'0')*10+(t[1]-'0')-(st[0]-'0')*10-(st[1]-'0'))*60+((t[3]-'0')*10+(t[4]-'0')-(st[3]-'0')*10-(st[4]-'0'));//停留时间 
				printf("                          收              据\n");
				printf("================================ 车牌号: %s===============================\n",num);
				printf("=========================================================================\n");
				printf("|进车场时刻         | 出车场时刻         | 停留时间(分钟)    | 应付（元）|\n");
				printf("|    %s          |     %s          |     %d           |       %d\n",st,t,stay,stay%60?(stay/60)*tick+tick:(stay/60)*tick);
				printf("注：不足一小时按一小时计算\n");
				printf("=========================================================================\n");
			}
			while(move->count)
			{
				pop(move,snum,st);
				push(park,snum,st);
			}
			if(road->front != road->rear )//等候区存在车辆
			{
				outqueue(road,snum,st);	
				push(park,snum,st);
			} 
			printf("请按回车键继续..."); 
			getchar();
       		getchar();
       		system("cls");
       		menu(road,park,move,num,t);
			return;
		}
		
	}
	printf("未找到此车牌的汽车\n");
	printf("请按回车键继续..."); 
       getchar();
       getchar();
       system("cls");
       menu(road,park,move,num,t);
}
void view(LinkQueue *road,LinkStack *park,LinkStack *move)//查看停车场状态 
{
	char num[10];
	char t[10];
	QueueNode r=road->front;
	StackNode p=park->top;
	printf("停车场中有%d辆汽车，车牌号分别是：",park->count); 
	while(p!=NULL)
	{
		if(p->next==NULL)
		printf("%s",p->data.number);
		else
		printf("%s,",p->data.number);
		p=p->next;
	}
	printf("\n");
	printf("等候区中有%d辆汽车，车牌号分别是：",linklength(*road)); 
	while(r->next!=NULL)
	{
		if(r->next->next==NULL)
		printf("%s",r->next->data.number);
		else
		printf("%s,",r->next->data.number);
		r=r->next;
	}
	   printf("\n");
	   printf("请按回车键继续..."); 
       getchar();
       getchar();
       system("cls");
       menu(road,park,move,num,t);
}
void query(LinkQueue *road,LinkStack *park,LinkStack *move)
{
	int s;
	StackNode p=park->top;
	char num[10];
	char t[10];
	printf("1.查询停车场全部车辆入场时间\n");
	printf("2.查询某辆车的入场时间\n");
	printf("0.返回\n"); 
	printf("请输入序号：");
	scanf("%d",&s);
	if(s==1)
	{
		printf("车牌号		入场时间\n");
		while(p!=NULL)
		{
			printf("%s",p->data.number);
			printf("    		");
			printf("%s",p->data.time);
			printf("\n");
			p=p->next;	
		} 
		p=park->top;//初始化 
	}
	else if(s==2)
	{
		printf("请输入查询汽车的车牌号：");
		scanf("%s",num); 
		while(p!=NULL)
		{
			if(strcmp(p->data.number,num)==0)
			{
				printf("入场时间：%s",p->data.time);
				break;
			}
			p=p->next;	
		} 
	}
	else if(s==0)
	{
		system("cls");
		menu(road,park,move,num,t);
	}
	printf("\n");
	printf("请按回车键继续..."); 
    getchar();
    getchar();
    system("cls");
    menu(road,park,move,num,t);
}
void add(LinkQueue *road,LinkStack *park,LinkStack *move)
{
	int s;
	char num[10];
	char t[10];
	int i;
	printf("请输入要新增的车位:");
	scanf("%d",&s);
	parkcount=parkcount+s;
	for(i=0;i<s;i++)
	{
		outqueue(road,num,t);
		push(park,num,t);
	}
	printf("请按回车键继续..."); 
    getchar();
    getchar();
    system("cls");
    menu(road,park,move,num,t);
}
void vip(LinkQueue *road,LinkStack *park,LinkStack *move)
{
	int s;
	int i;
	int flag=0;
	char num[10];
	char t[10];
	printf("1.购买vip	2.查询全部vip车辆	3.查询某辆汽车是否vip\n");
	scanf("%d",&s);
	if(s==1)
	{
		do
		{
			flag=0;
			if(flag==0)
			{
				printf("请输入购买vip的车牌号:");
				scanf("%s",num);
			}
			for(i=0;i<strlen(vip);i++)
			{
				if(strcmp(vipcar[i],num)==0)
				{
					printf("此车牌号已是vip，不可重复购买\n");	
					flag=1;
				}
			}
		}while(flag==1);
		strcpy(vipcar[vipcount],num);
		vipcount++;
		printf("购买成功！\n"); 
		printf("请按回车键继续..."); 
   		getchar();
    	getchar();
    	system("cls");
    	menu(road,park,move,num,t);
	}
	else if(s==2)
	{
		printf("vip车牌号：");
		for(i=0;i<=strlen(vipcar);i++)
		{
			if(i==strlen(vipcar))
			printf("%s",vipcar[i]);
			else
			printf("%s,",vipcar[i]);
		}
		printf("\n");
		printf("请按回车键继续..."); 
   		getchar();
    	getchar();
    	system("cls");
    	menu(road,park,move,num,t);
	}
	else if(s==3)
	{
		printf("请输入待查询的车牌号：");
		scanf("%s",num);
		for(i=0;i<=strlen(vipcar);i++)
		{
			if(strcmp(vipcar[i],num)==0)
			{
				printf("是\n");
				printf("请按回车键继续..."); 
   				getchar();
    			getchar();
    			system("cls");
    			menu(road,park,move,num,t);
				return; 
			}
		}
		printf("否\n");
		printf("请按回车键继续..."); 
   		getchar();
    	getchar();
    	system("cls");
    	menu(road,park,move,num,t);
	} 	
}
void money(LinkQueue *road,LinkStack *park,LinkStack *move)
{
	char num[10];
	char t[10];
	printf("请输入要修改的票价："); 
	scanf("%d",&tick);
	printf("修改成功\n");
	printf("请按回车键继续..."); 
    getchar();
    getchar();
    system("cls");
    menu(road,park,move,num,t);
	
}
int main()
{
	LinkQueue road;//便道 
    LinkStack park;//停车场通道 
    LinkStack move;//移动车辆 
    char num[10];
    char t[10];
    init(&road,&park,&move);
    menu(&road,&park,&move,num,t);
    return 0;
} 
