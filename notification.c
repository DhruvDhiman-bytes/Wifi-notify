#include <stdio.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

char* get_wifi_info(const char* field) {
    char command[256];
    snprintf(command, sizeof(command), "nmcli -t -f %s dev wifi | head -1", field);

    FILE* fp = popen(command, "r");
    if(fp == NULL) {
        printf("Failed to run nmcli\n");
        return NULL;
    }
    char* result = malloc(256);
    fgets(result, 256, fp);
    pclose(fp);

    result[strcspn(result, "\n")] = 0;

    return result;
}

int main() {

    return EXIT_SUCCESS;
}
