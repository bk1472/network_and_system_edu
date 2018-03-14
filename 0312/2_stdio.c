// stdio - Standard Input / Ouput
//  표준 입출력 라이브러리

// stdin   => line
// stdout  => line
// stderr  => no buffering
// 일반적인 파일 => full buffering

//  => FILE*
//  => 버퍼링
#include <stdio.h>

int main()
{
	// printf("test logging....");
	fprintf(stderr, "test logging...");
	// 1. '\n'
	// putchar('\n');

	// 2. 스트림(FILE)의 버퍼를 강제로 비우는 라이브러리 함수
	// fflush(stdout);
	// : fflush(stdin) 표준이 아닙니다. Windows 에서만 동작합니다.

	while (1)
		;
}
