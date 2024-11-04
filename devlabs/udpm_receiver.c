#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MULTICAST_GROUP "239.255.0.1"  // 멀티캐스트 주소
#define MULTICAST_PORT 7400         // 포트 번호
#define BUFFER_SIZE 256

int main() {
    int sockfd;
    struct sockaddr_in local_addr;
    struct ip_mreq multicast_request;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // 로컬 주소 설정
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 인터페이스에서 수신
    local_addr.sin_port = htons(MULTICAST_PORT);     // 포트 설정

    // 소켓 바인드
    if (bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    // 멀티캐스트 그룹 가입
    multicast_request.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_request.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_request, sizeof(multicast_request)) < 0) {
        perror("setsockopt");
        close(sockfd);
        exit(1);
    }

    // 메시지 수신
    while (1) {
        int len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, NULL, 0);
        if (len < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(1);
        }
        buffer[len] = '\0';  // 문자열 끝에 NULL 추가
        printf("Received message: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
