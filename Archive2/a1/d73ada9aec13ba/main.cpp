#include<stdio.h>
#define NUM 5

typedef struct Student
{
    int no; /*番号*/
	char name[10]; /*氏名*/
	int score; /*得点*/
}Student;

/*int search(student date[],int no);*/

int main(void)
{
	Student student[NUM] =
	{
		{ 1,"taro.s",100 },
		{ 2,"jiro.y",80 },
		{ 4,"saburo.h",65 },
		{ 5,"shiro.k",20 },
		{ 8,"goro.s",93 },
	};

	int i;
	int ban;

	printf("───────────────────────────────────\n");
	printf("番号│ 氏名 │ 得点\n");
	printf("───────────────────────────────────\n");
	for (i = 0; i < NUM; i++)
	{
		printf("%4d│%10s│%5d\n", student[i].no, student[i].name, student[i].score);
	}
	printf("───────────────────────────────────\n");

	printf("検索する番号を入力してください:");
	scanf("%d", &ban);

	if (0 <= ban&&NUM > ban)
	{
		printf("番号：%d\n", student[ban].no);
		printf("氏名：%s\n", student[ban].name);
		printf("得点：%d\n", student[ban].score);

		return 0;
	}
	else
	{
		return -1;
	}
}
