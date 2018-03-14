#include <stdio.h>

int main(int argc, char* argv[])
{
	int ch = 0;
	int size = 0;

	// getchar() 함수가 정수를 반환하는 이유는 EOF를 처리하기
	// 위해서 입니다.
	//  : 텍스트는 상관이 없습니다
	// 0x000000FF  -> 데이터를 반환
	// 0xFFFFFFFF  -> EOF
	while ((ch = getchar()) != EOF)
		++size;

	printf("size: %d\n", size);
}
