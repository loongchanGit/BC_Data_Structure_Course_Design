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
	data vexs[max];//��� 
	int arcs[max][max];//�ڽӾ��� 
	int vexnum,arcnum;//����������� 
}MGrapt; 
int DFSvisited[max]={0};//�����ʱ�� 
int DFSsave[max]={0}; 
int djsave[max];
int count;
int shortlength[max];
int primqueue[max]={0};
int s;
MGrapt TG;//����ͼ
int Infinity=65536;//����� 
void initG();// ��ʼ��ͼ
void menu();//��ʾ�˵� 
void queryinfo();//������Ϣ��ѯ 
void addinfo();//����������Ϣ 
void modifyinfo();//�޸ľ���͵�·��Ϣ
void deleteinfo();//ɾ������͵�·��Ϣ
void Pathquery();//�����������·����ѯ
void onetoallpath();//��һ�������е����·��
void twopath();//������֮������·�� 
void netting();//��Ѳ������� 
void ergodic();// ������һ���߱�ȫУ���·�� 
void initG()// ��ʼ��ͼ
{
	int i,j; 
	TG.vexnum=14;//14����� 
 	TG.arcnum=20;//20����
	data temp[100]={{1,"����","�����Ǳ���"},
					{2,"һ��ʳ��","������һ��ʳ��"}, 
					{3,"�ɲٳ�","�����Ǿɲٳ�"},
					{4,"����9","����������9"},
					{5,"��ѧԷ","�����ǲ�ѧԷ"},
					{6,"��������","��������������"},
					{7,"ҽ����","������ҽ����"},
					{8,"�綴ʵ����","�����Ƿ綴ʵ����"},
					{9,"���´�ҵ԰","�����Ǵ��´�ҵ԰"},
					{10,"�����ѧԺ","�����Ǽ��������Ϣ����ѧԺ"},
					{11,"����ѧԺ","�����ǲ��Ͽ�ѧ�빤��ѧԺ"},
					{12,"ͼ���","������ͼ���"},
					{13,"�²ٳ�","�������²ٳ�"},
					{14,"������","������������"},
				   };
	for(i=0;i<TG.vexnum;i++)
		TG.vexs[i]=temp[i];
	for(i=0;i<TG.vexnum;i++)
		TG.arcs[i][i]=Infinity;
	for(i=0;i<max;i++)//�ڽӾ�������Ԫ�س�ʼ��Ϊ����� ����·����Ϊ����� 
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
		printf("************��ӭʹ��������ѧԺ������ѯϵͳ***********");
		printf("\n");
		printf("	1.������Ϣ��ѯ\n");
		printf("	2.����������Ϣ\n");
		printf("	3.�޸ľ���͵�·��Ϣ\n");
		printf("	4.ɾ������͵�·��Ϣ\n");
		printf("	5.�������������·����ѯ\n");
		printf("	6.��һ�����㵽���о�������·��\n");
		printf("	7.��������������֮������·��\n");
		printf("	8.��Ѳ�������\n");
		printf("	0.�˳�ϵͳ\n");
		printf("*******************************************************\n");
		printf("��������ţ�");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8)
		{	
			system("cls"); 
			printf("��������ȷ����ţ�");		
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

void queryinfo()//������Ϣ��ѯ 
{
	int num;
	int i,j;
	int flag=0;
	char name[20];
	system("cls");
	do
	{
		printf("\n");
		printf("          1�����վ����Ų�ѯ\n");
		printf("          2�����վ������Ʋ�ѯ\n");
		printf("          3���г����о���͵�·��Ϣ\n");
		printf("          0��������һ��\n");
		printf("��������ţ�");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3 )
		{	
			system("cls"); 
			printf("��������ȷ����ţ�");		
		}
	}while(num!=0 && num!=1 && num!=2 && num!=3);
	if(num==1)
	{
		flag=0;
		printf("�����뾰���ţ�");
		scanf("%d",&num);
		for(i=0;i<TG.vexnum;i++)
		{
			if(TG.vexs[i].num==num)
			{
				flag=1;
				printf("�����ţ�%d\n",TG.vexs[i].num);
				printf("�������ƣ�%s\n",TG.vexs[i].name);
				printf("������ܣ�%s\n",TG.vexs[i].info);
				printf("\n");
				printf("�þ���·����Ϣ��\n");
				for(j=0;j<TG.vexnum;j++)
				{
					if(TG.arcs[i][j]!=Infinity)					
						printf("������%d--%s�ľ���Ϊ%d\n",TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
				}
			}
		}
		if(flag==0)
		printf("�Բ����޴˱�ţ�"); 
		getchar();
		getchar();
		system("cls");
		queryinfo();
	}
	else if(num==2)
	{
		flag=0;
		printf("�����뾰�����ƣ�");
		scanf("%s",name);
		for(i=0;i<TG.vexnum;i++)
		{
			if(strcmp(name,TG.vexs[i].name)==0)
			{
				flag=1;
				printf("�����ţ�%d\n",TG.vexs[i].num);
				printf("�������ƣ�%s\n",TG.vexs[i].name);
				printf("������ܣ�%s\n",TG.vexs[i].info);
				printf("\n");
				printf("�þ���·����Ϣ��\n");
				for(j=0;j<TG.vexnum;j++)
				{
					if(TG.arcs[i][j]!=Infinity)					
						printf("������%d--%s�ľ���Ϊ%d\n",TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
				}
			}
		}
		if(flag==0)
		printf("�Բ����޴����ƣ�"); 
		getchar();
		getchar();
		system("cls");
		queryinfo();
	}
	else if(num==3)
	{
		printf("������	��������	�������\n");
		for(i=0;i<TG.vexnum;i++)
		printf("%-16d%-16s%s\n",TG.vexs[i].num,TG.vexs[i].name,TG.vexs[i].info);
		printf("\n");
		printf("��·��Ϣ��\n");
		for(i=0;i<TG.vexnum;i++)
		{
			for(j=i;j<TG.vexnum;j++)
			{
				if(TG.arcs[i][j]!=Infinity)
				printf("����%d--%s�;���%d--%s���ڵ�·������Ϊ%d\n",TG.vexs[i].num,TG.vexs[i].name,TG.vexs[j].num,TG.vexs[j].name,TG.arcs[i][j]);
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

void addinfo()//����������Ϣ 
{
	int num;
	char name[20];
	char info[50];
	int flag=0;
	int i;
	printf("������������ľ�����Ϣ��\n");
	do
	{
		printf("�����ţ�");
		scanf("%d",&num);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==num)	
			flag=1;				
		if(flag==1)
		{
			printf("�ñ���Ѵ��ڣ�"); 
			getchar();
			getchar();
			system("cls");
			menu();
		}
	}while(flag==1); 
	printf("�������ƣ�");
	scanf("%s",name);
	printf("������ܣ�");
	scanf("%s",info); 
	TG.vexs[TG.vexnum].num=num;
	strcpy(TG.vexs[TG.vexnum].name,name);
	strcpy(TG.vexs[TG.vexnum].info,info);
	TG.vexnum++;
	printf("����������Ϣ�ɹ���"); 
	getchar();
	getchar();
	system("cls");
	menu();
}

void modifyinfo()//�޸ľ���͵�·��Ϣ
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
		printf("          1�����뾰�����޸ľ�����Ϣ\n");
		printf("          2�����뾰�������޸ľ�����Ϣ\n");
		printf("          3���޸�·����Ϣ����ԭ��·��������\n");
		printf("          0��������һ��\n");
		printf("��������ţ�");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3)
		{	
			system("cls"); 
			printf("��������ȷ����ţ�");		
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
			printf("�����뾰���ţ�");
			scanf("%d",&num);
			for(i=0;i<TG.vexnum;i++)
			if(TG.vexs[i].num==num)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("�Բ����޴˱�ţ�"); 
				getchar();
				getchar();
				system("cls");
				modifyinfo();
			}
		}while(flag==0); 
		printf("�������޸ĺ�����ƣ�");
		scanf("%s",name);
		strcpy(TG.vexs[x].name,name);
		printf("�������޸ĺ�Ľ��ܣ�"); 
		scanf("%s",info);
		strcpy(TG.vexs[x].info,info);
		printf("������Ϣ�޸ĳɹ���"); 
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
			printf("�����뾰�����ƣ�");
			scanf("%s",name);
			for(i=0;i<TG.vexnum;i++)
			if(strcmp(TG.vexs[i].name,name)==0)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("�Բ����޴����ƣ�"); 
				getchar();
				getchar();
				system("cls");
				modifyinfo();
			}
		}while(flag==0); 
		printf("�������޸ĺ�����ƣ�");
		scanf("%s",name);
		strcpy(TG.vexs[x].name,name);
		printf("�������޸ĺ�Ľ��ܣ�"); 
		scanf("%s",info);
		strcpy(TG.vexs[x].info,info);
		printf("������Ϣ�޸ĳɹ���"); 
		getchar();
		getchar();
		system("cls");
		modifyinfo();
	}
	else if(num==3)
	{
		flag=0;
		printf("��������޸ĵ�·����Ϣ������·��������\n");
		printf("��ʽ����(1-2,60),��ʾ��� 1 2��·������60��\n");
		scanf("%d-%d,%d",&first,&second,&length);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==first)
		{
			x=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("����ı�Ų����ڣ�");
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
			printf("����ı�Ų����ڣ�");
			getchar();
			getchar();
			system("cls");
			modifyinfo();
		}
		TG.arcs[x][y]=length;
		TG.arcs[y][x]=length;
		printf("�޸���Ϣ�ɹ���"); 
		getchar();
		getchar();
		system("cls");
		modifyinfo();
	}
}

