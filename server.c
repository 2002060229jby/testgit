#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SERV_PORT 8000
#define MAXLEN 80
int main() {
  struct sockaddr_in servaddr, cliaddr;
  int listenfd, connfd;
  int n;
  char str[INET_ADDRSTRLEN];
  socklen_t cliaddr_len;

  char buf[MAXLEN];
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  //服务器IP地址
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  listen(listenfd, 3);
  printf("accepting connections...\n");
  while (1) {
    cliaddr_len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    n = read(connfd, buf, MAXLEN);
    printf("received from %s:%d\n",
           inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
           ntohs(cliaddr.sin_port));
    for (int i = 0; i < n; i++) {
      buf[i] = toupper(buf[i]);
    }
    write(connfd, buf, n);
    close(connfd);
  }
  return 0;
}
