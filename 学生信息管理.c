#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student//ѧ����Ϣ�ṹ�� 
{
	char sno[15];
	char sname[20];
	int sex;//0��ʾŮ�ԣ�1��ʾ����
	char birthday[15];
	char tnum[15];
	char address[20]; 
	int score[10];
}student;
typedef struct listnode//������ 
{
	student data;
	struct listnode *next;
}listnode;
struct listnode *head;
int count=0;//ѧ����¼���� 
int scorecount=5;
void Add_student()//���ѧ����Ϣ
{
	struct listnode *p=head;
	int num; 
	int i;
	int flag=0;
	while(1){
		printf("¼��ѧ����Ϣ����ѡ��1.��������  0.����\n"); 
		scanf("%d",&num);
		if(num==1)
		{
			struct listnode *temp=(struct listnode*)malloc(sizeof(struct listnode));	
			count++; 
			do
			{
				p=head;
				flag=0;
				printf("ѧ�ţ�"); 
				scanf("%s",temp->data.sno); 
				while(p->next!=NULL)
				{
					if(strcmp(p->next->data.sno,temp->data.sno)==0)
					{
						flag=1; 
						printf("�Ѵ���ѧ�ţ�������Ψһ��ѧ�ţ�\n");
					}
					p=p->next;
				}
				if(flag==0)
				{
					temp->next=head->next;//ͷ�巨 
					head->next=temp;
				}
			}while(flag==1);
			printf("������");
			scanf("%s",temp->data.sname);
			while(1)
			{
			printf("�Ա�(0��ʾŮ�ԣ�1��ʾ����)��");
			scanf("%d",&temp->data.sex);
			if(temp->data.sex!=1 && temp->data.sex!=0)
			printf("��������ȷ���Ա����!\n");
			else
			break;
			}
			printf("��������(��2020-01-01)��");
			scanf("%s",temp->data.birthday);
			printf("�绰��");
			scanf("%s",temp->data.tnum);
			printf("��ַ��");
			scanf("%s",temp->data.address);
			for(i=1;i<=scorecount;i++)//ѧ���ɼ���ʼ��Ϊ0 
			temp->data.score[i]=0;
		}
		else if(num==0)
		{
			system("cls");
			meau1();
			return;
		}
		else	
		printf("��������ȷ����ţ�\n");
	};
} 
void Browse_student()//���ѧ����Ϣ 
{
	struct listnode *p=head;	
	printf("ѧ��		 ����	 	�Ա�	  	����		  �绰		  ��ַ\n"); 
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%-17s",p->data.sno);
		printf("%-16s",p->data.sname);
		if(p->data.sex==1)
		printf("��		");
		else if(p->data.sex==0)
		printf("Ů		");
		printf("%-18s",p->data.birthday);
		printf("%-16s",p->data.tnum);
		printf("%-20s",p->data.address);
		printf("\n");
	}
	getchar();
	getchar();//С�ڴ�ͣ��
}
void query_student()//��ѯѧ����Ϣ
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.����ѧ�Ų�ѯ	2.����������ѯ	0.����\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau1();
		return;
	}
	else if(num==1)
	{
		printf("����������ҵ�ѧ�ţ�");
		scanf("%s",sno);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("ѧ��		 ����	 	�Ա�	  	����		  �绰		  ��ַ\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("��		");
				else if(p->data.sex==0)
				printf("Ů		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n");
				query_student();
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ�\n");
		query_student();
		return;
		p=head;//��ʼ��ͷָ�� 
	}
	else if(num==2)
	{
		printf("����������ҵ�������");
		scanf("%s",sname); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("ѧ��		 ����	 	�Ա�	  	����		  �绰		  ��ַ\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("��		");
				else if(p->data.sex==0)
				printf("Ů		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n");
				query_student();
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ�\n");
		query_student();
		return;
	}
	else
	{
		printf("��������ȷ����ţ�\n");
		query_student();
		return;
	}
} 
void alter_student()//�޸�ѧ����Ϣ
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.����ѧ���޸�	2.���������޸�	0.����\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau1();
		return;
	}
	else if(num==1)
	{
		printf("��������޸ļ�¼��ѧ�ţ�\n"); 
		scanf("%s",sno); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("������Ҫ�޸ĵ�ѡ��(ѧ��1������2���Ա�3������4���绰5����ַ6)\n");
				scanf("%d",&num);
				switch(num)
				{
					case 1:scanf("%s",p->next->data.sno);break;
					case 2:scanf("%s",p->next->data.sname);break;
					case 3:scanf("%d",&p->next->data.sex);break;
					case 4:scanf("%s",p->next->data.birthday);break;
					case 5:scanf("%s",p->next->data.tnum);break;
					case 6:scanf("%s",p->next->data.address);break;
				}
				printf("�޸ĳɹ�����¼����Ϊ��\n");
				printf("ѧ��		 ����	 	�Ա�	  	����		  �绰		  ��ַ\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("��		");
				else if(p->data.sex==0)
				printf("Ů		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n"); 
				alter_student();
				return;
			}
			
			p=p->next;
		} 
	
		printf("û�ҵ�\n");
		alter_student();
		p=head;//��ʼ��ͷָ�� 
	}
	else if(num==2)
	{
		printf("��������޸ļ�¼��������"); 
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("������Ҫ�޸ĵ�ѡ��(ѧ��1������2���Ա�3������4���绰5����ַ6)\n");
				scanf("%d",&num);
				switch(num)
				{
					case 1:scanf("%s",p->next->data.sno);break;
					case 2:scanf("%s",p->next->data.sname);break;
					case 3:scanf("%d",&p->next->data.sex);break;
					case 4:scanf("%s",p->next->data.birthday);break;
					case 5:scanf("%s",p->next->data.tnum);break;
					case 6:scanf("%s",p->next->data.address);break;
				}
				printf("�޸ĳɹ�����¼����Ϊ��\n");
				printf("ѧ��		 ����	 	�Ա�	  	����		  �绰		  ��ַ\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("��		");
				else if(p->data.sex==0)
				printf("Ů		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				alter_student();
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ�\n");
		alter_student();
	}
	else
	{
		printf("��������ȷ����ţ�\n");
		alter_student();
	}
} 
void delete_student()//ɾ��ѧ����Ϣ 
{
	struct listnode *p=head;
	int num; 
	char sno[15];
	char sname[20];
	printf("1.����ѧ��ɾ����¼	2.��������ɾ����¼	0.����\n"); 
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau1();
		return;
	}    
	else if(num==1)
	{
		count--;
		if(p->next==NULL)
		{
			printf("����ѧ����Ϣ\n");
			delete_student();
			return;	
		}	
		else
		{
			scanf("%s",sno);
			while(p->next!=NULL)
			{
				if(strcmp(p->next->data.sno,sno)==0)
				{
				p->next=p->next->next;
				printf("��ɾ��ѧ��Ϊ%s�ļ�¼\n",sno);
				delete_student();
				return;
				}
				p=p->next;
			} 
			printf("û�ҵ�\n");
			delete_student();
			return;
		}
		
	}
	else if(num==2)
	{
		count--;
		if(p->next==NULL)
		{
			printf("����ѧ����Ϣ\n");
			delete_student();
			return;
		}	
		else
		{
			scanf("%s",sname);
			while(p->next!=NULL)
			{
				if(strcmp(p->next->data.sname,sname)==0)
				{
				p->next=p->next->next;
				printf("��ɾ������Ϊ%s�ļ�¼\n",sname);
				alter_student();
				return;
				}
				p=p->next;
			} 
			printf("û�ҵ�\n");
			delete_student();
			return;
		}
	}     
	else
	{
		printf("��������ȷ����ţ�\n");
		delete_student();
		return;
	}
}
void Add_score()//��ӳɼ���Ϣ
{
	char sno[15];
	struct listnode *p=head;
	int i;
	printf("������Ҫ¼��ɼ���ѧ��ѧ�ţ�\n");
	scanf("%s",sno);
			while(p->next!=NULL)
			{
				if(strcmp(p->next->data.sno,sno)==0)
				{
				printf("������%d�ųɼ�\n",scorecount);
				for(i=1;i<=scorecount;i++)
				scanf("%d",&p->next->data.score[i]); 
				printf("����ɹ���\n");
				printf("�밴���������...");
				getchar();
				getchar();
				system("cls");
				meau2();
				return;
				}
				p=p->next;
			} 
			printf("û�ҵ���ѧ��ѧ��\n");
			printf("�밴���������...");
			getchar(); 
			getchar();
			system("cls");
			meau2();
			return;
}
void Browse_score()//����ɼ���Ϣ 
{
	struct listnode *p=head;
	int i;
	printf("ѧ��		 ����	 	"); 
	for(i=1;i<=scorecount;i++)
	printf("�ɼ�%d	",i);
	printf("\n");
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%-17s",p->data.sno);
		printf("%-16s",p->data.sname);	
		for(i=1;i<=scorecount;i++)
		printf("%-8d",p->data.score[i]);
		printf("\n");
	}
	getchar();
	getchar();//С�ڴ�ͣ��
	system("cls");
	meau2();
	return;
}
void query_score()//��ѯ�ɼ���Ϣ
{
	int num;
	char sno[15];
	char sname[20];
	int i;
	struct listnode *p=head;
	printf("1.����ѧ�Ų�ѯ	2.����������ѯ	0.����\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau2();
		return;
	}
	else if(num==1)
	{
		printf("����������ҵ�ѧ�ţ�");
		scanf("%s",sno);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("ѧ��		 ����	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("�ɼ�%d	",i);
				printf("\n");
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				for(i=1;i<=scorecount;i++)
				printf("%-8d",p->data.score[i]);
				printf("\n");	
				getchar();
				getchar();
				system("cls"); 
				meau2();	
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ���ѧ�ŵĳɼ�\n");
		query_score();
		p=head;//��ʼ��ͷָ�� 
		return;
	}
	else if(num==2)
	{
		printf("����������ҵ�������");
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("ѧ��		 ����	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("�ɼ�%d	",i);
				printf("\n");
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);	
				for(i=1;i<=scorecount;i++)
				printf("%-8d",p->data.score[i]);
				printf("\n");	
				getchar();
				getchar();
				system("cls"); 
				meau2();	
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ��������ĳɼ�\n");
		query_score();
		p=head;//��ʼ��ͷָ�� 
		return;
	}
	else
	{
		printf("��������ȷ����ţ�\n");
		query_student();
		return;
	}
}
void alter_score()//�޸ĳɼ���Ϣ
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.����ѧ���޸�	2.���������޸�	0.����\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau2();
		return;
	}
	else if(num==1)
	{
		printf("��������޸ĳɼ���ѧ�ţ�\n"); 
		scanf("%s",sno); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("������Ҫ�޸ĵķ�������(��Ŵ�1��ʼ)\n");
				scanf("%d",&num);
				printf("ԭ�ɼ�Ϊ%d,�������µĳɼ���",p->next->data.score[num]); 
				scanf("%d",&p->next->data.score[num]);
				printf("�޸ĳɹ�����¼�Ѹ���!\n");
				alter_score();
				return;
			}		
			p=p->next;
		} 
		printf("û�ҵ�\n");
		alter_score();
		p=head;//��ʼ��ͷָ�� 
	}
	else if(num==2)
	{
		printf("��������޸ĳɼ���������"); 
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("������Ҫ�޸ĵķ�������(��Ŵ�1��ʼ)\n");
				scanf("%d",&num);
				printf("ԭ�ɼ�Ϊ%d,�������µĳɼ���",p->next->data.score[num]); 
				scanf("%d",&p->next->data.score[num]);
				printf("�޸ĳɹ�����¼�Ѹ���!\n");
				alter_score();
				return;
			}
			p=p->next;
		} 
		printf("û�ҵ�\n");
		alter_score();
		return;
	}
	else
	{
		printf("��������ȷ����ţ�\n");
		alter_score();
		return;
	}
}
void sort_score()//����ɼ���Ϣ
{
	struct listnode *p=head;
	student sort[100];
	student temp;
	int num; 
	int s=1;
	int i,j;
	int sum[100]={0};
	int k;//�����Ŀ��� 
	while(p->next!=NULL)//������ѧ����Ϣ�浽һ������ 
	{
		i=1;
		sort[s]=p->next->data;
		for(i=1;i<=scorecount;i++)//����ɼ��ܷ� 
			sum[s]=sum[s]+sort[i].score[i];
		p=p->next;
		s++;//��¼���� 
		
	}
	p=head;//��ʼ��ͷָ�� 
	printf("1.������������	2.�����ܷ�����	3.����ĳ�ſγ�����	0.����\n");
	scanf("%d",&num);
	if(num==1)
	{
		if(p->next==NULL)//�ռ�¼��� 
		{
		printf("������ѧ����¼���޷�����\n");
		printf("�밴�س�������..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("����������ʽ������0������1��\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					printf("*");
					if(strcmp(sort[j].sname,sort[j+1].sname)>0)//��һ�����ڵڶ��� 
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		} 
		else if(num==0)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(strcmp(sort[j].sname,sort[j+1].sname)<0)
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		}		
	}
	else if(num==2)
	{
		if(p->next==NULL)//�ռ�¼��� 
		{
		printf("������ѧ����¼���޷�����\n");
		printf("�밴�س�������..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("����������ʽ������0������1��\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sum[j]>sum[j+1])//��һ�����ڵڶ��� 
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		} 
		else if(num==0)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sum[j]<sum[j+1])
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		}		
	}
	else if(num==3)
	{
		if(p->next==NULL)//�ռ�¼��� 
		{
		printf("������ѧ����¼���޷�����\n");
		printf("�밴�س�������..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("�����������Ŀ��ţ���1��ʼ����");
		scanf("%d",&k); 
		printf("����������ʽ������0������1��\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sort[j].score[k]>sort[j+1].score[k])//��һ�����ڵڶ��� 
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		} 
		else if(num==0)
		{
			for(i=1;i<=s-1;i++)//���� 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sort[j].score[k]<sort[j+1].score[k])
					{
					temp=sort[j];
					sort[j]=sort[j+1];
					sort[j+1]=temp;
					}
				}
			}	
		}		
	}
	else if(num==0)
	{
		system("cls");
		meau2();
		return;
	}
	else
	{
		printf("��������ȷ����ţ�\n");
		sort_score();
		return;
	}
	printf("ѧ��		 ����	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("�ɼ�%d	",i);
				printf("\n");
	for(i=1;i<s;i++)
	{
		
		printf("%-17s",sort[i].sno);
		printf("%-16s",sort[i].sname);	
		for(j=1;j<=scorecount;j++)
			printf("%-7d ",sort[i].score[j]);
			printf("\n");
	}
	getchar();
	getchar();
	system("cls");
	meau2();
}
void alter_scorenum()//�޸ĳɼ���Ŀ 
{
	struct listnode *p=head;
	int i;
	int nowcount=scorecount;
	printf("������Ҫ�޸�Ϊ���ųɼ���");
	scanf ("%d",&scorecount);
	while(p->next!=NULL)
	{
		for(i=nowcount+1;i<=scorecount;i++)//�������ļ��ųɼ���ʼ��Ϊ0 ��ԭ�еĳɼ������޸� 
		p->next->data.score[i]=0;
		p=p->next;
	}
	printf("�޸ĳɹ���\n");
	printf("�밴�س������أ�");
	getchar();
	getchar();
	system("cls");
	 meau2();
}
void meau1();//ѧ��������Ϣҳ 
void meau2();//ѧ���ɼ�ҳ 
void meau0()//��ҳ 
{
	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	*****************��ӭ����ѧ����Ϣ����ϵͳ******************\n");
		printf("\n");
		printf("			1.������Ϣ����\n");
		printf("			2.�ɼ�����\n");
		printf("			0.�˳�\n");
		printf("\n");
		printf("	*************************ллʹ��*************************\n");
		printf("\n");
		printf("��������ţ�");
		scanf("%d",&num);
		switch(num)
		{
			case 1:system("cls");
			meau1();	
					break;
			case 2:system("cls");
			meau2();
					break;
			case 0:	exit(1);
			default:system("cls"); printf("���������������������룡\n");
		} 
	}while(num!=0 && num!=1 && num!=2);
}
void meau1()//ѧ��������Ϣ����ҳ�� 
{

	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	*********************ѧ��������Ϣ����*********************\n");
		printf("\n");
		printf("		1.���ѧ����Ϣ		2.���ѧ����Ϣ\n");
		printf("		3.��ѯѧ����Ϣ		4.�޸�ѧ����Ϣ\n");
		printf("		5.ɾ��ѧ����Ϣ		0.�˳�\n");		
		printf("\n");
		printf("				 	  (����%d��ѧ����Ϣ��¼)\n",count); 
		printf("	*************************ллʹ��*************************\n");
		printf("\n");
		printf("��������ţ�");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			Add_student();//���ѧ����Ϣ	
					break;
			case 2:
			Browse_student();//���ѧ����Ϣ 
			system("cls");
			meau1();
					break;
			case 3:
			query_student();//��ѯѧ����Ϣ
					break;
			case 4:
			alter_student();//�޸�ѧ����Ϣ
					break;
			case 5:
			delete_student();//ɾ��ѧ����Ϣ
					break;
			case 0:system("cls");
			meau0(); //���ص���ҳ�˵� 
			break;
			default:system("cls");printf("���������������������룡\n");
		} 
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5);
}
void meau2()//ѧ���ɼ�����ҳ�� 
{

	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	***********************ѧ���ɼ�����***********************\n");
		printf("\n");
		printf("		1.��ӳɼ���Ϣ		2.����ɼ���Ϣ\n");
		printf("		3.��ѯ�ɼ���Ϣ		4.�޸ĳɼ���Ϣ\n");
		printf("		5.����ɼ���Ϣ		6.�޸ĳɼ�����\n");		
		printf("		0.�˳�\n");	
		printf("\n");
		printf("				   	    Ŀǰѧ����%d�ųɼ�\n",scorecount); 
		printf("	*************************ллʹ��*************************\n");
		printf("\n");
		printf("��������ţ�");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			Add_score();//��ӳɼ���Ϣ	
					break;
			case 2:
			Browse_score();//����ɼ���Ϣ 
					break;
			case 3:
			query_score();//��ѯ�ɼ���Ϣ
					break;
			case 4:
			alter_score();//�޸ĳɼ���Ϣ
					break;
			case 5:
			sort_score();//����ɼ���Ϣ
					break;
			case 6:
				alter_scorenum();
					break;
			case 0:system("cls");
			meau0(); //���ص���ҳ�˵� 
			break;
			default:system("cls");printf("���������������������룡\n");
		} 
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6);
}
int main()
{
	head=(struct listnode*)malloc(sizeof(struct listnode));//����ͷָ��
	head->next=NULL;
	meau0();
	return 0;
}
