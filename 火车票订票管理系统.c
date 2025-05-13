#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<dos.h>
#define HEADER1 "---------------��Ʊ��Ʊ����ϵͳ---------------\n\n" 
#define HEADER2 "|  ����  | �������� | Ŀ�ĳ��� | ����ʱ�� | ����ʱ�� |  Ʊ��  |  Ʊ��  |\n"
#define HEADER3 "|----------|----------|----------|----------|----------|----------|----------|"
#define FORMAT "|%-10s|%-10s%|%-10s|%-10s|%-10s|%5d|  %5d   |\n"
#define DATA p->data.num, p->data.startcity, p->data.reachcity, p->data.takeofftime, p->data.arrivetime, p->data.price, p->data.ticketnum
#define FILENAME1 "train.txt"
#define FILENAME2 "man.txt"

int saveflag=0;

struct train//����洢��Ʊ��Ϣ�Ľṹ�� 
{
	char num[10];//���� 
	char startcity[10];//�������� 
	char reachcity[10];//Ŀ�ĳ��� 
	char takeofftime[10];//����ʱ�� 
	char arrivetime[10];//����ʱ�� 
	int price;//Ʊ�� 
	int ticketnum;//Ʊ�� 
}; 

struct man//����洢��Ʊ����Ϣ�Ľṹ�� 
{
	char num[18];//ID 
	char name[10];//���� 
	int bookNum;//����Ʊ�� 
};

typedef struct node//����洢��Ʊ��Ϣ������Ľڵ�ṹ 
{
	struct train data;
	struct node *next;
}Node,*Link;

typedef struct Man
{
	struct man data;
	struct Man *next;
}book,*bookLink;

void menu(); 						//������ʾϵͳ������ 
void Traininfo(Link linkhead);		//��ӻ�Ʊ��Ϣ 
void printheader();					//�����Ʊ��Ϣ��ͷ 
void printdata(Node *q);			//��ʽ������������� 
void searchtrain(Link l);			//��ѯ��Ʊ��Ϣ 
void Bookticket(Link l,bookLink k);	//Ԥ����Ʊ 
void Modify(Link l);				//�޸Ļ�Ʊ����ϲ 
void showtrain(Link l);				//��ʾ��Ʊ��Ϣ 
void SaveTrainInfo(Link l);			//�����Ʊ��Ϣ 
void SaveBookInfo(bookLink k);		//���涩Ʊ����Ϣ

void menu()
{
	printf("\n\n");
	printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|               ��Ʊ��Ʊ����ϵͳ               |\n");
	printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|                0.�˳�ϵͳ                      |\n");
	printf("\t\t|                1.��ӻ�Ʊ��Ϣ                |\n");
	printf("\t\t|                2.��ѯ��Ʊ��Ϣ                |\n");
	printf("\t\t|                3.Ԥ����Ʊ                    |\n");
	printf("\t\t|                4.�޸Ļ�Ʊ��Ϣ                |\n");
	printf("\t\t|                5.��ʾ��Ʊ��Ϣ                |\n");
	printf("\t\t|                6.�����Ʊ�Ͷ�Ʊ����Ϣ        |\n");
	printf("\t\t|------------------------------------------------|\n");
}

void Traininfo(Link linkhead)
{
	
	struct node *p,*r,*s;			//����3��node���͵�ָ�����
	char num[10];
	r=linkhead;						//rָ��ָ��洢��Ʊ��Ϣ��������ͷ 
	s=linkhead->next;				//sָ��ָ��洢��Ʊ��Ϣ���������һ����� 
	while(r->next!=NULL)			//�ж������Ƿ�Ϊ�� 
	r=r->next;
	while(1)						//ѭ�������Ʊ��Ϣ 
	{
		printf("������𳵳���(0-����ϵͳ������)��");
		scanf("%s",num);
		if(strcmp(num,"0")==0)		//�ж�����ֵ�Ƿ�Ϊ0
		{
			break;
		}				
		while(s)					//ѭ���ж�����ֵ�Ƿ��Ѿ����� 
		{
			if(strcmp(s->data.num,num)==0)
			{
				printf("�˳��λ���'%s'�Ѿ����ڣ�\n",num);
				return;
			}
			s=s->next;				//�ƶ�����һ���ڵ� 
		}
	
		p=(struct node*)malloc(sizeof(struct node));//Ϊp��̬�����ڴ�
		strcpy(p->data.num,num);	//���복�� 
		printf("����������У�");
		scanf("%s",p->data.startcity);//�����������
		printf("����Ŀ�ĳ��У�");
		scanf("%s",p->data.reachcity);//����Ŀ�ĳ��� 
		printf("���뷢��ʱ�䣺");
		scanf("%s",p->data.takeofftime);//���뷢��ʱ�� 
		printf("���뵽��ʱ�䣺");
		scanf("%s",p->data.arrivetime); //���뵽��ʱ�� 
		printf("�����Ʊ�ۣ�");
		scanf("%d",&p->data.price); //�����Ʊ�� 
		printf("����Ԥ��Ʊ����");
		scanf("%d",&p->data.ticketnum); //����Ԥ��Ʊ��
		p->next=NULL;
		r->next=p;
		r=p;							//��r�Ƶ�p�ڵ�
		saveflag=1;						//���ô洢��־ 
	}
}

