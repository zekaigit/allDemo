/* ************************************************************************
 *       Filename:  main.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年09月11日 17时47分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <sys/ioctl.h> 
#include <net/if.h> 
#include <netinet/in.h> 
#include <net/if_arp.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <pthread.h>

int getPeerMacbySocketFd( int sockfd, char *buf, char* localethname ) 
{ 
    int ret =0; 
    struct arpreq arpreq; 
    struct sockaddr_in dstadd_in; 
    socklen_t  len = sizeof( struct sockaddr_in ); 
    memset( &arpreq, 0, sizeof( struct arpreq )); 
    memset( &dstadd_in, 0, sizeof( struct sockaddr_in ));  
    if( getpeername( sockfd, (struct sockaddr*)&dstadd_in, &len ) < 0 ) 
    { 
        //perror( "get peer name wrong, %s\n", strerror(errno) ); 
		printf("get peer name wrong\n");
        return -1; 
    } 
    else 
    { 
        memcpy( ( struct sockaddr_in * )&arpreq.arp_pa, ( struct sockaddr_in * )&dstadd_in, sizeof( struct sockaddr_in )); 
        strcpy(arpreq.arp_dev, localethname); 
        arpreq.arp_pa.sa_family = AF_INET; 
        arpreq.arp_ha.sa_family = AF_UNSPEC; 
        if( ioctl( sockfd, SIOCGARP, &arpreq ) < 0 ) 
        { 
            //perror( "ioctl SIOCGARP wrong, %s\n", strerror(errno) ); 
            printf("ioctl SIOCGARP wrong\n "); 
            return -1; 
        } 
        else 
        { 
            unsigned char* ptr = (unsigned char *)arpreq.arp_ha.sa_data; 
            sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)); 
        } 
     } 
     return ret; 
}

int gahGetPeerMacbyIp(char *ipaddr, char* buf, char* localethname) 
{ 
        int     sockfd; 
        unsigned char *ptr; 
        struct arpreq arpreq; 
        struct sockaddr_in *sin; 
        struct sockaddr_storage ss; 
        char addr[INET_ADDRSTRLEN+1];

        memset(addr, 0, INET_ADDRSTRLEN+1); 
        memset(&ss, 0, sizeof(ss));

        sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
        if (sockfd == -1) { 
                perror("socket error"); 
                return -1; 
        } 
        sin = (struct sockaddr_in *) &ss; 
        sin->sin_family = AF_INET; 
        if (inet_pton(AF_INET, ipaddr, &(sin->sin_addr)) <= 0) { 
                perror( "inet_pton error"); 
                return -1; 
        } 
        sin = (struct sockaddr_in *) &arpreq.arp_pa; 
        memcpy(sin, &ss, sizeof(struct sockaddr_in)); 
        strcpy(arpreq.arp_dev, localethname); 
        arpreq.arp_ha.sa_family = AF_UNSPEC; 
        if (ioctl(sockfd, SIOCGARP, &arpreq) < 0) { 
                perror("ioctl SIOCGARP: "); 
                return -1; 
        } 
        ptr = (unsigned char *)arpreq.arp_ha.sa_data; 
        sprintf(buf,"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)); 
        return 0; 
}


int main(int argc, char *argv[])
{
	char dst_mac[32]={0};
	gahGetPeerMacbyIp("192.168.1.16", dst_mac, "eth1");
	printf("dst_mac = %s\n", dst_mac);
	return 0;
}
