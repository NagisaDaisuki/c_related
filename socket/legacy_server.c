#include <arpa/inet.h> // 提供 htons(), inet_ntoa()
// #include <asm-generic/socket.h>
#include <netinet/in.h> // 提供 socketadd_in 结构体
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // 提供 socket(), bind(), listen(), accept()
#include <unistd.h>     // 提供 close(), read(), write()

#define PORT 8080        // 端口号
#define BUFFER_SIZE 1024 // 缓冲区大小

// TCP生命周期
/*
 *  服务端生命周期时序：
 *  socket() -> setsockopt() -> bind() -> listen() -> accept()
 *  -> recv() / send() -> close()
 * */

// 核心结构体：C语言的"面向对象多态"
// 在 Linux 网络编程中，最常让人困惑的就是为什么定义了 sockaddr_in
// ，传参时却要强制类型转换成 sockaddr。这是理解网络结构体的核心枢纽。
/*
 *   struct sockaddr：通用的“基类”结构体
 *   struct sockaddr {
 *    sa_family_t sa_family; // 协议族(2 字节), 例如 AF_INET,AF_INET6, AF_UNIX
 *    char        sa_data[14]; // 目标地址数据(14字节)
 *   };
 *
 *   历史背景：早期的 BSD Socket 设计时，C 语言标准还没有通用指针 void*，更没有
C++ 的类继承。

作用：操作系统需要一个通用的接口来支持不同的网络协议（IPv4、IPv6、本地进程间通信
Unix Domain Socket）。struct sockaddr 充当了抽象基类的角色。所有的 Socket
系统调用（如 bind、connect、accept）统一接收 struct sockaddr*。

缺点：它把 IP 和端口全部揉碎在 14 字节的 sa_data
数组里，人手直接填充极难写且易出错。


      struct sockaddr_in：IPv4 的“专用派生类”
      为了方便程序员配置 IPv4 地址，系统专门定义了专门的 sockaddr_in（末尾的 _in
代表 Internet）：
      struct socketaddr_in {
        sa_family_t     sin_family;     // 地址族：固定填 AF_INET (IPv4)
        in_port_t       sin_port;       // 16 位端口号（必须是大端字节序）
        struct in_addr  sin_addr;       // 32 位 IPv4地址
        char            sin_zero[8];    // 填充字节，全部置0， 用来凑齐 16 字节
      };

      struct in_addr {
        in_addr_t       s_addr;         // 32 位的无符号整数(uint32_t),
                                        // 存放网络字节序的 IP
      };

      内存对齐原理：struct sockaddr 的总长度是 $2 + 14 = 16$ 字节。
      struct sockaddr_in 的长度是 $2 + 2 + 4 + 8 = 16$ 字节。
      二者在内存中的尺寸一模一样，前 2 个字节完全重合。
      因此代码中先用易读的 sockaddr_in 填数据，传参给系统调用时直接用
      (struct sockaddr *)&server_addr 强转指针，
      本质上是在 C 语言里手工实现向上转型（Upcasting）。
 * */

