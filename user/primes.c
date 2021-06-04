#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define CHAR2INT(ch) *((int *)ch)

// methods ref
static void wint_to_fd(int fd, int num);/*{{{*/
static void accept_number(int in);
static void write_fork_error(); /*}}}*/

int
main(int argc, char *argv[]) {/*{{{*/
    int p[2];
    int i;

    pipe(p);

    int child = fork();

    if(child < 0) {
        write_fork_error();
    }

    if(child == 0) {
        // child
        close(p[1]);
        accept_number(p[0]);
        close(p[0]);
        exit(0);
    } else {
        // parent
        close(p[0]);
        for(i = 2; i <= 35; i++) {
            wint_to_fd(p[1], i);
        }

        close(p[1]);
        wait(0);
        exit(0);
    }
}/*}}}*/

static void 
accept_number(int in) {/*{{{*/
    int p[2];
    int base = 0;
    char buf[4];
    int child_pid = 0;
    int rl;


    do {
        rl = read(in, buf, 4);
        if(rl <= 0) {
            break;
        }
        if(base == 0) {
            base = CHAR2INT(buf);
            // print
            printf("prime %d\n", base);
        } else {
            // pass to right
            if(CHAR2INT(buf) % base > 0) {
                // no child
                if(child_pid == 0) {
                    if(pipe(p) < 0) {
                        printf("%d:%s\n", getpid(), "pipe create error");
                        exit(-1);
                    }
                    child_pid = fork();
                    if(child_pid < 0) {
                        write_fork_error();
                    } else if(child_pid == 0) {
                        close(p[1]);
                        accept_number(p[0]);
                    } else {
                        close(p[0]);
                    }
                }

                wint_to_fd(p[1], CHAR2INT(buf));
            }
        }
    } while(rl > 0);

    // close(in);
    close(p[1]);
    wait(0);
    exit(0);
}/*}}}*/

static void 
wint_to_fd(int fd, int num) {/*{{{*/
    int *j;
    j = &num;
    write(fd, (char *) j, 4);
}/*}}}*/

static void 
write_fork_error() {/*{{{*/
    printf("%s\n", "fork error");
    exit(1);
}/*}}}*/
