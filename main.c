#include <stdlib.h>
#include <stdio.h>

int main()
{
	if (malloc(9223372036854775807) == NULL)
	{
		printf("Too big malloc\n");
		perror("");
	}
	return 0;
}
