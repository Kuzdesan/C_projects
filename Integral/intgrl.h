#define errExit(msg)    do { perror(msg); _exit(EXIT_FAILURE); } while (0)

#define N 10
#define ArgError 9

float *valid(int argc, const char *argv[]);

float function(float x);

float calcSum(float begin, float end);

