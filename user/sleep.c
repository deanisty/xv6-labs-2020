#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int time = 0;
    if(argc <= 1) {
	write(1, "missing time...\n", 16);
	exit(1);
    }
    time = atoi(argv[1]);
    exit(sleep(time));
}
