#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    char *buf = itoa(300);
    write(1, buf, strlen(buf));
}

char *itoa(int num) {/*{{{*/
    int length = 0;
    char index[] = "0123456789";
    int i = num;
    do {
        i /= 10;
        length++;
    }while(i);

    char *str = malloc(sizeof(char) * length);

    // 生成每个数字对应的字符
    do {
        str[--length] = index[num%10];
        num /= 10;
    }while(num);

    str[i] = '\0';

    return str;
}/*}}}*/
