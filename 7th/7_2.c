#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sig_usr( int sig )
{
	printf("get signal\n");
}
int main()
{
	signal(SIGUSR1, sig_usr);
	for(;;)
		pause();
	return 0;
}
