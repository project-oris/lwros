#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MULTICAST_GROUP "239.255.0.1"  // 멀티캐스트 주소
#define MULTICAST_PORT 7400         // 포트 번호
#define MESSAGE "Hello Multicast!"    // 전송할 메시지

int main() {
    int sockfd;
    struct sockaddr_in multicast_addr;
    int multicast_ttl = 1;  // TTL(Time to Live): 로컬 네트워크에서만 패킷이 전달되도록 설정
    
    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // 멀티캐스트 주소 설정
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);  // 멀티캐스트 그룹 주소
    multicast_addr.sin_port = htons(MULTICAST_PORT);  // 포트 설정

    // TTL 설정
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &multicast_ttl, sizeof(multicast_ttl)) < 0) {
        perror("setsockopt");
        close(sockfd);
        exit(1);
    }

    // 메시지 전송
    if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr*)&multicast_addr, sizeof(multicast_addr)) < 0) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }

    printf("Sent message: %s\n", MESSAGE);

    getchar();

    close(sockfd);
    return 0;
}
