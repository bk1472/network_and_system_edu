// 표준 라이브러리 파일 입출력 - 고수준 IO 
// => 버퍼링

// 일반적인 파일 입출력 
// => 풀 버퍼링: 버퍼가 가득차야 비워진다.
#include <stdio.h>

// task_struct
// start_kernel
int main()
{
	//                           "wt", "wb": Windows
	// 유닉스는 텍스트와 바이너리에 처리에 있어서 차이가 없습니다.
	// "r": 존재하는 파일이 없을 경우 에러
	// "w : 기존의 파일이 존재하지 않으면 새롭게 생성하고,
	//      존재한다면 덮어쓴다. 
	FILE* fp = fopen("test.txt", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "file open error...\n");
		return -1;
	}

	// 버퍼의 크기: 라이브러리의 구현에 의존한다.
	//    4K / 8K / 16K

	fprintf(fp, "Hello, Network Linux Programming...\n");
	fflush(fp);
	getchar();

	fclose(fp);
}
