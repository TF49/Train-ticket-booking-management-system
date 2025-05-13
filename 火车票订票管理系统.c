#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<dos.h>
#define HEADER1 "---------------火车票订票管理系统---------------\n\n" 
#define HEADER2 "|  车次  | 出发城市 | 目的城市 | 发车时间 | 到达时间 |  票价  |  票数  |\n"
#define HEADER3 "|----------|----------|----------|----------|----------|----------|----------|"
#define FORMAT "|%-10s|%-10s%|%-10s|%-10s|%-10s|%5d|  %5d   |\n"
#define DATA p->data.num, p->data.startcity, p->data.reachcity, p->data.takeofftime, p->data.arrivetime, p->data.price, p->data.ticketnum
#define FILENAME1 "train.txt"
#define FILENAME2 "man.txt"

int saveflag=0;

struct train//定义存储火车票信息的结构体 
{
	char num[10];//车次 
	char startcity[10];//出发城市 
	char reachcity[10];//目的城市 
	char takeofftime[10];//发车时间 
	char arrivetime[10];//到达时间 
	int price;//票价 
	int ticketnum;//票数 
}; 

struct man//定义存储订票人信息的结构体 
{
	char num[18];//ID 
	char name[10];//姓名 
	int bookNum;//订的票数 
};

typedef struct node//定义存储火车票信息的链表的节点结构 
{
	struct train data;
	struct node *next;
}Node,*Link;

typedef struct Man
{
	struct man data;
	struct Man *next;
}book,*bookLink;

void menu(); 						//用于显示系统主界面 
void Traininfo(Link linkhead);		//添加火车票信息 
void printheader();					//输出火车票信息表头 
void printdata(Node *q);			//格式化输出表中数据 
void searchtrain(Link l);			//查询火车票信息 
void Bookticket(Link l,bookLink k);	//预订火车票 
void Modify(Link l);				//修改火车票新年喜 
void showtrain(Link l);				//显示火车票信息 
void SaveTrainInfo(Link l);			//保存火车票信息 
void SaveBookInfo(bookLink k);		//保存订票人信息

void menu()
{
	printf("\n\n");
	printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|               火车票订票管理系统               |\n");
	printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|                0.退出系统                      |\n");
	printf("\t\t|                1.添加火车票信息                |\n");
	printf("\t\t|                2.查询火车票信息                |\n");
	printf("\t\t|                3.预订火车票                    |\n");
	printf("\t\t|                4.修改火车票信息                |\n");
	printf("\t\t|                5.显示火车票信息                |\n");
	printf("\t\t|                6.保存火车票和订票人信息        |\n");
	printf("\t\t|------------------------------------------------|\n");
}

void Traininfo(Link linkhead)
{
	
	struct node *p,*r,*s;			//定义3个node类型的指针变量
	char num[10];
	r=linkhead;						//r指针指向存储火车票信息的链表表表头 
	s=linkhead->next;				//s指针指向存储火车票信息的链表的下一个结点 
	while(r->next!=NULL)			//判断链表是否为空 
	r=r->next;
	while(1)						//循环输入火车票信息 
	{
		printf("请输入火车车次(0-返回系统主界面)：");
		scanf("%s",num);
		if(strcmp(num,"0")==0)		//判断输入值是否为0
		{
			break;
		}				
		while(s)					//循环判断输入值是否已经存在 
		{
			if(strcmp(s->data.num,num)==0)
			{
				printf("此车次或者'%s'已经存在！\n",num);
				return;
			}
			s=s->next;				//移动到下一个节点 
		}
	
		p=(struct node*)malloc(sizeof(struct node));//为p动态开辟内存
		strcpy(p->data.num,num);	//输入车次 
		printf("输入出发城市：");
		scanf("%s",p->data.startcity);//输入出发城市
		printf("输入目的城市：");
		scanf("%s",p->data.reachcity);//输入目的城市 
		printf("输入发车时间：");
		scanf("%s",p->data.takeofftime);//输入发车时间 
		printf("输入到达时间：");
		scanf("%s",p->data.arrivetime); //输入到达时间 
		printf("输入火车票价：");
		scanf("%d",&p->data.price); //输入火车票价 
		printf("输入预计票数：");
		scanf("%d",&p->data.ticketnum); //输入预定票数
		p->next=NULL;
		r->next=p;
		r=p;							//将r移到p节点
		saveflag=1;						//设置存储标志 
	}
}