void searchtrain(Link l)
{
	Node *s[10],*r;//����һ����Ʊ��Ϣ����ڵ����͵�ָ�������һ��ָ�� 
	int sel,k,i=0;
	char str1[5],str2[10];
	if(!l->next)
	{
		printf("û�в�ѯ���κλ�Ʊ��¼��");
		return; 
	}
	printf("��ѡ���ѯ��ʽ��\n1.���ݻ𳵳��β�ѯ;\n2.����Ŀ�ĳ��в�ѯ;\n");
	scanf("%d",&sel); //����ѡ������
	if(sel==1)
	{
		printf("�����ѯ���Σ�");
		scanf("%s",str1);
		r=l->next;
		while(r!=NULL)
			if(strcmp(r->data.num,str1)==0)//�����Ƿ���������ĳ�����ƥ�����Ϣ
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
		printf("����Ŀ�ĳ��У�");
		scanf("%s",str2);
		r=l->next;
		while(r!=NULL)
			if(strcmp(r->data.reachcity,str2)==0)//�����Ƿ����������Ŀ�ĳ�����ƥ�����Ϣ
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
		printf("û�в�ѯ�������Ϣ��");
	}
	else
	{
			printheader();//�����ͷ
		for(k=0;k<i;k=k+1)
		{
			printdata(s[k]);//ѭ�������ѯ������Ϣ 
		} 
	}
}

