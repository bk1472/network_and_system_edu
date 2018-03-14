#include <stdio.h>
#include <string.h>

int main()
{
	char arr[] = { 1, 2, 3, 4, 5 };
	
	memcpy(arr, arr + 1, 3);

	for (int i = 0 ; i < 5; ++i)
		printf("%d\n", arr[i]);
}
