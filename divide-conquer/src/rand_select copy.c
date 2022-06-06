#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "graph_utils.h"


int main(int argc, const char *argv[])
{
    srand(time(NULL));

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../data/kargerMinCut.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);

    exit(EXIT_SUCCESS);
}