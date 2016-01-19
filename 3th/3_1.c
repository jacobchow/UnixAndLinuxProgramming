#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv)
{
	int from, to;
	int n;
	char buf[1024];
	if( argc != 3 )
	{
		printf("Usage : %s  from-file  to-file\n", argv[0] );
		return 1;
	}
	if ( (from = open(argv[1], O_RDONLY) ) < 0 )
	{
		printf("open file failed!");
		return 1;
	}
	if ( (to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644) ) < 0 )
	{
		printf("open file failed!");
		return 1;
	}
	while( (n = read(from, buf, sizeof(buf) ) ) > 0)
		write(to, buf, n);
	close(from);
	close(to);
	return 0;
}