void searchtrain(Link l)
{
	Node *s[10],*r;//定义一个火车票信息链表节点类型的指针数组和一个指针 
	int sel,k,i=0;
	char str1[5],str2[10];
	if(!l->next)
	{
		printf("没有查询到任何火车票记录！");
		return; 
	}
	printf("请选择查询方式：\n1.根据火车车次查询;\n2.根据目的城市查询;\n");
	scanf("%d",&sel); //输入选择的序号
	if(sel==1)
	{
		printf("输入查询车次：");
		scanf("%s",str1);
		r=l->next;
		while(r!=NULL)
			if(strcmp(r->data.num,str1)==0)//检索是否有与输入的车次相匹配的信息
			{
				s[i]=r;
				i=i+1;
				break; 
			}
			else
			{
				r=r->next;
			}
	} 
	else if(sel==2)
	{
		printf("输入目的城市：");
		scanf("%s",str2);
		r=l->next;
		while(r!=NULL)
			if(strcmp(r->data.reachcity,str2)==0)//检索是否有与输入的目的城市相匹配的信息
			{
				s[i]=r;
				i=i+1;
				r=r->next;	
			}
			else
			{
				r=r->next;
			}
	}
	if(i==0)
	{
		printf("没有查询到相关信息！");
	}
	else
	{
			printheader();//输出表头
		for(k=0;k<i;k=k+1)
		{
			printdata(s[k]);//循环输出查询到的信息 
		} 
	}
}

void Bookticket(Link l,bookLink k)
{
	Node *r[10],*p;
	char ch[2],tnum[10],str[10],str1[10],str2[10];
	book *q,*h;
	int i=0,t=0,flag=0,dnum;
	q=k;//将读取的订票人信息链表地址赋值给指针q
	while(q->next!=NULL)//判断订票人信息链表是否为空 
	q=q->next;//将q指向订票人信息链表尾部
	printf("输入目的城市：");
	scanf("%s",&str);//输入要到达的城市
	p=l->next;//指针p指向火车票信息链表首节点
	while(p!=NULL)
	{
		if(strcmp(p->data.reachcity,str)==0)
		{
			r[i]=p;//将满足条件的记录存到数组r中
			i=i+1; 
		}
		p=p->next; 
	}
	printf("\n\n你查询到的%s的车次共有：%d趟\n",str,i);
		printheader();
	for(t=0;t<i;t=t+1)
		printdata(r[t]);
	if(i==0)
	{
		printf("\n抱歉！没有找到你要的火车车次！\n");
	}
	else
	{
		printf("\n你确定要订票吗？<y/n\n");
		scanf("%s",ch);
		if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)//判断是否订票
		{
			h=(book*)malloc(sizeof(book));
			printf("输入姓名：");
			scanf("%s",&str1);
			strcpy(h->data.name,str1);
			printf("请输入身份证号码:");
			scanf("%s",str2);
			strcpy(h->data.num,str2);
			printf("请输入火车车次：");
			scanf("%s",tnum);
			for(t=0;t<i;t=t+1)
			{
				if(strcmp(r[t]->data.num,tnum)==0)
				{
					if(r[t]->data.ticketnum<1)//判断剩余的票数是否小于1 
					{
						printf("抱歉没票了！");
						Sleep(2);
						return; 
					}
					printf("剩余%d张车票\n",r[t]->data.ticketnum);
					flag=1;
					break; 
				}
				if(flag==0)
				{
					printf("输入错误！");
					Sleep(2);
					return; 
				}
			} 
			printf("输入订票数量：");
			scanf("%d",&dnum);
			r[t]->data.ticketnum=r[t]->data.ticketnum-dnum;//可供预定的票数相应减少
			h->data.bookNum=dnum;
			h->next=NULL;
			q->next=h;
			q=h;
			printf("\n祝贺！你成功预定了%d张车票！",dnum);
			getch();
			saveflag=1; 
		} 
	}
}

void Modify(Link l)
{
	Node *p;
	char tnum[10],ch;
	p=l->next;
	if(!p)
	{
		printf("\n没有你要修改的记录！\n");
		return;
	}
	else
	{
		printf("\n你确定要修改火车票信息？(y/n)\n");
		getchar();
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n输入火车车次：");
			scanf("%s",tnum);
			while(p!=NULL)
			if(strcmp(p->data.num,tnum)==0)//查找与输入的车次相匹配的记录
			{
				break; 
			}
			else
			{
				p=p->next;	
			}
			if(p)
			{
				printf("输入新的火车车次：");
				scanf("%s",&p->data.num);
				printf("输入新的出发城市：");
				scanf("%s",&p->data.startcity); 
				printf("输入新的目的城市：");
				scanf("%s",&p->data.reachcity); 
				printf("输入新的发车时间：");
				scanf("%s",&p->data.takeofftime); 
				printf("输入新的到达时间：");
				scanf("%s",&p->data.arrivetime); 
				printf("输入新的火车票价：");
				scanf("%d",&p->data.price); 
				printf("输入新的预定票数：");
				scanf("%d",&p->data.ticketnum); 
				printf("\n修改记录成功！\n");
				saveflag=1;	
			}
			else
			{
				printf("\n没有此车次记录！"); 
			}
		}
	}
}

