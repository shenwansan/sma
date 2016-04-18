/************************************************************************
*   文件名：kmp01.c
*   文件描述：kmp函数接口
*	函数思路:在匹配过程中，利用子串中的预处理模式，加快不匹配时候待检查字符串的移动速度。
*	创建人： SJW, 2016年4月18日
*   版本号：1.0
*   修改记录：
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*================================================================
 * 函 数 名：next_arr
 * 参    数1：待检查的字符串
 * 参    数2：处理完的next数组
 * 功能描述:对待匹配子串预处理，记录每一个字符可以跳转的位置
 * 返 回 值：成功:0，失败-1
 * 抛出异常：
 ================================================================*/
int next_arr(char *substr, int * next)
{
	int len = strlen(substr);
	int i = len -1;
	int j = i - 1;
	memset(next, 0, sizeof(int) * len);
	while(i>=0 && j>=0)
	{
		while(j>=0)
		{
			if(substr[i] == substr[j])
			{
				next[i] = j;
				break;
			}
			j--;
		}
		i--;
		j=i-1;
	}
	return 0;
}

/*================================================================
 * 函 数 名：kmp_serach
 * 参    数1：待检查的字符串
 * 参    数2：待匹配子串
 * 参    数3：next数组
 * 功能描述:匹配子串，对每一个匹配失败的字符，回溯一位计算偏移位置，加快移动速度
 * 返 回 值：成功:0，失败-1
 * 抛出异常：
 ================================================================*/
int kmp_serach(char * deststr,char * substr, int * next)
{
	if(deststr==NULL||substr==NULL||next==NULL||strlen(deststr) < strlen(substr))
		goto ERR;
	
	int len_des = strlen(deststr);
	int len_sub = strlen(substr);
	
	int i = len_sub - 1;
	int j = len_sub - 1;
	int move;
	
	while(i  <  len_des)
	{
		int k = i;
		while(j >= 0)
		{
			if(deststr[k] != substr[j])
			{
				if(j != len_sub - 1)
					move = j + 1 - next[j + 1];
				else	
					move = 1;
				break;	
			}
			j--;
			k--;
		}
		if(j == -1)
		{
			printf("\nfind=%d\n",i - len_sub  + 1);
			return 0;
		}	
	
		i+= move;
		j = len_sub - 1;
	}

ERR:
	printf("\ncan not find substring\n");
	return -1;
}

int main()
{
	char * deststr="absaddsasfasdfasdfsasf";
	char * substr="asdf";
	int len = strlen(substr);
	int next[len];
	int i = 0;
	memset(next, 0, sizeof(int) * len);
	
	next_arr(substr, next);
	
	kmp_serach( deststr, substr,  next);
	
	//for(i = 0;i< len;i++)
	//	printf("%d\n",next[i]);

	return 0;
}
