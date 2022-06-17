#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parkcount=0;//��λ���� 
char vipcar[100][10];//���vip���ƺ� 
int vipcount;//vip���� 
int tick=5;
typedef struct Node   //����
{
    char number[10];
    char time[10]; 
}Node;

typedef struct QueueNode   //���н��
{
    struct Node data; //������ 
    struct QueueNode * next;//ָ���� 
}*QueueNode;

typedef struct LinkQueue    //������
{
    struct QueueNode * front;//ͷ 
    struct QueueNode * rear;//β 
}LinkQueue;

typedef struct stack         //ջ���
{
    struct Node data;
    struct stack *next;
}*StackNode;

typedef struct LinkStack     //��ջ
{
    StackNode top;//ջ�� 
    int count;//ջ������ 
}LinkStack;
void menu(LinkQueue *road,LinkStack *park,LinkStack *move,char num[],char t[]);//�˵�
int init(LinkQueue *road,LinkStack *park,LinkStack *move);//��ʼ�� 
int linklength(LinkQueue q);//������г��� 
int inqueue(LinkQueue *q,char num[],char t[]);//��� 
int outqueue(LinkQueue *q,char *num,char *t);//���� 
int push(LinkStack *s,char num[],char t[]);//��ջ 
int pop(LinkStack *s,char *num,char *t);//��ջ 
void inpark(LinkQueue *road,LinkStack *park,LinkStack *move);//ͣ�����복 
void outpark(LinkQueue *road,LinkStack *park,LinkStack *move);//ͣ��������
void view(LinkQueue *road,LinkStack *park,LinkStack *move);//�鿴ͣ����״̬ 
void query(LinkQueue *road,LinkStack *park,LinkStack *move);//��ѯ�����볡ʱ�� 
void add(LinkQueue *road,LinkStack *park,LinkStack *move);//����ͣ������λ 
void vip(LinkQueue *road,LinkStack *park,LinkStack *move);//vipģ�� 
void money(LinkQueue *road,LinkStack *park,LinkStack *move);
void menu(LinkQueue *road,LinkStack *park,LinkStack *move,char num[],char t[])//�˵�
{
	int s;
	do
	{
	printf("                  ** ͣ����������� **\n");
	printf("=========================================================\n");
	printf("**                                                     **\n");
	printf("**       1 --- ����������       2 --- ����������       **\n");
	printf("**       3 --- �鿴ͣ����״̬   4 --- ��ѯ�����볡ʱ�� **\n");
	printf("**       5 --- ����ͣ������λ   6 --- vip              **\n");
	printf("**       7 --- �޸ļ۸�         0 --- �˳�����         **\n");
	printf("**                                                     **\n");
	printf("**           ͣ����ʣ��%-1d��λ��ÿСʱ�շ�%dԪ            **\n",parkcount-park->count,tick);
	printf("=========================================================\n");
	printf("��������ţ�");
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
		printf("��������ȷ����ţ�\n");
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
    node->next = NULL;//��ʼ���ȴ����� 
    road->front = node;
    road->rear = node;

    move->top = NULL;//��ʼ���ƶ�����ջ 
    move->count = 0;	
    park->top=NULL;//��ʼ��ͣ��ջ 
    park->count=0;
}
int linklength(LinkQueue q)//������г��� 
{
    int i = 0;
    while(q.front != q.rear)
    {
        i++;
        q.front = q.front->next;
    }
    return i;
}
int inqueue(LinkQueue *q,char num[],char t[])//��� 
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

int outqueue(LinkQueue *q,char *num,char *t)//���� 
{
    if(q->front == q->rear)
    {
        return 0;
    }
    strcpy(num,q->front->next->data.number);
    strcpy(t,q->front->next->data.time);
    QueueNode temp = q->front->next;//��Ŵ�ɾ�����ĵ�ַ 
    q->front->next = q->front->next->next;
    if(temp->next == NULL)//ֻʣ��ͷβ�������������ɾ��β��㣬��ͷβָ�붼ָ��ͷ��� 
    {
        q->rear = q->front;
    }
    free(temp);
    return 1;
}
int push(LinkStack *s,char num[],char t[])//��ջ 
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

int pop(LinkStack *s,char *num,char *t)//��ջ 
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
void inpark(LinkQueue *road,LinkStack *park,LinkStack *move)//ͣ�����복 
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
		printf("�������볡�����ĳ��ƺţ�");
		scanf("%s",num);
		while(p!=NULL)
		{	
			if(strcmp(p->data.number,num)==0)//���ͣ�������Ƿ��Ѵ�����ͬ���ƺŵ����� 
			{
				flag=1;
				printf("ͣ�����Ѵ�����ͬ���ƺŵ����������鳵�ƺ������Ƿ���ȷ��\n");
			}
			p=p->next;
		}
		while(r->next!=NULL)
		{
			if(strcmp(r->next->data.number,num)==0)//���ͣ�������Ƿ��Ѵ�����ͬ���ƺŵ����� 
			{
				flag=1;
				printf("�Ⱥ����Ѵ�����ͬ���ƺŵ����������鳵�ƺ������Ƿ���ȷ��\n");
			}
			r=r->next;
		}
	}while(flag==1);
		while(1)
			{
				printf("�����������볡ʱ��(��ʽhh:ss)��");
				scanf("%s",t);
				if((t[0]-'0')>=2 && (t[1]-'0')>3 || t[2]!=':' || (t[3]-'0')>=6&& (t[4]-'0')>=0)
					printf("�밴��ȷ�ĸ�ʽ�����볡ʱ�䣡\n");
				else
					break;
			}
	if( park->count >=parkcount)//ͣ�����ڳ���ͣ�� 
    {
        printf("ͣ��������������ȴ�����\n");
        inqueue(road,num,t);//�������Ⱥ��� 
    	printf("�밴���������..."); 
       	getchar();
       	getchar();
      	system("cls");
       	menu(road,park,move,num,t);
    }
    else
    {
       push(park,num,t);//��ջ 
       printf("�ó��ѽ���ͣ����%d�ų���\n",park->count); 
       printf("�밴�س�������..."); 
       getchar();
       getchar();
       system("cls");
       menu(road,park,move,num,t);
    }
}
void outpark(LinkQueue *road,LinkStack *park,LinkStack *move)//ͣ��������
{ 
	char num[10],snum[10];
	char t[10],st[10];
	StackNode p=park->top;
	StackNode m=move->top;
	int stay;
	int flag=0;//��� 
	int f=0;//��� 
	int i;
	do
	{	
		flag=0; 
		p=park->top;
		printf("����������������ƣ�");
		scanf("%s",num);
		while(p!=NULL)
		{	
			if(strcmp(p->data.number,num)==0)//���ͣ�������Ƿ��Ѵ�����ͬ���ƺŵ����� 
				flag=1;
			p=p->next;
		}
		if(flag==0)
		{
			printf("ͣ�����ڲ����ڸó��ƣ���ȷ������ĳ��ƺ��Ƿ���ȷ��\n");
			printf("���س�������...");
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
				printf("��������������ʱ��(��ʽhh:ss)��");
				scanf("%s",t);
				if((t[0]-'0')>=2 && (t[1]-'0')>3 || t[2]!=':' || (t[3]-'0')>=6 && (t[4]-'0')>=0)
					printf("�밴��ȷ�ĸ�ʽ�������ʱ�䣡\n");
				else if((t[0]-'0')*10+(t[1]-'0')<=(st[0]-'0')*10+(st[1]-'0') && (t[3]-'0')*10+(t[4]-'0')<(st[3]-'0')*10+(st[4]-'0'))//������ʱ������볡ʱ�� 
					printf("����ʱ�䲻�������볡ʱ�䣡\n");
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
				printf("�ó�Ϊvip���������ܰ����Ż�!\n");
				stay=((t[0]-'0')*10+(t[1]-'0')-(st[0]-'0')*10-(st[1]-'0'))*60+((t[3]-'0')*10+(t[4]-'0')-(st[3]-'0')*10-(st[4]-'0'));//ͣ��ʱ�� 
				printf("                          ��              ��\n");
				printf("================================ ���ƺ�: %s===============================\n",num);
				printf("=========================================================================\n");
				printf("|������ʱ��         | ������ʱ��         | ͣ��ʱ��(����)    | Ӧ����Ԫ��|\n");
				printf("|    %s          |     %s          |     %d           |       %d\n",st,t,stay,(stay%60?(stay/60)*tick+tick:(stay/60)*tick)*4/5);
				printf("ע������һСʱ��һСʱ����\n");
				printf("=========================================================================\n");
			}
			else
			{
				stay=((t[0]-'0')*10+(t[1]-'0')-(st[0]-'0')*10-(st[1]-'0'))*60+((t[3]-'0')*10+(t[4]-'0')-(st[3]-'0')*10-(st[4]-'0'));//ͣ��ʱ�� 
				printf("                          ��              ��\n");
				printf("================================ ���ƺ�: %s===============================\n",num);
				printf("=========================================================================\n");
				printf("|������ʱ��         | ������ʱ��         | ͣ��ʱ��(����)    | Ӧ����Ԫ��|\n");
				printf("|    %s          |     %s          |     %d           |       %d\n",st,t,stay,stay%60?(stay/60)*tick+tick:(stay/60)*tick);
				printf("ע������һСʱ��һСʱ����\n");
				printf("=========================================================================\n");
			}
			while(move->count)
			{
				pop(move,snum,st);
				push(park,snum,st);
			}
			if(road->front != road->rear )//�Ⱥ������ڳ���
			{
				outqueue(road,snum,st);	
				push(park,snum,st);
			} 
			printf("�밴�س�������..."); 
			getchar();
       		getchar();
       		system("cls");
       		menu(road,park,move,num,t);
			return;
		}
		
	}
	printf("δ�ҵ��˳��Ƶ�����\n");
	printf("�밴�س�������..."); 
       getchar();
       getchar();
       system("cls");
       menu(road,park,move,num,t);
}
void view(LinkQueue *road,LinkStack *park,LinkStack *move)//�鿴ͣ����״̬ 
{
	char num[10];
	char t[10];
	QueueNode r=road->front;
	StackNode p=park->top;
	printf("ͣ��������%d�����������ƺŷֱ��ǣ�",park->count); 
	while(p!=NULL)
	{
		if(p->next==NULL)
		printf("%s",p->data.number);
		else
		printf("%s,",p->data.number);
		p=p->next;
	}
	printf("\n");
	printf("�Ⱥ�������%d�����������ƺŷֱ��ǣ�",linklength(*road)); 
	while(r->next!=NULL)
	{
		if(r->next->next==NULL)
		printf("%s",r->next->data.number);
		else
		printf("%s,",r->next->data.number);
		r=r->next;
	}
	   printf("\n");
	   printf("�밴�س�������..."); 
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
	printf("1.��ѯͣ����ȫ�������볡ʱ��\n");
	printf("2.��ѯĳ�������볡ʱ��\n");
	printf("0.����\n"); 
	printf("��������ţ�");
	scanf("%d",&s);
	if(s==1)
	{
		printf("���ƺ�		�볡ʱ��\n");
		while(p!=NULL)
		{
			printf("%s",p->data.number);
			printf("    		");
			printf("%s",p->data.time);
			printf("\n");
			p=p->next;	
		} 
		p=park->top;//��ʼ�� 
	}
	else if(s==2)
	{
		printf("�������ѯ�����ĳ��ƺţ�");
		scanf("%s",num); 
		while(p!=NULL)
		{
			if(strcmp(p->data.number,num)==0)
			{
				printf("�볡ʱ�䣺%s",p->data.time);
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
	printf("�밴�س�������..."); 
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
	printf("������Ҫ�����ĳ�λ:");
	scanf("%d",&s);
	parkcount=parkcount+s;
	for(i=0;i<s;i++)
	{
		outqueue(road,num,t);
		push(park,num,t);
	}
	printf("�밴�س�������..."); 
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
	printf("1.����vip	2.��ѯȫ��vip����	3.��ѯĳ�������Ƿ�vip\n");
	scanf("%d",&s);
	if(s==1)
	{
		do
		{
			flag=0;
			if(flag==0)
			{
				printf("�����빺��vip�ĳ��ƺ�:");
				scanf("%s",num);
			}
			for(i=0;i<strlen(vip);i++)
			{
				if(strcmp(vipcar[i],num)==0)
				{
					printf("�˳��ƺ�����vip�������ظ�����\n");	
					flag=1;
				}
			}
		}while(flag==1);
		strcpy(vipcar[vipcount],num);
		vipcount++;
		printf("����ɹ���\n"); 
		printf("�밴�س�������..."); 
   		getchar();
    	getchar();
    	system("cls");
    	menu(road,park,move,num,t);
	}
	else if(s==2)
	{
		printf("vip���ƺţ�");
		for(i=0;i<=strlen(vipcar);i++)
		{
			if(i==strlen(vipcar))
			printf("%s",vipcar[i]);
			else
			printf("%s,",vipcar[i]);
		}
		printf("\n");
		printf("�밴�س�������..."); 
   		getchar();
    	getchar();
    	system("cls");
    	menu(road,park,move,num,t);
	}
	else if(s==3)
	{
		printf("���������ѯ�ĳ��ƺţ�");
		scanf("%s",num);
		for(i=0;i<=strlen(vipcar);i++)
		{
			if(strcmp(vipcar[i],num)==0)
			{
				printf("��\n");
				printf("�밴�س�������..."); 
   				getchar();
    			getchar();
    			system("cls");
    			menu(road,park,move,num,t);
				return; 
			}
		}
		printf("��\n");
		printf("�밴�س�������..."); 
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
	printf("������Ҫ�޸ĵ�Ʊ�ۣ�"); 
	scanf("%d",&tick);
	printf("�޸ĳɹ�\n");
	printf("�밴�س�������..."); 
    getchar();
    getchar();
    system("cls");
    menu(road,park,move,num,t);
	
}
int main()
{
	LinkQueue road;//��� 
    LinkStack park;//ͣ����ͨ�� 
    LinkStack move;//�ƶ����� 
    char num[10];
    char t[10];
    init(&road,&park,&move);
    menu(&road,&park,&move,num,t);
    return 0;
} 
