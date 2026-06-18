#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <libnotify/notify.h>

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

    int init_notify = notify_init("Wifi-notify");
    if(!init_notify) {
        printf("Failed to initalize notification system\n");
        return EXIT_FAILURE;
    }

    char* ssid = get_wifi_info("SSID");
    char* signal = get_wifi_info("SIGNAL");
    char* bars = get_wifi_info("BARS");
    char* speed = get_wifi_info("RATE");

    if(!ssid || !signal || !bars || !speed) {
        printf("Failed to get wifi info\n");
        return EXIT_FAILURE;
    }
    printf("SSID: %s\n", ssid);
    printf("Signal: %s\n", signal);
        printf("Bars:   %s\n", bars);
        printf("Speed:  %s\n", speed);

        // build notification body
        char body[512];
        snprintf(body, sizeof(body),
            "Signal: %s%% %s\nSpeed: %s", signal, bars, speed);

        // create and show notification
        NotifyNotification* notification = notify_notification_new(
            ssid,                // title = SSID name
            body,                // body = signal + speed
            "network-wireless"   // wifi icon
        );

        notify_notification_set_urgency(notification, NOTIFY_URGENCY_NORMAL);
        notify_notification_set_timeout(notification, 5000); // 5 seconds

        if(!notify_notification_show(notification, NULL)) {
            printf("Failed to show notification\n");
            return EXIT_FAILURE;
        }

        printf("Notification sent successfully\n");

        // cleanup
        g_object_unref(G_OBJECT(notification));
        notify_uninit();
        free(ssid);
        free(signal);
        free(bars);
        free(speed);
    return EXIT_SUCCESS;
}
