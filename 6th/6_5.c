#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void parse(char *buf, char *args[ ])
{
	int i = 0;
	while ( *buf != '\0')
	{
		args[i++] = buf;
		while( (*buf == '\0') || (*buf == '\t' || (*buf == '\n') ))   *buf++ = '\0';
		while( (*buf != '\0') && (*buf != '\t') && (*buf != '\n') )   buf++;
	}
	args[i] = '\0';
}
void execute(char *args[])
{
	int pid, status;
	if( ( pid = fork() ) < 0 )
		exit(1);
	if (pid == 0)
	{
		if( execvp(*args, args) == -1 )
			printf("no such file.\n");
		exit(0);
	}
	waitpid(pid, &status, 0);
}
int main()
{
	char buf[1024];
	char *args[64], *cp;
	for( ; ; )
	{
		printf( "Command: " );
		cp = fgets(buf, sizeof(buf), stdin);
		if(cp == NULL)
		{
			printf("quit\n");
			exit(0);
		}
		if(*cp == '\n')
			continue;
		//printf("%s", buf);
		parse(buf, args);
		execute(args);
	}
}
