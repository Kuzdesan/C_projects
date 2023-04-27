#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <poll.h>
#include "intgrl.h"

float *valid(int argc, const char *argv[]) {
    if (argc != 3) { exit(ArgError); }
    int len;
    float res = 0.0;
    float *out = malloc(sizeof(float) * 2);

    if (sscanf(argv[1], "%f %n", &res, &len) == 1 && len == (int) strlen(argv[1])) {
        out[0] = res;
        res = 0.0;

    } else {
        errExit("Arguments error");
    }
    if (sscanf(argv[2], "%f %n", &res, &len) == 1 && len == (int) strlen(argv[2])) {
        out[1] = res;
    } else {
        errExit("Arguments error");
    }
    return out;

}


float function(float x) {
    return (cos(x));
}

float calcSum(float begin, float end) {
    double prtSum;
    prtSum = (end - begin) * (function((end + begin) / 2));
    printf("Counted for 1 step: %f [PID: %d]\n", prtSum, getpid());
    return prtSum;
}
