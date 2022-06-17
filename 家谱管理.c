#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 
typedef struct data{
    char name[20];
    char birthday[20];
	 int sex;//0Ů����1���� 
    int marry;//0δ�飬1�ѻ� 
    char address[20];
    char death_date[20];
    int generation;//�ڼ��� 
}data;
typedef struct node{
    data person;
    struct node *lchild,*rbrother;
}node,*tree;
typedef struct{   //ѭ�����еĶ���
    tree queue[100];
    int front,rear;
}queue;
tree BT;
int count=0;
int flag=0;//���
int countnum(tree T); //���㹲�м��� 
int BirthdayPreOrderTraverse(tree T);//��������ǰ����� 
int NamePreOrderTraverse(tree T,char name[20]);//��������ǰ����� 
int AddPreOrderTraverse(tree T,char name[20]);//��Ӻ���ǰ����� 
void printfinfo(tree p);//��ӡ�����Ϣ 
void Qinit(queue *Q);//��ʼ������ 
void inqueue(queue *Q,tree e);//���
void outqueue(queue *Q,tree *e);//����
int empty(queue Q);//�жӿ�
int full(queue Q);//�ж���
int TreeDepth(tree T);//���ض�������� 
void Tinit();//��ʼ�������� 
void today_birthday();//��ʾ�������յĳ�Ա 
void show();//��ʾ���� 
void shownum();//��ʾ�ڼ����˵���Ϣ 
void lookupname();// �����������ҳ�Ա 
void Addchildren();//Ϊ��Ա��Ӻ��� 
void deletemember();//ɾ����Ա 
void modifymember();//�޸ĳ�Ա��Ϣ 
void determinemember();//ȷ����Ա�Ĺ�ϵ 
void menu();

int countnum(tree T) //���㹲�м��� 
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
int BirthdayPreOrderTraverse(tree T)//��������ǰ����� 
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

int NamePreOrderTraverse(tree T,char name[20])//��������ǰ����� 
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
        	printf("����Ϊ���׵�%d����Ա������ϢΪ��\n",T->person.generation);
        	printfinfo(T);
			printf("���ĺ�����ϢΪ��\n"); 
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

int AddPreOrderTraverse(tree T,char name[20])//��Ӻ���ǰ����� 
{
	tree p=(tree)malloc(sizeof(struct node));
	int num;//�������� 
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
        	printf("��������Ӻ��ӵ�����(��1��ʼ����)��");
        	scanf("%d",&num);
        	 
        	if(T->lchild)//������Ӵ��� 
        	{
        		p->person.generation=T->person.generation+1;
        		if(num==1)//���е�һ�� ����ѽ����ڸ��������� 
        		{
        			p->rbrother=T->lchild;
        			T->lchild=p;
				}
				else
				{
					num--;
					T=T->lchild;
        			num--;//���ڵڼ�����ȡ�ڼ���ǰһ������ 
        			while(T->rbrother && num>0)
        			{
        				T=T->rbrother;
        				num--;
					}
        			p->rbrother=T->rbrother;
        			T->rbrother=p;
				}	
			}
			else//���Ӳ������ȴ������� 
			{
				p->person.generation=T->person.generation+1;
				T->lchild=p;
			}
        	printf("��������Ӻ��ӵ�����:");
        	scanf("%s",&p->person.name);
        	do
			{
				if(strlen(p->person.birthday)!=10 && strlen(p->person.birthday)!=0)
				printf("��������ȷ�����ڸ�ʽ\n");
        		printf("��������Ӻ��ӵĳ�������(��ʽ����: 2020-01-01):");
        		scanf("%s",&p->person.birthday);
			} while(strlen(p->person.birthday)!=10); 
        	printf("��������Ӻ��ӵļ�ͥסַ:");
			scanf("%s",&p->person.address);
			printf("��������Ӻ��ӵĻ���״�� 0/1 (0��ʾδ�飬1��ʾ�ѻ�):"); 
			scanf("%d",&p->person.marry);
			printf("��������Ӻ��ӵ�ȥ��ʱ�� (������0-0-0):");
			scanf("%s",&p->person.death_date); 
			printf("��������Ӻ��ӵ��Ա� 0/1 (0��ʾŮ��1��ʾ��):"); 
			scanf("%d",&p->person.sex); 
		}
        AddPreOrderTraverse(T->lchild,name);
        AddPreOrderTraverse(T->rbrother,name);
    }
}

