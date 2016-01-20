#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv )
{
	int index, c, iflag = 0, fflag = 0, sflag = 0;
	char *fvalue = NULL;
	while( (c = getopt(argc, argv, ":f:is")) != -1 )
		switch (c) {
		case 'f' :
			fflag = 1;
			fvalue = optarg;
			break;
		case 'i' :
			iflag = 1;
			break;
		case 's' :
			sflag = 1;
			break;
		case '?' :
			printf("Unknown option '-%c'\n", optopt);
			break;
		case ':' :
			printf(" '-%c' missing option argument\n", optopt);
			break;
		}
	printf("%d  %s  %d  %d\n", fflag, fvalue, iflag, sflag );
	return 0;
}
