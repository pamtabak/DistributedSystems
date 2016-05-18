#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	int n = 17;
	int k = 5;

	int *v = (int *) calloc(0, n * sizeof(int));

	int c = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = c; j < n; j += k)
		{
			v[j] = 1;
		}
		c++;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d\n", v[i]);
	}
	return 0;
}