int main() {
  int server_fd = -1;
  int client_fd = -1;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  char buffer[BUFFER_SIZE];

  // 1. 创建套接字(Socket)
  // AF_INET: 使用IPv4 协议
  // SOCK_STREAM: 使用面向连接的稳定字节流(TCP)
  // 0: 使用默认协议(IPPROTO_TCP)
  // socket(): 向操作系统申领通信端点
  // int socket(int domain, int type, int protocol);
  /*
   *  参数 1 (AF_INET)：协议族。AF_INET 代表 IPv4，AF_INET6 代表 IPv6，AF_UNIX
      代表本机 IPC。

      参数 2 (SOCK_STREAM)：通信类型。SOCK_STREAM
   代表面向连接的流式传输（TCP）；若传 SOCK_DGRAM 则代表无连接的数据报（UDP）。

      参数 3 (0)：具体协议。传 0
      表示让系统根据前两个参数自动挑选默认协议（此处默认匹配为 IPPROTO_TCP）。

      返回值：成功返回一个正整数（文件描述符 fd），失败返回 -1。
   * */

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket failed.");
    exit(EXIT_FAILURE);
  }
  printf("[1]成功创建服务端监听套接字，分配的文件描述符(server_fd): %d\n",
         server_fd);

  // 优化选项：允许地址重用(SO_REUSEADDR)
  // 作用：程序重启时，如果端口处于 TIME_WAIT 状态，允许立即
  // 重新绑定该端口
  // setsockopt(): 调整套接字的内核行为
  // SOL_SOCKET: 表示要调整的选项位于Socket API通用层
  // SO_REUSEADDR: 重用处于 TIME_WAIT 状态的本地地址。
  //
  // TCP连接主动断开的一方会进入长达1 ~ 2分钟的TIME_WAIT状态，
  // 如果重启服务端进程，没有配备这个选项，操作系统内核会报错 Address
  // already in use 拒绝启动；开启后即可瞬间重新绑定端口
  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // 2. 准备地址并绑定(Bind)
  // bind(): 給套接字赋予物理名字(IP + Port)
  // socket()创建的插头一开始是"漂浮在虚空"中的，没有任何网络坐标。
  // bind()的任务就是把这个套接字牢牢定在本机的特定网卡(IP)和特定端口号上。
  // INADDR_ANY: 0.0.0.0 监听本机所有网卡上的流量
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  // INADDR_ANY: 绑定本机所有可用网卡 IP(0.0.0.0)
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // htons: Host to Network Short, 将端口号转换为网络大端字节序
  server_addr.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }
  printf("[2]成功将套接字绑定到端口：%d\n", PORT);

  // 3. 开启监听(Listen)
  // 将主动套接字转变为被动监听套接字
  // 128: 内核排队队列(Backlog)长度，允许等待三次握手完成的连接上限
  // listen(): 转变为被动监听模式
  // 默认创建的套接字是"主动套接字"(用来调connect连接别人的)。listen()
  // 是一道不可逆的命令，将该套接字变为"被动套接字"(只负责等待别人来连接)。
  //
  if (listen(server_fd, 128) < 0) {
    perror("listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }
  printf("[3]服务端进入LISTEN状态，等待客户端连接...\n");

  // 4. 接收客户端连接(Accept)
  // 注意：accept() 是阻塞调用，三次握手是由操作系统内核在后台完成的
  // 当连接建立完成后，accept 从内核队列中取出一个连接，并返回一个全新的
  // client_fd
  // int accept(int sockfd, struct sockaddr *addr, socklen_t
  // *addrlen): 从就绪队列提取已建好的连接 addr 和
  // addrlen是传出承诺书。内核会将对方(客户端)的真实IP和端口 填入 client_addr
  // 中。
  // 两个 fd 的分水岭：sockfd(server_fd):
  // 前台门卫，只负责迎客，整个生命周期只有一个。 返回值 client_fd:
  // 操作系统新生成的专属通信通道。后续的一切数据收发，只能通过这个新的
  // client_fd。
  client_fd =
      accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (client_fd < 0) {
    perror("accept failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // 打印连入客户端的IP和端口
  printf("[4]客户端连接成功！\n");
  printf("客户端IP: %s, 端口 %d\n", inet_ntoa(client_addr.sin_addr),
         ntohs(client_addr.sin_port));
  printf("专属通信文件描述符(client_fd): %d\n", client_fd);

  // 5. 数据读写循环(Echo回显逻辑)
  while (1) {
    memset(buffer, 0, BUFFER_SIZE);

    // recv() 与 send(): 流式数据传输
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    /*
     *  recv() 的三大返回值法则（必须牢记）：
        > 0：成功读取到的真实字节数。注意：由于 TCP 粘包拆包特性，你期望读 1024
        字节，它可能只收到 5 字节，必须按实际返回值处理。
        == 0：连接正常关闭。表示对端执行了 close()，向我方发送了 TCP 四次挥手的
     FIN 包。此时必须跳出循环并关闭本地套接字。
        < 0：发生网络错误或系统中断，需要查看 errno。
        send() 的物理本质：
        send()并不是把数据直接扔给网线，而是把数据从用户空间内存拷贝到操作系统内核的
        TCP发送缓冲区（Send Buffer）。只要拷贝进缓冲区，send()
        就立刻返回成功。何时真正由网卡发射出去，全权由操作系统的网络栈算法（如
     Nagle 算法）掌控。
     * */

    // recv()也是阻塞调用：如果没有数据发来，当前进程会睡眠让出CPU
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read > 0) {
      printf("[受到来自客户端 %d 的消息]：%s", client_fd, buffer);

      // 原样将数据发送回客户端(回显)
      send(client_fd, buffer, bytes_read, 0);
    } else if (bytes_read == 0) {
      // 返回 0 表示客户端主动关闭了连接(接收到四次挥手的FIN包)
      printf("[5]客户端主动断开连接。\n");
      break;
    } else {
      // 返回负数表示发生网络异常
      perror("recv error");
      break;
    }
  }

  // 6. 清理资源：C语言必须手动关闭每一个申请出来的fd！
  close(client_fd);
  close(server_fd);
  printf("[6]服务端正常退出，套接字已安全关闭。\n");

  return EXIT_SUCCESS;
}
