#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERV_PORT 8000
#define MAXLEN 80

int main() {
  struct sockaddr_in servaddr;
  char buf[MAXLEN] = {"hello tcp"};
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

  connect(sockfd, (struct sockaddr *)*servaddr, sizeof(servaddr));
  write(sockfd, buf, strlen(buf));
  int n = read(sockfd, buf, MAXLEN);
  printf("response from server:\n");
  write(1, buf, n);
  close(sockfd);
  return 0;
}