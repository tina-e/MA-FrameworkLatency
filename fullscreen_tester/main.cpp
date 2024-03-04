#include <iostream>
#include <windows.h>

int main() {
    QUERY_USER_NOTIFICATION_STATE nstate;
    SHQueryUserNotificationState(&nstate);
    printf("%d\n", nstate);
    fflush(stdout);
}
