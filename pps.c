#include <stdio.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <string.h>

#define IFA_STAT(s)     (((struct if_data *)ifa->ifa_data)->ifi_ ## s)

int main(void)
{
    struct ifaddrs *ifap, *ifa;
    char *name;

    if (getifaddrs(&ifap) != 0) {
        printf("error\n");
    }
    else {
        for (ifa = ifap; ifa; ifa= ifa->ifa_next) {
            name = ifa->ifa_name;
            printf("%s: %lu, %lu\n", ifa->ifa_name, IFA_STAT(opackets), IFA_STAT(ipackets));
            while (ifa->ifa_next != NULL && 
                    (strcmp(ifa->ifa_next->ifa_name, name) == 0))  {
                ifa = ifa->ifa_next;
            }
        }
    }
}
