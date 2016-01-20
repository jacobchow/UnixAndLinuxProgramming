#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv)
{
	int fd;
	if ( (fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0644) ) < 0 )
	{
		printf("open file failed!");
		return 1;
	}
	if( dup2(fd, STDOUT_FILENO) == -1 )
		return 1;
	printf("this is a test program for redirect.\n");
	close(fd);
	return 0;
}
