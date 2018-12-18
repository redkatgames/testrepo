

#include <stdio.h>

int main()
{
	unsigned short int i = 0;

	printf("sizeof %u \n", sizeof i);

	i = 65535;
	printf("%u \n", i);

	i+=2;
	printf("%u \n", i);

	return 0;
}