void printheader()
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
void printdata(Node *q)
{
	Node*p;
	p=q;
	printf(FORMAT,DATA);
}
void showtrain(Link l)//自定义函数显示火车票信息 
{
	Node* p;
	p=l->next;
	printheader();
	if(l->next==NULL)
	{
		printf("没有此列车车票记录！"); 
	}
	else
	{
		while(p!=NULL)
		{
			printdata(p);
			p=p->next;
		}
	}
}

void SaveTrainInfo(Link l)
{
	FILE *fp;
	Node *p;
	int count=0,flag=1;
	fp=fopen("train.txt","wb");
	if(fp==NULL)
	{
		printf("无法打开保存火车票信息的文件！");
		return; 
	}
	p=l->next;
	while(p)
	{
		if(fwrite(p,sizeof(Node),1,fp)==1)
		{
			p=p->next;
			count=count+1;
		}
		else
		{
			flag=0;
			break;
		}
		
	}
	if(flag)
		{
			printf("保存了%d辆火车的车票记录\n",count);
			saveflag=0;
		}
		fclose(fp);
}

void SaveBookInfo(bookLink k)
{
	FILE *fp;
	book *p;
	int count=0,flag=1;
	fp=fopen("man.txt","wb");
	if(fp==NULL)
	{
		printf("无法打开保存订票人信息的文件！");
		return;
	}
	p=k->next;
	while(p)
	{
		if(fwrite(p,sizeof(book),1,fp)==1)
		{
			p=p->next;
			count=count+1;
		}
		else
		{
			flag=0;
			break;
		}
		
	}
	if(flag)
		{
			printf("保存了%d份订票人记录\n",count);
			saveflag=0;
		}
		fclose(fp);
}

int main()
{
	FILE *fp1,*fp2;
	Node *p,*r;
	char ch1,ch2;
	Link l;
	bookLink k;
	book *t,*h;
	int sel;
	l=(Node*)malloc(sizeof(Node));
	l->next=NULL;
	r=l;
	k=(book*)malloc(sizeof(book));
	k->next=NULL;
	h=k;
	fp1=fopen("train.txt","ab+");	//打开存储火车票信息的文件 
	if((fp1==NULL))												 	//文件未成功打开 
	{
		printf("无法打开保存火车票信息的文件！");
		return 0; 
	}
	while(!feof(fp1))												//判断文件流是否到结尾 
	{
		p=(Node*)malloc(sizeof(Node));							 	//为p动态开辟内存 
		if(fread(p,sizeof(Node),1,fp1)==1)							//从指定磁盘文件读取记录 
		{
			p->next=NULL;
			r->next=p;												//构造链表 
			r=p;
		}
	}
	fclose(fp1);													//关闭文件 
	fp2=fopen("man.txt","ab+");		//打开存储订票人信息的文件 
	if((fp2==NULL))													//文件为成功打开 
	{
		printf("无法打开保存订票人信息的文件！");
		system("pause"); 
		return 0;
	}
	while(!feof(fp2))												//判断文件流是否到结尾 
	{
		t=(book*)malloc(sizeof(book));								//为t动态开辟内存 
		if(fread(t,sizeof(book),1,fp2)==1)							//从指定磁盘文件读取记录 
		{
			t->next=NULL;
			h->next=t;												//构造链表 
			h=t;
		}
	}
	fclose(fp2);													//关闭文件 
	while(1)
	{
		system("cls");												//清屏	 
		menu();														//调用nemu()主界面函数 
		printf("\t请选择(0-6):");
		scanf("%d",&sel);
		system("cls");
		if(sel==0)
		{
			if(saveflag==1)											//退出时判断信息是否保存 
			{
				getchar();
				printf("\n文件已经修改！是否保存(y/n)?\n");
				scanf("%c",&ch1);
				if(ch1=='y'||ch1=='Y')
				{
					SaveBookInfo(k);
					SaveTrainInfo(l); 
				}
			}
			printf("\n谢谢！欢迎再次光临！\n");
			break;
		}
	
	switch(sel)														//根据不同的sel值的不同选择相应操作 
	{
		case 1:
			Traininfo(l);								//调用添加火车票信息的函数 
			break;
		case 2:
			searchtrain(l);										//调用查询火车票信息的函数 
			break;
		case 3:
			Bookticket(l,k);										//调用预定火车票的函数 
			break;
		case 4:
			Modify(l);											//调用修改火车票信息的函数 
			break;
		case 5:
			showtrain(l);											//调用显示火车票信息的函数 
			break;
		case 6:
			SaveTrainInfo(l);										//调用保存火车票信息的函数 
			SaveBookInfo(k);										//调用保存订票人信息的函数 
			break;
		case 0:
			return 0;
	}
	printf("\n按任意键继续...");
	system("pause");
	getch();
	}
}
