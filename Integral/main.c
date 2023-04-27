#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <poll.h>
#include "intgrl.h"


int main(int argc, const char *argv[]) {
    float *parms = valid(argc, argv);
    int nfds, num_open_fds;
    struct pollfd *pfds;

    float globalBegin, globalEnd, begin, end, step, sum, tmp;
    pid_t pid[N];
    int pipefd[N][2], sign, ready;
    char buff[20];
    float calculationOut;
    int i;
    sum = 0;
    sign = 0;

    srand(time(NULL));

    num_open_fds = nfds = N;
    pfds = calloc(nfds, sizeof(struct pollfd));
    if (pfds == NULL) errExit("malloc");

    globalBegin = parms[0];
    globalEnd = parms[1];
    if (globalBegin > globalEnd) {
        tmp = globalEnd;
        globalEnd = globalBegin;
        globalBegin = tmp;
        sign = 1;
    }
    step = fabs(globalEnd - globalBegin) / N;
    for (i = 0; i < N; i++) {
        if (pipe(pipefd[i])) {
            errExit("Pipe error");
        }
        pfds[i].fd = pipefd[i][0];
        pfds[i].events = POLLIN;
        begin = globalBegin + step * i;
        end = globalEnd - step * (N - 1 - i);
        if ((pid[i] = fork()) == -1) errExit("fork");
        if (pid[i] == 0) {
            close(pipefd[i][0]);
            calculationOut = calcSum(begin, end);
            sprintf(buff, "%f", calculationOut);
            write(pipefd[i][1], buff, 20);
            memset(buff, 0, sizeof(buff));
            close(pipefd[i][1]);
            _exit(0);
        } else {
            close(pipefd[i][1]);
        }
    }


    //printf("poll\n");
    while (num_open_fds > 0) {
        for (i = 0; i < N; i++) pfds[i].revents = 0;
        if ((ready = poll(pfds, nfds, -1)) == -1) errExit("poll");
        for (i = 0; i < N; i++) {
            if (pfds[i].revents & POLLIN) {
                read(pipefd[i][0], buff, 20);
                sum += atof(buff);
                dprintf(STDOUT_FILENO, "Read calculation result for 1 step %f PID: %d\n", atof(buff), pid[i]);
                if (pfds[i].revents & POLLHUP) {
                    dprintf(STDOUT_FILENO, "POLLHUP\n");
                    close(pfds[i].fd);
                    pfds[i].fd = -1;
                    pfds[i].events = 0;
                    num_open_fds--;
                }
            } else if (pfds[i].revents & POLLHUP) {
                dprintf(STDOUT_FILENO, "POLLHUP\n");
                close(pfds[i].fd);
                pfds[i].fd = -1;
                pfds[i].events = 0;
                num_open_fds--;
            }

        }
    }

    if (sign == 1) {
        sum *= -1;
    }
    printf("\n\n\nResult:%f\n", sum);
    return 0;
}