void deleteinfo()//ɾ������͵�·��Ϣ
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
		printf("          1�����뾰����ɾ��������Ϣ\n");
		printf("          2�����뾰������ɾ��������Ϣ\n");
		printf("          3��ɾ����·��Ϣ\n");
		printf("          0��������һ��\n");
		printf("��������ţ�");
		scanf("%d",&num);
		if(num!=0 && num!=1 && num!=2 && num!=3)
		{	
			system("cls"); 
			printf("��������ȷ����ţ�");		
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
			printf("�����뾰���ţ�");
			scanf("%d",&num);
			for(i=0;i<TG.vexnum;i++)
			if(TG.vexs[i].num==num)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("�Բ����޴˱�ţ�"); 
				getchar();
				getchar();
				system("cls");
				deleteinfo();
			}
		}while(flag==0); 
		for(i=x;i<TG.vexnum;i++)
		TG.vexs[i]=TG.vexs[i+1];
		TG.vexnum--;
		printf("����ɾ���ɹ���");
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
			printf("�����뾰�����ƣ�");
			scanf("%s",name);
			for(i=0;i<TG.vexnum;i++)
			if(strcmp(TG.vexs[i].name,name)==0)	
			{
				x=i;
				flag=1;	
			}				
			if(flag==0)
			{
				printf("�Բ����޴����ƣ�"); 
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
		printf("�������ɾ����·����Ϣ\n");
		printf("��ʽ����(1-2),��ʾ��� 1 2\n");
		scanf("%d-%d,%d",&first,&second);
		for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==first)
		{
			x=i;
			flag=1;
		}
		if(flag==0)
		{
			printf("����ı�Ų����ڣ�");
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
			printf("����ı�Ų����ڣ�");
			getchar();
			getchar();
			system("cls");
			deleteinfo();
		}
		TG.arcs[x][y]=Infinity;
		TG.arcs[y][x]=Infinity;
		printf("ɾ���ɹ���"); 
		getchar();
		getchar();
		system("cls");
		deleteinfo();
	}
}