void Bookticket(Link l,bookLink k)
{
	Node *r[10],*p;
	char ch[2],tnum[10],str[10],str1[10],str2[10];
	book *q,*h;
	int i=0,t=0,flag=0,dnum;
	q=k;//����ȡ�Ķ�Ʊ����Ϣ�����ַ��ֵ��ָ��q
	while(q->next!=NULL)//�ж϶�Ʊ����Ϣ�����Ƿ�Ϊ�� 
	q=q->next;//��qָ��Ʊ����Ϣ����β��
	printf("����Ŀ�ĳ��У�");
	scanf("%s",&str);//����Ҫ����ĳ���
	p=l->next;//ָ��pָ���Ʊ��Ϣ�����׽ڵ�
	while(p!=NULL)
	{
		if(strcmp(p->data.reachcity,str)==0)
		{
			r[i]=p;//�����������ļ�¼�浽����r��
			i=i+1; 
		}
		p=p->next; 
	}
	printf("\n\n���ѯ����%s�ĳ��ι��У�%d��\n",str,i);
		printheader();
	for(t=0;t<i;t=t+1)
		printdata(r[t]);
	if(i==0)
	{
		printf("\n��Ǹ��û���ҵ���Ҫ�Ļ𳵳��Σ�\n");
	}
	else
	{
		printf("\n��ȷ��Ҫ��Ʊ��<y/n\n");
		scanf("%s",ch);
		if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)//�ж��Ƿ�Ʊ
		{
			h=(book*)malloc(sizeof(book));
			printf("����������");
			scanf("%s",&str1);
			strcpy(h->data.name,str1);
			printf("���������֤����:");
			scanf("%s",str2);
			strcpy(h->data.num,str2);
			printf("������𳵳��Σ�");
			scanf("%s",tnum);
			for(t=0;t<i;t=t+1)
			{
				if(strcmp(r[t]->data.num,tnum)==0)
				{
					if(r[t]->data.ticketnum<1)//�ж�ʣ���Ʊ���Ƿ�С��1 
					{
						printf("��ǸûƱ�ˣ�");
						Sleep(2);
						return; 
					}
					printf("ʣ��%d�ų�Ʊ\n",r[t]->data.ticketnum);
					flag=1;
					break; 
				}
				if(flag==0)
				{
					printf("�������");
					Sleep(2);
					return; 
				}
			} 
			printf("���붩Ʊ������");
			scanf("%d",&dnum);
			r[t]->data.ticketnum=r[t]->data.ticketnum-dnum;//�ɹ�Ԥ����Ʊ����Ӧ����
			h->data.bookNum=dnum;
			h->next=NULL;
			q->next=h;
			q=h;
			printf("\nף�أ���ɹ�Ԥ����%d�ų�Ʊ��",dnum);
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
		printf("\nû����Ҫ�޸ĵļ�¼��\n");
		return;
	}
	else
	{
		printf("\n��ȷ��Ҫ�޸Ļ�Ʊ��Ϣ��(y/n)\n");
		getchar();
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n����𳵳��Σ�");
			scanf("%s",tnum);
			while(p!=NULL)
			if(strcmp(p->data.num,tnum)==0)//����������ĳ�����ƥ��ļ�¼
			{
				break; 
			}
			else
			{
				p=p->next;	
			}
			if(p)
			{
				printf("�����µĻ𳵳��Σ�");
				scanf("%s",&p->data.num);
				printf("�����µĳ������У�");
				scanf("%s",&p->data.startcity); 
				printf("�����µ�Ŀ�ĳ��У�");
				scanf("%s",&p->data.reachcity); 
				printf("�����µķ���ʱ�䣺");
				scanf("%s",&p->data.takeofftime); 
				printf("�����µĵ���ʱ�䣺");
				scanf("%s",&p->data.arrivetime); 
				printf("�����µĻ�Ʊ�ۣ�");
				scanf("%d",&p->data.price); 
				printf("�����µ�Ԥ��Ʊ����");
				scanf("%d",&p->data.ticketnum); 
				printf("\n�޸ļ�¼�ɹ���\n");
				saveflag=1;	
			}
			else
			{
				printf("\nû�д˳��μ�¼��"); 
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
void showtrain(Link l)//�Զ��庯����ʾ��Ʊ��Ϣ 
{
	Node* p;
	p=l->next;
	printheader();
	if(l->next==NULL)
	{
		printf("û�д��г���Ʊ��¼��"); 
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
		printf("�޷��򿪱����Ʊ��Ϣ���ļ���");
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
			printf("������%d���𳵵ĳ�Ʊ��¼\n",count);
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
		printf("�޷��򿪱��涩Ʊ����Ϣ���ļ���");
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
			printf("������%d�ݶ�Ʊ�˼�¼\n",count);
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
	fp1=fopen("train.txt","ab+");	//�򿪴洢��Ʊ��Ϣ���ļ� 
	if((fp1==NULL))												 	//�ļ�δ�ɹ��� 
	{
		printf("�޷��򿪱����Ʊ��Ϣ���ļ���");
		return 0; 
	}
	while(!feof(fp1))												//�ж��ļ����Ƿ񵽽�β 
	{
		p=(Node*)malloc(sizeof(Node));							 	//Ϊp��̬�����ڴ� 
		if(fread(p,sizeof(Node),1,fp1)==1)							//��ָ�������ļ���ȡ��¼ 
		{
			p->next=NULL;
			r->next=p;												//�������� 
			r=p;
		}
	}
	fclose(fp1);													//�ر��ļ� 
	fp2=fopen("man.txt","ab+");		//�򿪴洢��Ʊ����Ϣ���ļ� 
	if((fp2==NULL))													//�ļ�Ϊ�ɹ��� 
	{
		printf("�޷��򿪱��涩Ʊ����Ϣ���ļ���");
		system("pause"); 
		return 0;
	}
	while(!feof(fp2))												//�ж��ļ����Ƿ񵽽�β 
	{
		t=(book*)malloc(sizeof(book));								//Ϊt��̬�����ڴ� 
		if(fread(t,sizeof(book),1,fp2)==1)							//��ָ�������ļ���ȡ��¼ 
		{
			t->next=NULL;
			h->next=t;												//�������� 
			h=t;
		}
	}
	fclose(fp2);													//�ر��ļ� 
	while(1)
	{
		system("cls");												//����	 
		menu();														//����nemu()�����溯�� 
		printf("\t��ѡ��(0-6):");
		scanf("%d",&sel);
		system("cls");
		if(sel==0)
		{
			if(saveflag==1)											//�˳�ʱ�ж���Ϣ�Ƿ񱣴� 
			{
				getchar();
				printf("\n�ļ��Ѿ��޸ģ��Ƿ񱣴�(y/n)?\n");
				scanf("%c",&ch1);
				if(ch1=='y'||ch1=='Y')
				{
					SaveBookInfo(k);
					SaveTrainInfo(l); 
				}
			}
			printf("\nлл����ӭ�ٴι��٣�\n");
			break;
		}
	
	switch(sel)														//���ݲ�ͬ��selֵ�Ĳ�ͬѡ����Ӧ���� 
	{
		case 1:
			Traininfo(l);								//������ӻ�Ʊ��Ϣ�ĺ��� 
			break;
		case 2:
			searchtrain(l);										//���ò�ѯ��Ʊ��Ϣ�ĺ��� 
			break;
		case 3:
			Bookticket(l,k);										//����Ԥ����Ʊ�ĺ��� 
			break;
		case 4:
			Modify(l);											//�����޸Ļ�Ʊ��Ϣ�ĺ��� 
			break;
		case 5:
			showtrain(l);											//������ʾ��Ʊ��Ϣ�ĺ��� 
			break;
		case 6:
			SaveTrainInfo(l);										//���ñ����Ʊ��Ϣ�ĺ��� 
			SaveBookInfo(k);										//���ñ��涩Ʊ����Ϣ�ĺ��� 
			break;
		case 0:
			return 0;
	}
	printf("\n�����������...");
	system("pause");
	getch();
	}
}
