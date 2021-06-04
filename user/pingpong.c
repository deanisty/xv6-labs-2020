#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char* itoa(int num, char *str);

int
main(int argc, char *argv[]) {
    char str[5];
    int p[2];
    char buf[4];
    int rl;


    pipe(p);

    int fk = fork();

    if(fk == 0) {
        itoa(getpid(), str);

	rl = read(p[0], buf, 4);

        write(1, str, 1);
	// write(1, "c", 1);
        write(1, ":", 1);

	if(rl > 0) {
	    write(1, " received ", 10);
	    write(1, buf, rl);
	    write(p[1], "pong", 4);
	}
	write(1, "\n", 1);
        exit(0);
    } else if(fk > 0) {
        itoa(getpid(), str);

	write(p[1], "ping", 4);

	wait(0);

	rl = read(p[0], buf, 4);

        write(1, str, 1);
	// write(1, "p", 1);
        write(1, ":", 1);

        write(1, " received ", 10);
	write(1, buf, rl);
	write(1, "\n", 1);

	exit(0);
    } else {
        fprintf(1, "fork failed", 12);
	exit(1);
    }
}

char* itoa(int num, char *str) {
    char index[] = "0123456789";
    int i = 0;
    // 生成每个数字对应的字符
    do {
        str[i++] = index[num%10];
	num /= 10;
    }while(num);

    str[i] = '\0';
    // switch
    char tmp;
    for(int j = 0; j <= (i-1)/2; j++) {
	tmp = str[j];
    	str[j] = str[i - 1 -j];
	str[i-1-j] = tmp;	
    }

    return str;
}