void DFS(int m,int start, int end)//���� 
{
    int i,j; 
    for(i = 0; i < TG.vexnum; i++)
	{
        if(TG.arcs[start][i] !=Infinity && DFSvisited[i] == 0)//��ʼ��㵽i����·����iδ������ 
		{
            DFSvisited[i] = 1;
            if(i == end)//����Ŀ����ʱ��ӡ 
			{
                count++;
                printf("��%d.",count);
                for(j = 0; j < m; j++) 
				{
                    printf("%s->", TG.vexs[DFSsave[j]].name);
                }
                printf("%s\n", TG.vexs[end].name);
                DFSvisited[i] = 0;
            }
            else //������洢��� 
			{
                DFSsave[m] = i;
                m++;
                DFS(m,i, end);
                m--;
                DFSvisited[i] = 0;//�ݹ������·�������н���ʼ��Ϊδ���� 
            }
        }
    }
}

void Pathquery()//�����������·����ѯ
{
	int flag=0; 
	int start,end;
	int x,y;
	int i;
	for(i=0;i<TG.vexnum;i++)//��ʼ������ 
	{
		DFSvisited[i]=0;
		DFSsave[i]=0;	
	}
	printf("��������ʼ�����ź��յ㾰���ţ��ÿո������");
	scanf("%d %d",&start,&end);
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==start)
	{
		flag=1;
		x=i;
	}
	if(flag==0)
	{
		printf("����ı�Ų����ڣ�");
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
		printf("����ı�Ų����ڣ�");
		getchar();
		getchar();
		system("cls");
		menu(); 
	}
	DFSsave[0]=x;//��ʼ��� 
	DFSvisited[x]=1;
	DFS(1,x,y);
	getchar();
	getchar();
	system("cls");
	menu(); 
}



