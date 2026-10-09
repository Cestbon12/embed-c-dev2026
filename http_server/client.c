#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFSIZE 1024
int main(void){
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		exit(1);
	}
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    // 3. connect
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("已连接到服务器\n");

    // 4. 循环：读用户输入，发给服务器，收服务器回复
    char buf[BUFSIZE];
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
        write(sock, buf, strlen(buf));

        ssize_t n = read(sock, buf, BUFSIZE - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("服务器回复: %s", buf);
    }

    close(sock);
    return 0;
}
