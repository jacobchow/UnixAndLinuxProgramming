#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int global = 5;
int main()
{
	pid_t pid;
	char *string = "I am parent";
	int local = 10;
	printf(" before fork --- \n");
	local++;
	if((pid = fork()) < 0 )
		return 1;
	if( pid ==0 )
	{
		 string = "I am child";
		 printf("%s, my pid = %d: global = %d, local = %d\n", string, getpid(), global, &global );
		 global++;
		// printf("%s, my pid = %d: global = %d, local = %d\n", string, getpid(), global, local );
	}
	else
	{
		 printf("%s, my pid = %d: global = %d, local = %d\n", string, getpid(), global, &global );
		 local++;
		// printf("%s, my pid = %d: global = %d, local = %d\n", string, getpid(), global, local );
	}
	return 0;
}
