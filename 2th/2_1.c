#include <stdio.h>
#include <errno.h>

int main()
{
	FILE *stream;
	char buf[80];
	printf("open and create test file!\n");
	if( (stream = fopen("testFile", "w")) == NULL )
	{
		printf("fopen() failed");
		return 1;
	}
	printf("write string to test file!\n");
	fputs("Hello World!", stream);
	if( (stream = freopen("testFile", "r", stream )) == NULL )
	{
		printf("fopen() failed");
		return 1;
	}
	printf("read string from test file!\n");
	fgets( buf, sizeof(buf), stream);
	printf("The string is \" %s \" \n", buf );
	fclose(stream);
	return 0;
}