int DeletePreOrderTraverse(tree T,char name[20])//ɾ������ǰ����� 
{
	if(strcmp(name,BT->person.name)==0)//ɾ�����ڵ���� 
	{
		flag=1;
		if(BT->rbrother!=NULL)//����㲻�������ֵ� 
		{
			BT=BT->rbrother;
			return 0; 
		}
		else if(BT->rbrother==NULL)//���ڵ�������ֵ� 
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
        if(strcmp(name,T->lchild->person.name)==0)//��ǰ�������� 
        {
        	flag=1;
        	T->lchild=T->lchild->rbrother;//��ǰ������ӵ������ӵ����ֵ� 
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

int modifyPreOrderTraverse(tree T,char name[20])//�޸ĳ�Ա��Ϣǰ�����
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
        	printf("��ѡ��Ҫ�޸�%s����������:\n",T->person.name);
        	printf("1.�޸�����\n");
        	printf("2.�޸ĳ�������\n");
        	printf("3.�޸ļ�ͥסַ\n");
        	printf("4.�޸Ļ���״��\n");
        	printf("5.�޸��������\n");
        	printf("6.�޸��Ա�\n");
        	printf("7.������һ��\n");
        	scanf("%d",&num);
			switch(num)
			{
				case 1:
				printf("�������޸ĺ��������");
				scanf("%s",T->person.name);
				break;
				case 2:
					do
					{
						if(strlen(T->person.birthday)!=10 && strlen(T->person.birthday)!=0)
						printf("��������ȷ�����ڸ�ʽ\n");
						printf("�������޸ĺ�ĳ�������(��ʽ����: 2020-01-01)��");
        				scanf("%s",&T->person.birthday);
					} while(strlen(T->person.birthday)!=10); 
				break;
				case 3:
				printf("�������޸ĺ�ļ�ͥסַ��");
				scanf("%s",T->person.address);
				break;
				case 4:
				printf("�������޸ĺ�Ļ���״��(0δ�飬1�ѻ�)��");
				scanf("%d",&T->person.marry) ;
				break;
				case 5:
				printf("�������޸ĺ���������(������0-0-0)��");
				scanf("%d",&T->person.death_date);
				break;
				case 6:
				printf("�������޸ĺ���Ա�(0Ů����1����)��");
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

int deterPreOrderTraverse(tree T,char name[20],int *gen)//ȷ����Ա�Ĺ�ϵǰ����� 
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

void printfinfo(tree p)//��ӡ�����Ϣ 
{
			printf("%s  ",p->person.name);
			printf("�����ڣ�%s  ",p->person.birthday);
			printf("%s  ",p->person.address);
			if(p->person.marry==1)
			printf("�ѻ�  ");
			else
			printf("δ��  "); 
			if(p->person.sex==1)
			printf("��  ");
			else
			printf("Ů  ");
			if(strcmp(p->person.death_date,"0-0-0")==0)
			printf("����\n");
			else
			printf("�������ڣ�%s\n",p->person.death_date);
}
void new_left(tree p,data d)//�������� 
{
    tree q=(tree)malloc(sizeof(node));
    q->person=d;
    q->lchild=q->rbrother=NULL;
    p->lchild=q;
}

void new_right(tree p,data d)//�������ֵ� 
{
    tree q=(tree)malloc(sizeof(node));
    q->person=d;
    q->lchild=q->rbrother=NULL;
    p->rbrother=q;
}

int Generation(tree T)//���ش��� 
{
    if(T==NULL)
    return 0;
    if(T)
    return Generation(T->lchild)+1;
}


void Tinit()//��ʼ�������� 
{
	data initdata[10]={{"A","1960-06-12",1,1,"���ż���","2019-10-01",1},
					   {"B","1980-06-12",1,1,"���ż���","0-0-0",2},
                       {"C","1981-06-18",1,1,"���ż���","0-0-0",2},
					   {"D","1982-06-12",1,1,"���ż���","0-0-0",2},
					   {"E","2021-06-12",1,1,"���ż���","0-0-0",3},
					   {"F","2021-06-12",1,1,"���ż���","0-0-0",3},
					   {"G","2021-06-12",1,1,"���ż���","0-0-0",3},
					   {"H","2021-06-12",1,1,"���ż���","0-0-0",3}, 
					   {"I","2021-06-12",1,1,"���ż���","0-0-0",3},
					   {"J","2021-06-12",1,1,"���ż���","0-0-0",3}
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

void today_birthday()//��ʾ�������յĳ�Ա 
{
	flag=0;
	time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
	printf("����������%d-%d���������ճ�Ա��",1+p->tm_mon,p->tm_mday); 
	BirthdayPreOrderTraverse(BT);
	printf("\n");
	if(flag==0)
	printf("������û�г�Ա������\n");
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void show()//��ʾ���� 
{
	queue *q=(queue *)malloc(sizeof(queue));
	q->front=q->rear=0;
	count=0;
	if(BT!=NULL)//����BT���ж����� 
	countnum(BT);
	system("cls");
	printf("����%d����%d��\n",Generation(BT),count);
	printf("\n");
	int d=1;
	tree p=BT;
	tree n=(tree)malloc(sizeof(struct node));//�ָ��� 
	strcpy(n->person.name,"NULL");
	n->lchild=n->rbrother=NULL; 
	if(p)
	{
		printf("��1��\n");
		q->queue[q->rear++]=p;//�������� 
		while(p->rbrother)//�Ѹ�����������ֵ���� 
			{
				p=p->rbrother;
				q->queue[q->rear++]=p;
			}
		q->queue[q->rear++]=n;//�ָ������ 
		while(q->front!=q->rear)//���в�Ϊ�� 
		{
			p=q->queue[q->front++];//ȡ��ͷ��� 
			if(strcmp(p->person.name,"NULL")==0 && q->front!=q->rear)//Ϊ�ָ�ű�ʾһ������ 
			{
				printf("��%d��\n",++d);
				q->queue[q->rear++]=n;//����ָ�����ִ����� 
			}	
			else if(q->front!=q->rear)
			{
				printfinfo(p);
			}
			if(p->lchild)	//������Ӵ��� 
			{
				p=p->lchild;
				q->queue[q->rear++]=p;//�������������ֵ���ӣ���ʾһ�� 
				while(p->rbrother)
				{
					p=p->rbrother;
					q->queue[q->rear++]=p;
				}
			}
		}
	}
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void shownum()//��ʾ�ڼ����� 
{
	int num;
	printf("��������Ҫ��ѯ�ĵڼ����ˣ�");
	scanf("%d",&num); 
	queue *q=(queue *)malloc(sizeof(queue));
	q->front=q->rear=0;
	system("cls");
	int d=1;
	tree p=BT;
	tree n=(tree)malloc(sizeof(struct node));//�ָ��� 
	strcpy(n->person.name,"NULL");
	n->lchild=n->rbrother=NULL; 
	if(p)
	{
		q->queue[q->rear++]=p;//�������� 
		while(p->rbrother)//�Ѹ�����������ֵ���� 
			{
				p=p->rbrother;
				q->queue[q->rear++]=p;
			}
		q->queue[q->rear++]=n;//�ָ������ 
		while(q->front!=q->rear)//���в�Ϊ�� 
		{
			p=q->queue[q->front++];//ȡ��ͷ��� 
			if(strcmp(p->person.name,"NULL")==0 && q->front!=q->rear)//Ϊ�ָ�ű�ʾһ������ 
			{
				d++;
				q->queue[q->rear++]=n;//����ָ�����ִ����� 
			}	
			else if(q->front!=q->rear && num==d)
			{
				printfinfo(p);
			}
			if(p->lchild)	//������Ӵ��� 
			{
				p=p->lchild;
				q->queue[q->rear++]=p;//�������������ֵ���ӣ���ʾһ�� 
				while(p->rbrother)
				{
					p=p->rbrother;
					q->queue[q->rear++]=p;
				}
			}
		}
	}
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void Addchildren() //Ϊ��Ա��Ӻ��� 
{
	char name[20];
	printf("������Ҫ��Ӻ��ӳ�Ա��������");
	scanf("%s",name); 
	flag=0;
	AddPreOrderTraverse(BT,name);
	if(flag==0)
	printf("û�������\n");
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void lookupname()//�����������ҳ�Ա 
{
	char name[20];
	flag=0; 
	printf("������Ҫ��ѯ�˵�����:");
	scanf("%s",name);
	NamePreOrderTraverse(BT,name);
	if(flag==0)
	printf("�Բ����Ҳ������˵���Ϣ\n");
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
}

void deletemember()//ɾ����Ա 
{
	flag=0;
	char name[20];
	printf("������Ҫɾ����Ա��������"); 
	scanf("%s",name);
	DeletePreOrderTraverse(BT,name);
	if(flag==0)
		printf("�Բ����Ҳ������˵���Ϣ\n");
	else
		printf("ɾ���ɹ���");
		printf("�밴�س�������..."); 
		getchar();
		getchar(); 
		system("cls");
		menu();
	
}

void modifymember()//�޸ĳ�Ա��Ϣ 
{
	flag=0; 
	char name[20]; 
	printf("������Ҫ�޸��˵�������"); 
	scanf("%s",name);
	modifyPreOrderTraverse(BT,name);
	if(flag==0)
		printf("�Բ����Ҳ������˵���Ϣ\n");
	else
		printf("�޸ĳɹ���\n");
		printf("�밴�س�������..."); 
		getchar();
		getchar(); 
		system("cls");
		menu();
}

void determinemember()//ȷ����Ա�Ĺ�ϵ 
{
	int i;
	int firstgen=0;//��һ���˴��� 
	int secondgen=0;//�ڶ����˴��� 
	char name1[20],name2[20]; 
	flag=0;
	printf("�������һ���˵�������");
	scanf("%s",name1);
	deterPreOrderTraverse(BT,name1,&firstgen);
	if(flag==0)
	printf("�����޴��ˣ������½��룡\n");
	else
	{
		flag=0;
		printf("������ڶ����˵�������");
		scanf("%s",name2);
		deterPreOrderTraverse(BT,name2,&secondgen);
		if(flag==0)
		printf("�����޴��ˣ������½��룡\n");
		else
		if(secondgen>firstgen)
		{
			printf("%s��%s��%d��\n",name1,name2,secondgen-firstgen);
			for(i=0;i<secondgen-firstgen;i++)
			{
				
			} 
		}
		else if(secondgen<firstgen)
		printf("%s��%sС%d��\n",name1,name2,firstgen-secondgen);
		else if(secondgen==firstgen)
		printf("%s��%sͬ��\n",name1,name2); 
	}
	printf("�밴�س�������..."); 
	getchar();
	getchar(); 
	system("cls");
	menu();
	
}

void menu()
{
	int num;
	printf("\n");
	printf("                        ��ӭ������׹���ϵͳ\n");
	printf("            1.��ʾ�������ճ�Ա           2.��ʾ����\n");
	printf("            3.��ʾ��n�������˵���Ϣ      4.�����������ҳ�Ա\n");
	printf("            5.Ϊ��Ա��Ӻ���             6.ɾ����Ա\n");
	printf("            7.�޸ĳ�Ա��Ϣ               8.ȷ�������˵Ĺ�ϵ\n");
	printf("            0.�˳�����\n");
	do
	{
		printf("��������ţ�");
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
		default:printf("��������ȷ����ţ�\n");
		}	
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8);
}
int main()
{
	Tinit();//��ʼ�������� 
	menu();
	return 0;
}
