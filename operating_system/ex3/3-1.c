#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define PAGE_NUM  320    // 指令序列（用页数表示）
#define BLOCK 6   // 用户页面容量

void init(int page_seq[]) //生成页  
{
	srand((unsigned)time(NULL));
	int m = rand() % 320;
	for (int i = 0; i < PAGE_NUM; i += 4)
	{
		page_seq[i] = m / 10;
		page_seq[i + 1] = (m + 1) / 10;
		m = rand() % m;
		page_seq[i + 2] = m / 10;
		page_seq[i + 3] = (m + 1) / 10;
		m = (rand() % (320 - m) + m);
	}
}

int sum_found(int found[])
{
	int i;
	int sum = 0;
	for (i = 0; i < BLOCK; i++)
		sum += found[i];
	return sum;
}

int opt(int page_seq[])
{
	int p;
	int i, j;
	int found[BLOCK] = { 0 };
	int block[BLOCK];
	int lack = 0;
	for (i = 0; i < BLOCK; i++)
		block[i] = -1;
	for (i = 0; i < PAGE_NUM; i++)
	{
		for (p = 0; p < BLOCK; p++)
			found[p] = 0;
		for (p = 0; p < BLOCK; p++)
			if (block[p] == page_seq[i])
				break;
		if (p == BLOCK)
		{
			lack++;
			//for (p = 0; p < BLOCK; p++)
			//	printf("%d\t", block[p]);
			//printf("\nlack_page_number :%d\n", page_seq[i]);
			for (j = i + 1; j < PAGE_NUM; j++)
			{
				for (p = 0; p < BLOCK; p++)
					if (block[p] == page_seq[j])
					{
						found[p] = 1;
						break;
					}
				if (sum_found(found) == 3)
					break;
				else continue;
			}
			if (sum_found(found) == 3)
				block[p] = page_seq[i];
			else
				for (p = 0; p < BLOCK; p++)
					if (found[p] == 0 || block[p] == -1)
					{
						block[p] = page_seq[i]; break;
					}
		}
	}
	return lack;
}

int fifo(int page_seq[])
{
	int rear = -1;
	int i, p, k;
	int lack = 0, replace = 0;
	int block[BLOCK];
	for (i = 0; i < BLOCK; i++)
		block[i] = -1;
	for (i = 0; i < PAGE_NUM; i++)
	{
		for (p = 0; p < BLOCK; p++)
			if (block[p] == page_seq[i])
			{
				replace = block[p];
				while (p < rear)
				{
					block[p] = block[p + 1];
					p++;
				}
				block[rear] = replace;
				break;
			}
		if (p == BLOCK)
		{
			lack++;
			//for (p = 0; p < BLOCK; p++)
			//	printf("%d\t", block[p]);
			//printf("\nlack_page_number :%d\n", page_seq[i]);
			for (p = 0; p < BLOCK; p++)
				if (block[p] == -1)
				{
					block[p] = page_seq[i];
					rear = rear + 1;
					break;
				}
			if (p == BLOCK)
			{
				for (p = 0; p < BLOCK - 1; p++)
					block[p] = block[p + 1];
				block[BLOCK - 1] = page_seq[i];
				//for (k = 0; k < BLOCK; k++)//////////
				//	printf("%d\t", block[k]);
				//printf("\n");////////////
			}
		}
	}
	return lack;
}

int lru(int page_seq[])
{
	int p;
	int i, j;
	int found[BLOCK] = { 0 };
	int block[BLOCK];
	int lack = 0;
	for (i = 0; i < BLOCK; i++)
		block[i] = -1;
	for (i = 0; i < PAGE_NUM; i++)
	{
		for (p = 0; p < BLOCK; p++)
			found[p] = 0;
		for (p = 0; p < BLOCK; p++)
			if (block[p] == page_seq[i])
				break;
		if (p == BLOCK)
		{
			lack++;
			//for (p = 0; p < BLOCK; p++)
			//	printf("%d\t", block[p]);
			//printf("\nlack_page_number :%d\n", page_seq[i]);
			for (j = i - 1; j >= 0; j--)
			{
				for (p = 0; p < BLOCK; p++)
					if (block[p] == page_seq[j])
					{
						found[p] = 1;
						break;
					}
				if (sum_found(found) == 3)
					break;
				else continue;
			}
			if (sum_found(found) == 3)
				block[p] = page_seq[i];
			else
				for (p = 0; p < BLOCK; p++)
					if (found[p] == 0 || block[p] == -1)
					{
						block[p] = page_seq[i]; break;
					}
		}
	}
	return lack;
}

int main(void)
{
	int page_seq[PAGE_NUM];
	int lack = 0;
	float lack_rate = 0.0;
	init(page_seq);
	// for(i=0;i<BLOCK;i++) /*Initiate the physical block*/
	//  block[i]=-1;
	lack = opt(page_seq);
	lack_rate = (1.0*lack) / PAGE_NUM;
	printf("OPT:  缺页次数=%d\t缺页率=%f\n\n", lack, lack_rate);
	lack = fifo(page_seq);
	lack_rate = (1.0*lack) / PAGE_NUM;
	printf("FIFO:   缺页次数=%d\t缺页率=%f\n\n", lack, lack_rate);
	lack = lru(page_seq);
	lack_rate = (1.0*lack) / PAGE_NUM;
	printf("LRU:   缺页次数=%d\t缺页率=%f\n\n", lack, lack_rate);

	//for (int i = 0; i < PAGE_NUM; i ++)
	//{
	//	printf("%d    ", page_seq[i]);
	//}
	return 1;
}
