#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM 4
//ѧ�����ݽṹ��
struct data
{
	char name[20];
	char school[20];
	char city[20];
	char province[20];
}info;
//ѧ������
struct data addrs[NUM] =
{
	"WenHai","BIT","JiLIn","jilin",
	"tongwei","BIT","zhengjiang","jiangsu",
	"SunYou","BIT","WeiFang","ShangDong",
	"XiaoMing","PKU","TaiYuan","ShanXi"
};
//��������
void quick_disk(FILE *fp, int count);
void qs_disk(FILE *fp, int left, int right);
void exchangedata(FILE *fp, long i, long j);
struct data *get_data(FILE *fp, long rec);
char *get_name(FILE *fp, long rec);
void print_data(struct data *p);


void main(void)
{
	int i;
	FILE *fp = NULL;
	//��д�����ı��ļ�
	fopen_s(&fp, "datalist.txt", "w+");
	if (fp == NULL)
	{
		printf("\n���ļ�ʧ��");
		exit(0);
	}
	printf("\n��δ��������д���ļ�\n");
	fwrite(addrs, sizeof(addrs), 1, fp);
	//��ӡ�ļ��е�����
	for (i = 0; i < NUM; i++)
	{
		struct data *p;
		p = get_data(fp, i);
		print_data(p);
		printf("\n");
	}
	fclose(fp);
	//�����Ʒ�ʽ���ļ�
	fopen_s(&fp, "datalist.txt", "rb+");
	if (fp  == NULL)
	{
		printf("\n�����Զ�д��ʽ���ļ�");
		exit(0);
	}

	printf("\n���ļ���������");
	//�ı��нṹ���ַ�����������
	quick_disk(fp, NUM);
	printf("\n�������");
	//��ӡ�����ṹ��
	for (i = 0; i < NUM; i++)
	{
		struct data *p;
		p = get_data(fp, i);
		print_data(p);
		printf("\n");
	}
	fclose(fp);

	return;
}
//�ļ��нṹ��������
void quick_disk(FILE *fp, int count)
{
	qs_disk(fp, 0, count - 1);
}
//�ļ��нṹ��������---���溯���漰������
void qs_disk(FILE *fp, int left, int right)
{
	long int i, j;
	char x[30];
	i = left;
	j = right;

	//��������ѡ���м�һ��ֵ��key�����߿�ʼ�ȽϽ���
	//���õݹ飬���������������ֻ��һ��Ԫ��
	if (i == j)
		return;
	strcpy_s(x, sizeof(info), get_name(fp, (long)(i + j) / 2));
	//���߱Ƚϣ��ҵ���Ҫ������Ԫ�ء��������ȫ��С�ڵ���key,�ұ�ȫ�Ǵ��ڵ���key��
	//i,jֵ���������;jָ��С��key��ֵ����i=j-1ʱ��iָ����ڵ���keyֵ��������i-j=1��������i=j-1ʱ��iָ��С��keyֵ��ִ�к�i-j=1��
	//                jָ����ڵ���keyֵ����i=j-1ʱ��iָ����ڵ���keyֵ��i����j��С�����i-j=1��������i=j-1ʱ��iָ��С��keyֵ��i=j��j��С�����i-j=1��
	do
	{
		while ((strcmp(x, get_name(fp, i)) > 0) && (i <= j))
			i++;
		while ((strcmp(x, get_name(fp, j)) < 0) && (j >= i))
			j--;
		if (i < j)
		{
			exchangedata(fp, i, j);
			i++;
			j--;
		}
	} while (i <= j);

	qs_disk(fp, left, j);
	qs_disk(fp, i, right);
	return;
}

//�����ļ���i��j��Ӧ��Ԫ��
void exchangedata(FILE *fp, long i, long j)
{
	char a[sizeof(info)], b[sizeof(info)];
	//��ȡi��j��ӦԪ��
	fseek(fp, sizeof(info)*i, SEEK_SET);
	fread(a, sizeof(info), 1, fp);
	fseek(fp, sizeof(info)*j, SEEK_SET);
	fread(b, sizeof(info), 1, fp);
	//����д��
	fseek(fp, sizeof(info)*i, SEEK_SET);
	fwrite(b, sizeof(info), 1, fp);
	fseek(fp, sizeof(info)*j, SEEK_SET);
	fwrite(a, sizeof(info), 1, fp);
	return;
}

//�õ��ļ���rec��Ӧ��Ԫ�ص�name�ַ�����ָ��
char *get_name(FILE *fp, long rec)
{
	struct data *p;
	p = &info;
	rewind(fp);
	fseek(fp, sizeof(info)*rec, SEEK_SET);
	fread(p, sizeof(info), 1, fp);
	return p->name;
}
struct data *get_data(FILE *fp, long rec)
{
	struct data *p;
	p = &info;
	rewind(fp);
	fseek(fp, sizeof(info)*rec, SEEK_SET);
	fread(p, sizeof(info), 1, fp);
	return p;
}

//��ӡ�ṹ�庯��
void print_data(struct data *p)
{
	printf("������%s\n", p->name);
	printf("ѧУ��%s\n", p->school);
	printf("���У�%s\n", p->city);
	printf("ʡ  ��%s\n", p->province);

	return;
}