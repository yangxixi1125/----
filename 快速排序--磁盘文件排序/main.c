#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM 4
//学生数据结构体
struct data
{
	char name[20];
	char school[20];
	char city[20];
	char province[20];
}info;
//学生资料
struct data addrs[NUM] =
{
	"WenHai","BIT","JiLIn","jilin",
	"tongwei","BIT","zhengjiang","jiangsu",
	"SunYou","BIT","WeiFang","ShangDong",
	"XiaoMing","PKU","TaiYuan","ShanXi"
};
//函数声明
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
	//读写生成文本文件
	fopen_s(&fp, "datalist.txt", "w+");
	if (fp == NULL)
	{
		printf("\n打开文件失败");
		exit(0);
	}
	printf("\n将未排序数据写入文件\n");
	fwrite(addrs, sizeof(addrs), 1, fp);
	//打印文件中的数组
	for (i = 0; i < NUM; i++)
	{
		struct data *p;
		p = get_data(fp, i);
		print_data(p);
		printf("\n");
	}
	fclose(fp);
	//二进制方式打开文件
	fopen_s(&fp, "datalist.txt", "rb+");
	if (fp  == NULL)
	{
		printf("\n不能以读写方式打开文件");
		exit(0);
	}

	printf("\n将文件数据排序");
	//文本中结构体字符串快速排序
	quick_disk(fp, NUM);
	printf("\n排序结束");
	//打印排序后结构体
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
//文件中结构体排序函数
void quick_disk(FILE *fp, int count)
{
	qs_disk(fp, 0, count - 1);
}
//文件中结构体排序函数---上面函数涉及参数少
void qs_disk(FILE *fp, int left, int right)
{
	long int i, j;
	char x[30];
	i = left;
	j = right;

	//快速排序，选择中间一个值做key，两边开始比较交换
	//运用递归，结束条件，排序的只有一个元素
	if (i == j)
		return;
	strcpy_s(x, sizeof(info), get_name(fp, (long)(i + j) / 2));
	//两边比较，找到需要交换的元素。最终左边全是小于等于key,右边全是大于等于key。
	//i,j值有三种情况;j指向小于key的值，当i=j-1时，i指向大于等于key值，交换后i-j=1；；；当i=j-1时，i指向小于key值，执行后i-j=1。
	//                j指向大于等于key值，当i=j-1时，i指向大于等于key值，i不变j减小，最后i-j=1；；；当i=j-1时，i指向小于key值，i=j，j减小，最后i-j=1。
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

//交换文件中i和j对应的元素
void exchangedata(FILE *fp, long i, long j)
{
	char a[sizeof(info)], b[sizeof(info)];
	//读取i和j对应元素
	fseek(fp, sizeof(info)*i, SEEK_SET);
	fread(a, sizeof(info), 1, fp);
	fseek(fp, sizeof(info)*j, SEEK_SET);
	fread(b, sizeof(info), 1, fp);
	//交换写入
	fseek(fp, sizeof(info)*i, SEEK_SET);
	fwrite(b, sizeof(info), 1, fp);
	fseek(fp, sizeof(info)*j, SEEK_SET);
	fwrite(a, sizeof(info), 1, fp);
	return;
}

//得到文件中rec对应的元素的name字符数组指针
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

//打印结构体函数
void print_data(struct data *p)
{
	printf("姓名：%s\n", p->name);
	printf("学校：%s\n", p->school);
	printf("城市：%s\n", p->city);
	printf("省  ：%s\n", p->province);

	return;
}