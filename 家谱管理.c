#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 
typedef struct data{
    char name[20];
    char birthday[20];
	 int sex;//0女生，1男生 
    int marry;//0未婚，1已婚 
    char address[20];
    char death_date[20];
    int generation;//第几代 
}data;
typedef struct node{
    data person;
    struct node *lchild,*rbrother;
}node,*tree;
typedef struct{   //循环队列的定义
    tree queue[100];
    int front,rear;
}queue;
tree BT;
int count=0;
int flag=0;//标记
int countnum(tree T); //计算共有几人 
int BirthdayPreOrderTraverse(tree T);//查找生日前序遍历 
int NamePreOrderTraverse(tree T,char name[20]);//查找姓名前序遍历 
int AddPreOrderTraverse(tree T,char name[20]);//添加孩子前序遍历 
void printfinfo(tree p);//打印结点信息 
void Qinit(queue *Q);//初始化队列 
void inqueue(queue *Q,tree e);//入队
void outqueue(queue *Q,tree *e);//出队
int empty(queue Q);//判队空
int full(queue Q);//判队满
int TreeDepth(tree T);//返回二叉树深度 
void Tinit();//初始化二叉树 
void today_birthday();//显示今天生日的成员 
void show();//显示家谱 
void shownum();//显示第几代人的信息 
void lookupname();// 根据姓名查找成员 
void Addchildren();//为成员添加孩子 
void deletemember();//删除成员 
void modifymember();//修改成员信息 
void determinemember();//确定成员的关系 
void menu();

int countnum(tree T) //计算共有几人 
{
	if (T == NULL)
	{
        return 0;
    }
    else
	{
        count++;
        countnum(T->lchild);
        countnum(T->rbrother);
    }
}
int BirthdayPreOrderTraverse(tree T)//查找生日前序遍历 
{
	time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    int m=0;
    int d=0;
    if (T == NULL)
	{
        return 0;
    }
    else
	{
		m=(T->person.birthday[5]-'0')*10+(T->person.birthday[6]-'0');
		d=(T->person.birthday [8]-'0')*10+(T->person.birthday[9]-'0');
        if(m==1+p->tm_mon && d==p->tm_mday)
        {
        	flag=1;
        	printf("%s ",T->person.name);
		}
        BirthdayPreOrderTraverse(T->lchild);
        BirthdayPreOrderTraverse(T->rbrother);
    }
}

int NamePreOrderTraverse(tree T,char name[20])//查找姓名前序遍历 
{
    if (T == NULL)
	{
        return 0;
    }
    else
	{
        if(strcmp(name,T->person.name)==0)
        {
        	flag=1;
        	printf("此人为家谱第%d代成员，其信息为：\n",T->person.generation);
        	printfinfo(T);
			printf("他的孩子信息为：\n"); 
			if(T->lchild)
			{
				T=T->lchild;
				printfinfo(T);
				while(T->rbrother)
				{
					T=T->rbrother;
					printfinfo(T); 
				}
			}
		}
        NamePreOrderTraverse(T->lchild,name);
        NamePreOrderTraverse(T->rbrother,name);
    }
    
}

int AddPreOrderTraverse(tree T,char name[20])//添加孩子前序遍历 
{
	tree p=(tree)malloc(sizeof(struct node));
	int num;//孩子排行 
	int i;
	if (T == NULL)
	{
        return 0;
    }
    else
	{
        if(strcmp(name,T->person.name)==0)
        {
        	flag=1;
        	printf("请输入添加孩子的排行(从1开始计数)：");
        	scanf("%d",&num);
        	 
        	if(T->lchild)//如果左孩子存在 
        	{
        		p->person.generation=T->person.generation+1;
        		if(num==1)//排行第一代 ，则把结点放在父结点的左孩子 
        		{
        			p->rbrother=T->lchild;
        			T->lchild=p;
				}
				else
				{
					num--;
					T=T->lchild;
        			num--;//排在第几代需取第几代前一代的数 
        			while(T->rbrother && num>0)
        			{
        				T=T->rbrother;
        				num--;
					}
        			p->rbrother=T->rbrother;
        			T->rbrother=p;
				}	
			}
			else//左孩子不存在先创建左孩子 
			{
				p->person.generation=T->person.generation+1;
				T->lchild=p;
			}
        	printf("请输入添加孩子的姓名:");
        	scanf("%s",&p->person.name);
        	do
			{
				if(strlen(p->person.birthday)!=10 && strlen(p->person.birthday)!=0)
				printf("请输入正确的日期格式\n");
        		printf("请输入添加孩子的出生年月(格式形如: 2020-01-01):");
        		scanf("%s",&p->person.birthday);
			} while(strlen(p->person.birthday)!=10); 
        	printf("请输入添加孩子的家庭住址:");
			scanf("%s",&p->person.address);
			printf("请输入添加孩子的婚姻状况 0/1 (0表示未婚，1表示已婚):"); 
			scanf("%d",&p->person.marry);
			printf("请输入添加孩子的去世时间 (在世填0-0-0):");
			scanf("%s",&p->person.death_date); 
			printf("请输入添加孩子的性别 0/1 (0表示女，1表示男):"); 
			scanf("%d",&p->person.sex); 
		}
        AddPreOrderTraverse(T->lchild,name);
        AddPreOrderTraverse(T->rbrother,name);
    }
}

