#define _POSIX_C_SOURCE 200112L

#include <arpa/inet.h> // 提供 inet_ntop()
#include <netdb.h>     // 提供 getaddrinfo(), freeaddrinfo(), gai_strerror()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// 辅助函数：从通用 sockaddr中提取纯IP地址指针(兼容 IPv4 和 IPv6)
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "用法：%s <主机名/域名/IP> <端口号>\n", argv[0]);
    fprintf(stderr, "示例：%s 127.0.0.1 8080\n", argv[0]);
    fprintf(stderr, "示例：%s localhost 8080\n", argv[0]);
    fprintf(stderr, "示例：%s ::1 8080\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *hostname = argv[1];
  const char *port = argv[2];

  struct addrinfo hints;            // 过滤提示
  struct addrinfo *servinfo = NULL; // 链表头指针
  struct addrinfo *p = NULL;        // 链表遍历指针
  int status;
  int sockfd = -1;

  // 1. 设置偏好过滤条件
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;     // 核心：IPv4 或 IPv6均可，系统自动匹配
  hints.ai_socktype = SOCK_STREAM; // 面向连接的流式传输(TCP)

  // 2. 域名解析与地址填充
  // 无论是传 "127.0.0.1" "localhost" 还是 "baidu.com",
  // 系统在后台全自动处理
  // int getaddrinfo(const char *node,
  //                 const char *service,
  //                 const struct addrinfo *hints,
  //                 struct addrinfo **res);
  /*
   *  参数与返回值详解
        node（主机节点）：
        可以是主机名/域名（如
        "[www.baidu.com](https://www.baidu.com)"、"localhost"）。 也可以是IP
        地址字符串（如 "192.168.1.1"、"::1"）。 若作为服务端且设置了 AI_PASSIVE
        标志，此处可传 NULL，系统会自动绑定到本机通配地址（对应 IPv4 的
        INADDR_ANY 或 IPv6 的 in6addr_any）。

        service（服务名称 / 端口）：
        可以是十进制端口号字符串（如 "8080"、"443"）。
        也可以是标准服务名（如 "http"、"https"、"ftp"、"ssh"，系统会从
        /etc/services 中自动查找对应端口）。

        hints（过滤提示）：
        一个指向 struct addrinfo
        的输入参数。你可以在其中指定期望的协议族（AF_INET、AF_INET6 或
        AF_UNSPEC）、Socket 类型（SOCK_STREAM 或
        SOCK_DGRAM）等偏好，系统只返回符合你要求的记录。

        res（结果链表头指针）：
        二级指针传出参数。系统内部会在堆上动态分配一个或多个 struct addrinfo
        结构体，将其组织为单向链表，并将头节点的地址赋给 *res。

        返回值：
        成功返回 0；
        失败返回非零错误码（注意：它不设置 errno，必须用专用的
        gai_strerror(status) 来获取人类可读的错误文本）。
        配套释放函数：使用完毕后必须调用 void freeaddrinfo(struct addrinfo
        *res); 释放链表内存。
   * */
  if ((status = getaddrinfo(hostname, port, &hints, &servinfo)) != 0) {
    // getaddrinfo 的错误码需要用专用的 gai_strerror 打印
    fprintf(stderr, "getaddrinfo 错误：%s\n", gai_strerror(status));
    return 1;
  }

  // 3. 顺着链表逐个尝试连接
  // 一个域名可能解析出多个IP（如同时有多个 IPv4 和 IPv6地址）
  for (p = servinfo; p != NULL; p = p->ai_next) {
    // 创建套接字：完全使用系统填好的参数，不再硬编码 AF_INET
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) {
      continue; // 当前协议创建失败，尝试下一个节点
    }

    // 发起 TCP 三次握手连接
    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      sockfd = -1;
      continue; // 连接失败，关闭套接字，尝试下一个节点
    }

    // 走到这里说明连接成功，跳出循环！
    break;
  }

  if (p == NULL) {
    fprintf(stderr, "客户端：连接目标所有可用地址均失败\n");
    freeaddrinfo(servinfo);
    return 2;
  }

  // 4. 打印实际连上的 IP 地址信息（支持展示 IPv4 和 IPv6 格式）
  char ip_str[INET6_ADDRSTRLEN];
  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), ip_str,
            sizeof ip_str);
  printf("成功连接至：%s [%s] 端口：%s (fd: %d)\n", hostname, ip_str, port,
         sockfd);

  // 5. 链表任务完成，必须显式释放由 getaddrinfo 分配的堆内存
  freeaddrinfo(servinfo);

#define IF_LOOP 1
#ifndef IF_LOOP
  // 6. 发送数据并接收服务端的回显
  const char *msg = "Hello modern socket network!\n";
  if (send(sockfd, msg, strlen(msg), 0) == -1) {
    perror("send");
    close(sockfd);
    return 1;
  }
  printf("[发送]：%s\n", msg);

  char buffer[BUFFER_SIZE];
  memset(buffer, 0, sizeof(buffer));
  ssize_t bytes_recv = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_recv > 0) {
    printf("[收到回显]: %s", buffer);
  } else if (bytes_recv == 0) {
    printf("服务端主动关闭了连接\n");
  } else {
    perror("recv");
  }
#else
  // 持续双向通信循环
  char send_buf[BUFFER_SIZE];
  char recv_buf[BUFFER_SIZE];

  while (1) {
    printf("请输入消息 > ");
    fflush(stdout);

    // 从终端标准输入读取一行 （支持包含空格的输入）
    if (fgets(send_buf, sizeof(send_buf), stdin) == NULL) {
      // 用户按下了 Ctrl+D (EOF)
      printf("\n检测到 EOF, 正在退出...\n");
      break;
    }

    // 判断退出命令
    if (strcmp(send_buf, "quit\n") == 0 || strcmp(send_buf, "exit\n") == 0) {
      printf("主动退出通信。\n");
      break;
    }

    // 如果用户直接敲回车，跳过本次发送
    if (strcmp(send_buf, "\n") == 0) {
      continue;
    }

    // 1. 发送数据給服务端
    ssize_t bytes_sent = send(sockfd, send_buf, strlen(send_buf), 0);
    if (bytes_sent == -1) {
      perror("send 出错");
      break;
    }

    // 2. 阻塞接收服务端的回显响应
    memset(recv_buf, 0, sizeof(recv_buf));
    ssize_t bytes_recv = recv(sockfd, recv_buf, sizeof(recv_buf) - 1, 0);

    if (bytes_recv > 0) {
      printf("[服务端回显]: %s", recv_buf);
    } else if (bytes_recv == 0) {
      printf("服务端主动关闭了连接。\n");
      break;
    } else {
      perror("recv 出错");
      break;
    }
  }
#endif

  // 7. 关闭套接字(像对端发送 FIN包)
  close(sockfd);
  printf("连接已断开，客户端退出。\n");
  return EXIT_SUCCESS;
}
