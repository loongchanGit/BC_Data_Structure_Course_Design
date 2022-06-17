#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student//学生信息结构体 
{
	char sno[15];
	char sname[20];
	int sex;//0表示女性，1表示男性
	char birthday[15];
	char tnum[15];
	char address[20]; 
	int score[10];
}student;
typedef struct listnode//链表结点 
{
	student data;
	struct listnode *next;
}listnode;
struct listnode *head;
int count=0;//学生记录总数 
int scorecount=5;
void Add_student()//添加学生信息
{
	struct listnode *p=head;
	int num; 
	int i;
	int flag=0;
	while(1){
		printf("录入学生信息，请选择：1.输入数据  0.返回\n"); 
		scanf("%d",&num);
		if(num==1)
		{
			struct listnode *temp=(struct listnode*)malloc(sizeof(struct listnode));	
			count++; 
			do
			{
				p=head;
				flag=0;
				printf("学号："); 
				scanf("%s",temp->data.sno); 
				while(p->next!=NULL)
				{
					if(strcmp(p->next->data.sno,temp->data.sno)==0)
					{
						flag=1; 
						printf("已存在学号，请输入唯一的学号！\n");
					}
					p=p->next;
				}
				if(flag==0)
				{
					temp->next=head->next;//头插法 
					head->next=temp;
				}
			}while(flag==1);
			printf("姓名：");
			scanf("%s",temp->data.sname);
			while(1)
			{
			printf("性别(0表示女性，1表示男性)：");
			scanf("%d",&temp->data.sex);
			if(temp->data.sex!=1 && temp->data.sex!=0)
			printf("请输入正确的性别序号!\n");
			else
			break;
			}
			printf("出生日期(如2020-01-01)：");
			scanf("%s",temp->data.birthday);
			printf("电话：");
			scanf("%s",temp->data.tnum);
			printf("地址：");
			scanf("%s",temp->data.address);
			for(i=1;i<=scorecount;i++)//学生成绩初始化为0 
			temp->data.score[i]=0;
		}
		else if(num==0)
		{
			system("cls");
			meau1();
			return;
		}
		else	
		printf("请输入正确的序号！\n");
	};
} 
void Browse_student()//浏览学生信息 
{
	struct listnode *p=head;	
	printf("学号		 姓名	 	性别	  	生日		  电话		  地址\n"); 
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%-17s",p->data.sno);
		printf("%-16s",p->data.sname);
		if(p->data.sex==1)
		printf("男		");
		else if(p->data.sex==0)
		printf("女		");
		printf("%-18s",p->data.birthday);
		printf("%-16s",p->data.tnum);
		printf("%-20s",p->data.address);
		printf("\n");
	}
	getchar();
	getchar();//小黑窗停留
}
void query_student()//查询学生信息
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.输入学号查询	2.输入姓名查询	0.返回\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau1();
		return;
	}
	else if(num==1)
	{
		printf("请输入待查找的学号：");
		scanf("%s",sno);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("学号		 姓名	 	性别	  	生日		  电话		  地址\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("男		");
				else if(p->data.sex==0)
				printf("女		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n");
				query_student();
				return;
			}
			p=p->next;
		} 
		printf("没找到\n");
		query_student();
		return;
		p=head;//初始化头指针 
	}
	else if(num==2)
	{
		printf("请输入待查找的姓名：");
		scanf("%s",sname); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("学号		 姓名	 	性别	  	生日		  电话		  地址\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("男		");
				else if(p->data.sex==0)
				printf("女		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n");
				query_student();
				return;
			}
			p=p->next;
		} 
		printf("没找到\n");
		query_student();
		return;
	}
	else
	{
		printf("请输入正确的序号！\n");
		query_student();
		return;
	}
} 
void alter_student()//修改学生信息
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.输入学号修改	2.输入姓名修改	0.返回\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau1();
		return;
	}
	else if(num==1)
	{
		printf("请输入待修改记录的学号：\n"); 
		scanf("%s",sno); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("请输入要修改的选项(学号1，姓名2，性别3，生日4，电话5，地址6)\n");
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
				printf("修改成功，记录更新为：\n");
				printf("学号		 姓名	 	性别	  	生日		  电话		  地址\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("男		");
				else if(p->data.sex==0)
				printf("女		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				printf("\n"); 
				alter_student();
				return;
			}
			
			p=p->next;
		} 
	
		printf("没找到\n");
		alter_student();
		p=head;//初始化头指针 
	}
	else if(num==2)
	{
		printf("请输入待修改记录的姓名："); 
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("请输入要修改的选项(学号1，姓名2，性别3，生日4，电话5，地址6)\n");
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
				printf("修改成功，记录更新为：\n");
				printf("学号		 姓名	 	性别	  	生日		  电话		  地址\n"); 
				p=p->next;
				printf("%-17s",p->data.sno);
				printf("%-16s",p->data.sname);
				if(p->data.sex==1)
				printf("男		");
				else if(p->data.sex==0)
				printf("女		");
				printf("%-18s",p->data.birthday);
				printf("%-16s",p->data.tnum);
				printf("%-20s",p->data.address);
				alter_student();
				return;
			}
			p=p->next;
		} 
		printf("没找到\n");
		alter_student();
	}
	else
	{
		printf("请输入正确的序号！\n");
		alter_student();
	}
} 
void delete_student()//删除学生信息 
{
	struct listnode *p=head;
	int num; 
	char sno[15];
	char sname[20];
	printf("1.输入学号删除记录	2.输入姓名删除记录	0.返回\n"); 
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
			printf("暂无学生信息\n");
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
				printf("已删除学号为%s的记录\n",sno);
				delete_student();
				return;
				}
				p=p->next;
			} 
			printf("没找到\n");
			delete_student();
			return;
		}
		
	}
	else if(num==2)
	{
		count--;
		if(p->next==NULL)
		{
			printf("暂无学生信息\n");
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
				printf("已删除姓名为%s的记录\n",sname);
				alter_student();
				return;
				}
				p=p->next;
			} 
			printf("没找到\n");
			delete_student();
			return;
		}
	}     
	else
	{
		printf("请输入正确的序号！\n");
		delete_student();
		return;
	}
}
void Add_score()//添加成绩信息
{
	char sno[15];
	struct listnode *p=head;
	int i;
	printf("请输入要录入成绩的学生学号：\n");
	scanf("%s",sno);
			while(p->next!=NULL)
			{
				if(strcmp(p->next->data.sno,sno)==0)
				{
				printf("请输入%d门成绩\n",scorecount);
				for(i=1;i<=scorecount;i++)
				scanf("%d",&p->next->data.score[i]); 
				printf("输入成功！\n");
				printf("请按任意键继续...");
				getchar();
				getchar();
				system("cls");
				meau2();
				return;
				}
				p=p->next;
			} 
			printf("没找到该学号学生\n");
			printf("请按任意键继续...");
			getchar(); 
			getchar();
			system("cls");
			meau2();
			return;
}
void Browse_score()//浏览成绩信息 
{
	struct listnode *p=head;
	int i;
	printf("学号		 姓名	 	"); 
	for(i=1;i<=scorecount;i++)
	printf("成绩%d	",i);
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
	getchar();//小黑窗停留
	system("cls");
	meau2();
	return;
}
void query_score()//查询成绩信息
{
	int num;
	char sno[15];
	char sname[20];
	int i;
	struct listnode *p=head;
	printf("1.输入学号查询	2.输入姓名查询	0.返回\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau2();
		return;
	}
	else if(num==1)
	{
		printf("请输入待查找的学号：");
		scanf("%s",sno);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("学号		 姓名	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("成绩%d	",i);
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
		printf("没找到该学号的成绩\n");
		query_score();
		p=head;//初始化头指针 
		return;
	}
	else if(num==2)
	{
		printf("请输入待查找的姓名：");
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("学号		 姓名	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("成绩%d	",i);
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
		printf("没找到该姓名的成绩\n");
		query_score();
		p=head;//初始化头指针 
		return;
	}
	else
	{
		printf("请输入正确的序号！\n");
		query_student();
		return;
	}
}
void alter_score()//修改成绩信息
{
	int num;
	char sno[15];
	char sname[20];
	struct listnode *p=head;
	printf("1.输入学号修改	2.输入姓名修改	0.返回\n");
	scanf("%d",&num);
	if(num==0)
	{
		system("cls");
		meau2();
		return;
	}
	else if(num==1)
	{
		printf("请输入待修改成绩的学号：\n"); 
		scanf("%s",sno); 
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sno,sno)==0)
			{
				printf("请输入要修改的分数序列(序号从1开始)\n");
				scanf("%d",&num);
				printf("原成绩为%d,请输入新的成绩：",p->next->data.score[num]); 
				scanf("%d",&p->next->data.score[num]);
				printf("修改成功，记录已更新!\n");
				alter_score();
				return;
			}		
			p=p->next;
		} 
		printf("没找到\n");
		alter_score();
		p=head;//初始化头指针 
	}
	else if(num==2)
	{
		printf("请输入待修改成绩的姓名："); 
		scanf("%s",sname);
		while(p->next!=NULL)
		{
			if(strcmp(p->next->data.sname,sname)==0)
			{
				printf("请输入要修改的分数序列(序号从1开始)\n");
				scanf("%d",&num);
				printf("原成绩为%d,请输入新的成绩：",p->next->data.score[num]); 
				scanf("%d",&p->next->data.score[num]);
				printf("修改成功，记录已更新!\n");
				alter_score();
				return;
			}
			p=p->next;
		} 
		printf("没找到\n");
		alter_score();
		return;
	}
	else
	{
		printf("请输入正确的序号！\n");
		alter_score();
		return;
	}
}
void sort_score()//排序成绩信息
{
	struct listnode *p=head;
	student sort[100];
	student temp;
	int num; 
	int s=1;
	int i,j;
	int sum[100]={0};
	int k;//排序科目序号 
	while(p->next!=NULL)//把所有学生信息存到一个数组 
	{
		i=1;
		sort[s]=p->next->data;
		for(i=1;i<=scorecount;i++)//计算成绩总分 
			sum[s]=sum[s]+sort[i].score[i];
		p=p->next;
		s++;//记录长度 
		
	}
	p=head;//初始化头指针 
	printf("1.根据姓氏排序	2.根据总分排序	3.根据某门课程排序	0.返回\n");
	scanf("%d",&num);
	if(num==1)
	{
		if(p->next==NULL)//空记录情况 
		{
		printf("不存在学生记录，无法排序！\n");
		printf("请按回车键继续..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("请输入排序方式（降序0，升序1）\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//升序 
			{
				for(j=1;j<=s-1-i;j++)
				{
					printf("*");
					if(strcmp(sort[j].sname,sort[j+1].sname)>0)//第一个大于第二个 
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
			for(i=1;i<=s-1;i++)//降序 
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
		if(p->next==NULL)//空记录情况 
		{
		printf("不存在学生记录，无法排序！\n");
		printf("请按回车键继续..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("请输入排序方式（降序0，升序1）\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//升序 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sum[j]>sum[j+1])//第一个大于第二个 
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
			for(i=1;i<=s-1;i++)//降序 
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
		if(p->next==NULL)//空记录情况 
		{
		printf("不存在学生记录，无法排序！\n");
		printf("请按回车键继续..."); 
		getchar();
		getchar();
		system("cls");
		meau2(); 
		return; 
		}
		printf("请输入排序科目序号（从1开始）：");
		scanf("%d",&k); 
		printf("请输入排序方式（降序0，升序1）\n"); 
		scanf("%d",&num); 
		if(num==1)
		{
			for(i=1;i<=s-1;i++)//升序 
			{
				for(j=1;j<=s-1-i;j++)
				{
					if(sort[j].score[k]>sort[j+1].score[k])//第一个大于第二个 
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
			for(i=1;i<=s-1;i++)//降序 
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
		printf("请输入正确的序号！\n");
		sort_score();
		return;
	}
	printf("学号		 姓名	 	"); 
				for(i=1;i<=scorecount;i++)
				printf("成绩%d	",i);
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
void alter_scorenum()//修改成绩数目 
{
	struct listnode *p=head;
	int i;
	int nowcount=scorecount;
	printf("请输入要修改为几门成绩：");
	scanf ("%d",&scorecount);
	while(p->next!=NULL)
	{
		for(i=nowcount+1;i<=scorecount;i++)//把新增的几门成绩初始化为0 ，原有的成绩不作修改 
		p->next->data.score[i]=0;
		p=p->next;
	}
	printf("修改成功！\n");
	printf("请按回车键返回！");
	getchar();
	getchar();
	system("cls");
	 meau2();
}
void meau1();//学生基本信息页 
void meau2();//学生成绩页 
void meau0()//首页 
{
	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	*****************欢迎进入学生信息管理系统******************\n");
		printf("\n");
		printf("			1.基本信息管理\n");
		printf("			2.成绩管理\n");
		printf("			0.退出\n");
		printf("\n");
		printf("	*************************谢谢使用*************************\n");
		printf("\n");
		printf("请输入序号：");
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
			default:system("cls"); printf("输入的序号有误，请重新输入！\n");
		} 
	}while(num!=0 && num!=1 && num!=2);
}
void meau1()//学生基本信息管理页面 
{

	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	*********************学生基本信息管理*********************\n");
		printf("\n");
		printf("		1.添加学生信息		2.浏览学生信息\n");
		printf("		3.查询学生信息		4.修改学生信息\n");
		printf("		5.删除学生信息		0.退出\n");		
		printf("\n");
		printf("				 	  (现有%d条学生信息记录)\n",count); 
		printf("	*************************谢谢使用*************************\n");
		printf("\n");
		printf("请输入序号：");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			Add_student();//添加学生信息	
					break;
			case 2:
			Browse_student();//浏览学生信息 
			system("cls");
			meau1();
					break;
			case 3:
			query_student();//查询学生信息
					break;
			case 4:
			alter_student();//修改学生信息
					break;
			case 5:
			delete_student();//删除学生信息
					break;
			case 0:system("cls");
			meau0(); //返回到首页菜单 
			break;
			default:system("cls");printf("输入的序号有误，请重新输入！\n");
		} 
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5);
}
void meau2()//学生成绩管理页面 
{

	int num;
	do
	{
		printf("\n");
		printf("\n");
		printf("	***********************学生成绩管理***********************\n");
		printf("\n");
		printf("		1.添加成绩信息		2.浏览成绩信息\n");
		printf("		3.查询成绩信息		4.修改成绩信息\n");
		printf("		5.排序成绩信息		6.修改成绩数量\n");		
		printf("		0.退出\n");	
		printf("\n");
		printf("				   	    目前学生有%d门成绩\n",scorecount); 
		printf("	*************************谢谢使用*************************\n");
		printf("\n");
		printf("请输入序号：");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			Add_score();//添加成绩信息	
					break;
			case 2:
			Browse_score();//浏览成绩信息 
					break;
			case 3:
			query_score();//查询成绩信息
					break;
			case 4:
			alter_score();//修改成绩信息
					break;
			case 5:
			sort_score();//排序成绩信息
					break;
			case 6:
				alter_scorenum();
					break;
			case 0:system("cls");
			meau0(); //返回到首页菜单 
			break;
			default:system("cls");printf("输入的序号有误，请重新输入！\n");
		} 
	}while(num!=0 && num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6);
}
int main()
{
	head=(struct listnode*)malloc(sizeof(struct listnode));//链表头指针
	head->next=NULL;
	meau0();
	return 0;
}