int DeletePreOrderTraverse(tree T,char name[20])//删除孩子前序遍历 
{
	if(strcmp(name,BT->person.name)==0)//删除根节点情况 
	{
		flag=1;
		if(BT->rbrother!=NULL)//根结点不存在右兄弟 
		{
			BT=BT->rbrother;
			return 0; 
		}
		else if(BT->rbrother==NULL)//根节点存在右兄弟 
		{
			BT=NULL;	
			return 0;
		} 
	}
	if (T == NULL)
	{
        return 0;
    }
    else
	{
		if(T->lchild!=NULL)
        if(strcmp(name,T->lchild->person.name)==0)//当前结点的左孩子 
        {
        	flag=1;
        	T->lchild=T->lchild->rbrother;//当前结点左孩子等于左孩子的右兄弟 
		}
		if(T->rbrother!=NULL)
		if(strcmp(name,T->rbrother->person.name)==0)
		{
			flag=1;
			T->rbrother=T->rbrother->rbrother;
		}
        DeletePreOrderTraverse(T->lchild,name);
        DeletePreOrderTraverse(T->rbrother,name);
    }
}

int modifyPreOrderTraverse(tree T,char name[20])//修改成员信息前序遍历
{
	int num;
	if (T == NULL)
	{
        return 0;
    }
    else
	{
        if(strcmp(name,T->person.name)==0)
        {
        	flag=1;
        	printf("请选择要修改%s的哪项数据:\n",T->person.name);
        	printf("1.修改姓名\n");
        	printf("2.修改出生年月\n");
        	printf("3.修改家庭住址\n");
        	printf("4.修改婚姻状况\n");
        	printf("5.修改在世情况\n");
        	printf("6.修改性别\n");
        	printf("7.返回上一级\n");
        	scanf("%d",&num);
			switch(num)
			{
				case 1:
				printf("请输入修改后的姓名：");
				scanf("%s",T->person.name);
				break;
				case 2:
					do
					{
						if(strlen(T->person.birthday)!=10 && strlen(T->person.birthday)!=0)
						printf("请输入正确的日期格式\n");
						printf("请输入修改后的出生年月(格式形如: 2020-01-01)：");
        				scanf("%s",&T->person.birthday);
					} while(strlen(T->person.birthday)!=10); 
				break;
				case 3:
				printf("请输入修改后的家庭住址：");
				scanf("%s",T->person.address);
				break;
				case 4:
				printf("请输入修改后的婚姻状况(0未婚，1已婚)：");
				scanf("%d",&T->person.marry) ;
				break;
				case 5:
				printf("请输入修改后的在世情况(在世填0-0-0)：");
				scanf("%d",&T->person.death_date);
				break;
				case 6:
				printf("请输入修改后的性别(0女生，1男生)：");
				scanf("%d",&T->person.sex);
				break;
				case 7:
				return 0;
			}
			
		}
        modifyPreOrderTraverse(T->lchild,name);
        modifyPreOrderTraverse(T->rbrother,name);
    }
} 

int deterPreOrderTraverse(tree T,char name[20],int *gen)//确定成员的关系前序遍历 
{
	if (T == NULL)
	{
        return 0;
    }
    else
	{
        if(strcmp(name,T->person.name)==0)
        {
			flag=1;	
			*gen=T->person.generation;
		}
        deterPreOrderTraverse(T->lchild,name,gen);
        deterPreOrderTraverse(T->rbrother,name,gen);
    }
}

void printfinfo(tree p)//打印结点信息 
{
			printf("%s  ",p->person.name);
			printf("出生于：%s  ",p->person.birthday);
			printf("%s  ",p->person.address);
			if(p->person.marry==1)
			printf("已婚  ");
			else
			printf("未婚  "); 
			if(p->person.sex==1)
			printf("男  ");
			else
			printf("女  ");
			if(strcmp(p->person.death_date,"0-0-0")==0)
			printf("健在\n");
			else
			printf("死亡日期：%s\n",p->person.death_date);
}
void new_left(tree p,data d)//创建左孩子 
{
    tree q=(tree)malloc(sizeof(node));
    q->person=d;
    q->lchild=q->rbrother=NULL;
    p->lchild=q;
}