void onetoallpath()//��һ�������е����·��
{
	int start;
	int i,j;
	int flag=0;
	int x=0;
	int stack[max]={-1};
	int s=0;
	printf("��������ʼ�����ţ�");
	scanf("%d",&start);
	for(i=0;i<TG.vexnum;i++)
	if(TG.vexs[i].num==start)
	{
		flag=1;
		x=i;
	}
	if(flag==0)
	{
		printf("����ı�Ų����ڣ�"); 
		getchar();
		getchar();
		system("cls");
		menu();
	}
	Dijkstra(x);
	printf("%s���������������̾������£�\n",TG.vexs[x].name);
	for(i=0;i<TG.vexnum;i++)
	{
		if(i!=x)
		{
			s=0;
			stack[0]=djsave[i]; //�յ��ǰһ������±�ֵ�������� 
			printf("%s->",TG.vexs[x].name);
			/*for(i=0;i<TG.vexnum;i++)
			printf("%d��",djsave[i]);*/
			for(j=1;j<TG.vexnum;j++)
			{
			stack[j]=djsave[stack[j-1]];//ÿ�δ洢��һ������ǰһ������±� 
			}
			for(j=0;j<TG.vexnum;j++)
			{
			if(stack[j]==-1) 
			break;
			s++;//���㹲�ж��ٽ�㣨��������ʼ�ͽ�����
			}
			for(j=s-1;j>=0;j--)
			printf("%s->",TG.vexs[stack[j]].name);
			printf("%s\n",TG.vexs[i].name);
			printf("����Ϊ��%dm\n",shortlength[i]);
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
	for(i=0;i<TG.vexnum;i++)//��¼��������ڽӽ��Ȩֵ 
	{
		shortlength[i]=TG.arcs[start][i];
		visited[i]=0;//��ʼ��Ϊδ���� 
		djsave[i]=-1;
	}
	shortlength[start]=0;
	visited[start]=1;//��ʼ������ѷ��� 
	for(i=0;i<TG.vexnum;i++)
	{
		k=-1;
		min=Infinity;
		for(j=0;j<TG.vexnum;j++)//�ҳ����·�� 
		{
			if(visited[j]==0 && shortlength[j]<min)//j���δ�����ʣ���㵽j����ȨֵС����Сֵ 
			{
				min=shortlength[j];
				k=j;	
			}
		}
		visited[k]=1;
		
		for(j=0;j<TG.vexnum;j++)
		{
			if(visited[j]==0 && TG.arcs[k][j]+shortlength[k]<shortlength[j])//�������·�� 
			{
				shortlength[j]=TG.arcs[k][j]+shortlength[k];
				djsave[j]=k;
			}
			
		} 
	}
}

void twopath()//������֮������·�� 
{
	int flag=0; 
	int start,end;
	int x=0,y=0;
	int i=0;
	int stack[max]={-1};
	int s=0;
	printf("��������ʼ�����ź��յ㾰���ţ��ÿո������");
	scanf("%d %d",&start,&end);
	if(start==end)
	{
		printf("�����յ㲻����ͬ��");
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
		printf("����ı�Ų����ڣ�");
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
		printf("����ı�Ų����ڣ�");
		getchar();
		getchar();
		system("cls");
		menu();
	}
	Dijkstra(x);
	printf("��%s��%s�����·���ǣ�\n",TG.vexs[x].name,TG.vexs[y].name);
	stack[0]=djsave[y]; //�յ��ǰһ������±�ֵ�������� 
	printf("%s->",TG.vexs[x].name);
	/*for(i=0;i<TG.vexnum;i++)
	printf("%d��",djsave[i]);*/
	for(i=1;i<TG.vexnum;i++)
	{
		stack[i]=djsave[stack[i-1]];//ÿ�δ洢��һ������ǰһ������±� 
	}
	for(i=0;i<TG.vexnum;i++)
	{
		if(stack[i]==-1) 
		break;
		s++;//���㹲�ж��ٽ�㣨��������ʼ�ͽ����� 
	}
	for(i=s-2;i>=0;i--)
	printf("%s->",TG.vexs[stack[i]].name);
	printf("%s\n",TG.vexs[y].name);
	printf("����Ϊ��%dm",shortlength[y]);
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
    s=0;//ȫ�ֱ��� 
    for(i=0;i<TG.vexnum;i++)
    {
    	if(i!=start)
    	{
    		primqueue[i]=start;
    		lowcost[i]=TG.arcs[start][i];//��1�����ڽӽ���Ӧ��Ȩֵ��¼����
		}
	}
        
    //lowcost[start]=0;//1��㸳ֵΪ0��ʾ�ѷ���
    for(i=0;i<TG.vexnum-1;i++)
    {
        min=99999;
        j=0;
        k=0;
        while(j<TG.vexnum)
        {
            if(lowcost[j]!=0 && lowcost[j]<min)//�ҳ�Ȩֵ���µ��Ҽ�¼���±�
            {
                min=lowcost[j];
                k=j;
            }
            j++;
        }
        cost=cost+min;//����С���Ȩֵ����
        printf("	��%s---%s:%d m\n", TG.vexs[primqueue[k]].name,TG.vexs[k].name,lowcost[k]);
        //printf("%d\n",cost);
        lowcost[k]=0;//�ý����Ϊ�ѷ���
       // primqueue[s++]=k;
        for(j=0;j<TG.vexnum;j++)//���¶��㼯����������·��
        {
            if(j!=k && lowcost[j]!=0 && TG.arcs[k][j]<lowcost[j])//�ѷ��ʵĽ��Ͳ���Ҫ�ҵ��ý������·��
            {
            	lowcost[j]=TG.arcs[k][j];
            	primqueue[j]=k;
			}
                
        }
    }
    return cost;
}

void netting()// ������һ���߱�ȫУ���·��
{
	int start; 
	int i;
	int x;
	int flag=0;
	int length=0;
	printf("�����뾰���ţ�");
	scanf("%d",&start);
	for(i=0;i<TG.vexnum;i++)
		if(TG.vexs[i].num==start)
		{
			flag=1;
			x=i;
		}
	if(flag==0)
	{
		printf("����ı�Ų����ڣ�");
		getchar();
		getchar();
		system("cls");
		menu();
	}
	length=prim(x);
	printf("	�ܳ���Ϊ��%dm ",length);
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
