#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    char ip_address[16];
    printf("Enter an IP address: ");
    scanf("%15s", ip_address);

    int ip[4];
    int cidr;

    // Parse IP address
    sscanf(ip_address, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

    printf("\nIP Address: %s\n", ip_address);

    printf("\n1. Classful\n2. Classless\n3. Exit\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (ip[0] >= 1 && ip[0] <= 127) {
                printf("Class A\n");
                printf("Subnet Mask: 255.0.0.0\n");
            } else if (ip[0] <= 191) {
                printf("Class B\n");
                printf("Subnet Mask: 255.255.0.0\n");
            } else if (ip[0] <= 223) {
                printf("Class C\n");
                printf("Subnet Mask: 255.255.255.0\n");
            } else if (ip[0] <= 239) {
                printf("Class D\n");
            } else {
                printf("Class E\n");
            }
            break;
        case 2:
            printf("Enter CIDR notation (e.g., 24 for /24): ");
            scanf("%d", &cidr);
            if (cidr >= 0 && cidr <= 32) {
                printf("CIDR Notation: /%d\n", cidr);
                int mask[4] = {0};
                for (int i = 0; i < cidr; i++) {
                    mask[i / 8] |= (1 << (7 - (i % 8)));
                }
                printf("Subnet Mask: %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
                printf("Number of Hosts: %ld\n", (long)pow(2, 32 - cidr) - 2);
            } else {
                printf("Invalid CIDR notation\n");
            }
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