void new_right(tree p,data d)//创建右兄弟 
{
    tree q=(tree)malloc(sizeof(node));
    q->person=d;
    q->lchild=q->rbrother=NULL;
    p->rbrother=q;
}

int Generation(tree T)//返回代数 
{
    if(T==NULL)
    return 0;
    if(T)
    return Generation(T->lchild)+1;
}


void Tinit()//初始化二叉树 
{
	data initdata[10]={{"A","1960-06-12",1,1,"厦门集美","2019-10-01",1},
					   {"B","1980-06-12",1,1,"厦门集美","0-0-0",2},
                       {"C","1981-06-18",1,1,"厦门集美","0-0-0",2},
					   {"D","1982-06-12",1,1,"厦门集美","0-0-0",2},
					   {"E","2021-06-12",1,1,"厦门集美","0-0-0",3},
					   {"F","2021-06-12",1,1,"厦门集美","0-0-0",3},
					   {"G","2021-06-12",1,1,"厦门集美","0-0-0",3},
					   {"H","2021-06-12",1,1,"厦门集美","0-0-0",3}, 
					   {"I","2021-06-12",1,1,"厦门集美","0-0-0",3},
					   {"J","2021-06-12",1,1,"厦门集美","0-0-0",3}
					   };
	BT=(tree)malloc(sizeof(node));
	BT->person=initdata[0];
	BT->lchild=BT->rbrother=NULL;
	new_left(BT,initdata[1]);
	new_left(BT->lchild,initdata[4]);
	new_right(BT->lchild->lchild,initdata[5]);
	new_right(BT->lchild->lchild->rbrother,initdata[7]);
	new_right(BT->lchild,initdata[2]);
	new_left(BT->lchild->rbrother,initdata[6]);
	new_right(BT->lchild->rbrother->lchild,initdata[8]);
	new_right(BT->lchild->rbrother,initdata[3]);
	new_left(BT->lchild->rbrother->rbrother,initdata[9]);
}

