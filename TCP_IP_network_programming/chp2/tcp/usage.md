## linux平台

### 1. 编译运行服务端
编译

gcc tcp_server.c -o tserver

运行
./tserver 9190

### 2. 编译运行客户端

gcc tcp_client.c -o tclient

./tclient 127.0.0.1 9190

