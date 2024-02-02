#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define PORT 4771

// Function to convert binary string to decimal integer
unsigned long binaryToDecimal(const char *binaryString) {
    return strtoul(binaryString, NULL, 2);
}

//convert decimal to Binary
char *decimalToBinary(unsigned long num,int N) {
     int bits = N-1; // Assuming a 32-bit integer, adjust for different sizes
    char *binaryString = (char *)malloc(bits + 1); // Extra space for null terminator

    if (binaryString == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    binaryString[bits] = '\0'; // Null-terminate the string

    // Convert integer to binary
    for (int i = 0; i < bits; i++) {
        binaryString[bits - 1 - i] = (num % 2) + '0'; // Get the least significant bit and convert to character
        num /= 2; // Divide by 2 to get the next bit
    }


    return binaryString;
}

// Function to calculate CRC
unsigned long calculateCRC(unsigned long data, unsigned long divisor) {
    // XOR operation to calculate CRC
    return data/divisor;
}

int main(int argc,char *argv[])
{
        char Data[100],Divisor[100],buffer[100];
        int sockfd,a,connfd,len,i=0;
        struct sockaddr_in servaddr,cliaddr;
        
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd==-1)
        {
                printf("Error creating socket\n");
                exit(0);
        }
        printf("Server Socket Created Successfully.\n");
        bzero((struct sockaddr *)&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(PORT);
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        {
                printf("Error in BIND function");
                exit(0);
        }
        printf("Server Socket Binded.\n");
        if((a=listen(sockfd,5))==-1)
        {
                printf("Error in LISTEN function");
                exit(0);
        }
        printf("Server Socket Listened...\n");
        len=sizeof(cliaddr);
        if((connfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len))<0)
        {
                printf("Error in ACCEPT");
                exit(0);
        }
        
        	
        strcpy(Data," ");
        read(connfd,Data,100);
        printf("From client \nData: %s",Data);
        strcpy(Divisor," ");
        read(connfd,Divisor,100);
        printf("\nDivisor: %s",Divisor);
	
	/*
	long dataInt = strtol(data, NULL, 2);
	long divrInt = strtol(divisor, NULL, 2);
	
	int n = 0;
	for(n = 0;data[n] != '\0';n++){
		//n++;
		continue;
	}
	int mul = power(n-1);
	dataInt = dataInt * mul;
	int result = dataInt/divrInt ;
	printf("Size: %ld\ndataINT: %ld",n,dataInt);
	*/
	
	unsigned long data = binaryToDecimal(Data);
	unsigned long divisor = binaryToDecimal(Divisor);

	double logResult = log2(divisor);
	int N = ceil(logResult);
	data = data * pow(2,N-1);

	// Calculate CRC
	unsigned long crc = calculateCRC(data, divisor);

	// Represent CRC in binary
	char *crcBinary = decimalToBinary(crc,N);

	// Print the results
	printf("\nConverted Decimal Values:\n");
	printf("Data: %lu\n", data);
	printf("Divisor: %lu\n", divisor);

	printf("\nCRC Calculation:\n");
	printf("CRC: %lu\n", crc);
	printf("CRC in Binary: %s\n", crcBinary);

	//////////
	strcpy(buffer," ");
	for(int i=0;Data[i]!='\n';i++){
		buffer[i] = Data[i];
	}
        strcat(buffer,crcBinary);
        write(connfd,buffer,100);
        
        exit(0);
        close(connfd);
        return 0;
}