void today_birthday()//显示今天生日的成员 
{
	flag=0;
	time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
	printf("今天日期是%d-%d，今天生日成员：",1+p->tm_mon,p->tm_mday); 
	BirthdayPreOrderTraverse(BT);
	printf("\n");
	if(flag==0)
	printf("家谱中没有成员过生日\n");
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void show()//显示家谱 
{
	queue *q=(queue *)malloc(sizeof(queue));
	q->front=q->rear=0;
	count=0;
	if(BT!=NULL)//计算BT共有多少人 
	countnum(BT);
	system("cls");
	printf("共计%d代，%d人\n",Generation(BT),count);
	printf("\n");
	int d=1;
	tree p=BT;
	tree n=(tree)malloc(sizeof(struct node));//分隔符 
	strcpy(n->person.name,"NULL");
	n->lchild=n->rbrother=NULL; 
	if(p)
	{
		printf("第1代\n");
		q->queue[q->rear++]=p;//根结点入队 
		while(p->rbrother)//把根结点所有右兄弟入队 
			{
				p=p->rbrother;
				q->queue[q->rear++]=p;
			}
		q->queue[q->rear++]=n;//分隔符入队 
		while(q->front!=q->rear)//队列不为空 
		{
			p=q->queue[q->front++];//取队头结点 
			if(strcmp(p->person.name,"NULL")==0 && q->front!=q->rear)//为分割号表示一代结束 
			{
				printf("第%d代\n",++d);
				q->queue[q->rear++]=n;//加入分割号区分代各代 
			}	
			else if(q->front!=q->rear)
			{
				printfinfo(p);
			}
			if(p->lchild)	//如果左孩子存在 
			{
				p=p->lchild;
				q->queue[q->rear++]=p;//把左孩子所有右兄弟入队，表示一代 
				while(p->rbrother)
				{
					p=p->rbrother;
					q->queue[q->rear++]=p;
				}
			}
		}
	}
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void shownum()//显示第几代人 
{
	int num;
	printf("请输入需要查询的第几代人：");
	scanf("%d",&num); 
	queue *q=(queue *)malloc(sizeof(queue));
	q->front=q->rear=0;
	system("cls");
	int d=1;
	tree p=BT;
	tree n=(tree)malloc(sizeof(struct node));//分隔符 
	strcpy(n->person.name,"NULL");
	n->lchild=n->rbrother=NULL; 
	if(p)
	{
		q->queue[q->rear++]=p;//根结点入队 
		while(p->rbrother)//把根结点所有右兄弟入队 
			{
				p=p->rbrother;
				q->queue[q->rear++]=p;
			}
		q->queue[q->rear++]=n;//分隔符入队 
		while(q->front!=q->rear)//队列不为空 
		{
			p=q->queue[q->front++];//取队头结点 
			if(strcmp(p->person.name,"NULL")==0 && q->front!=q->rear)//为分割号表示一代结束 
			{
				d++;
				q->queue[q->rear++]=n;//加入分割号区分代各代 
			}	
			else if(q->front!=q->rear && num==d)
			{
				printfinfo(p);
			}
			if(p->lchild)	//如果左孩子存在 
			{
				p=p->lchild;
				q->queue[q->rear++]=p;//把左孩子所有右兄弟入队，表示一代 
				while(p->rbrother)
				{
					p=p->rbrother;
					q->queue[q->rear++]=p;
				}
			}
		}
	}
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void Addchildren() //为成员添加孩子 
{
	char name[20];
	printf("请输入要添加孩子成员的姓名：");
	scanf("%s",name); 
	flag=0;
	AddPreOrderTraverse(BT,name);
	if(flag==0)
	printf("没有这个人\n");
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void lookupname()//根据姓名查找成员 
{
	char name[20];
	flag=0; 
	printf("请输入要查询人的姓名:");
	scanf("%s",name);
	NamePreOrderTraverse(BT,name);
	if(flag==0)
	printf("对不起，找不到此人的信息\n");
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void deletemember()//删除成员 
{
	flag=0;
	char name[20];
	printf("请输入要删除成员的姓名："); 
	scanf("%s",name);
	DeletePreOrderTraverse(BT,name);
	if(flag==0)
		printf("对不起，找不到此人的信息\n");
	else
		printf("删除成功！");
		printf("请按回车键继续..."); 
		getchar();
		getchar(); 
		system("cls");
		menu();
	
}

void modifymember()//修改成员信息 
{
	flag=0; 
	char name[20]; 
	printf("请输入要修改人的姓名："); 
	scanf("%s",name);
	modifyPreOrderTraverse(BT,name);
	if(flag==0)
		printf("对不起，找不到此人的信息\n");
	else
		printf("修改成功！\n");
		printf("请按回车键继续..."); 
		getchar();
		getchar(); 
		system("cls");
		menu();
}

void determinemember()//确定成员的关系 
{
	int i;
	int firstgen=0;//第一个人代数 
	int secondgen=0;//第二个人代数 
	char name1[20],name2[20]; 
	flag=0;
	printf("请输入第一个人的姓名：");
	scanf("%s",name1);
	deterPreOrderTraverse(BT,name1,&firstgen);
	if(flag==0)
	printf("家谱无此人，请重新进入！\n");
	else
	{
		flag=0;
		printf("请输入第二个人的姓名：");
		scanf("%s",name2);
		deterPreOrderTraverse(BT,name2,&secondgen);
		if(flag==0)
		printf("家谱无此人，请重新进入！\n");
		else
		if(secondgen>firstgen)
		{
			printf("%s比%s大%d辈\n",name1,name2,secondgen-firstgen);
			for(i=0;i<secondgen-firstgen;i++)
			{
				
			} 
		}
		else if(secondgen<firstgen)
		printf("%s比%s小%d辈\n",name1,name2,firstgen-secondgen);
		else if(secondgen==firstgen)
		printf("%s和%s同辈\n",name1,name2); 
	}
	printf("请按回车键继续..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
	
}

void menu()
{
	int num;
	printf("\n");
	printf("                        欢迎进入家谱管理系统\n");
	printf("            1.显示今天生日成员           2.显示家谱\n");
	printf("            3.显示第n代所有人的信息      4.根据姓名查找成员\n");
	printf("            5.为成员添加孩子             6.删除成员\n");
	printf("            7.修改成员信息               8.确定两个人的关系\n");
	printf("            0.退出程序\n");
	do
	{
		printf("请输入序号：");
		scanf("%d",&num);
		switch(num)
		{
		case 0:
		exit(1);
		case 1:
		today_birthday();
		break;
		case 2:
		show();
		break;
		case 3:
		shownum();
		break;
		case 4:
		lookupname();
		break;
		case 5:
		Addchildren();
		break;
		case 6:
		deletemember();
		break;
		case 7:
		modifymember();
		break;
		case 8:
		determinemember();
		break;	
		default:printf("请输入正确的序号！\n");
		}	
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8);
}
int main()
{
	Tinit();//初始化二叉树 
	menu();
	return 0;
}
