/*
 * 文件功能：socket tcp、udp通信相关函数
 */

#include "socket_util.h"
#define MAX_CONNECT 128

/****************************************
*初始化服务器的tcp socket套接字
*成功返回监听套接字，失败返回-1
*****************************************/
int socket_init(const char *pIp , const int iHost){
    struct sockaddr_in sockAddr;
    int socketFd = 0;
    int nOpt = 1;
    bzero(&sockAddr , sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    if(NULL == pIp)
        sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        sockAddr.sin_addr.s_addr = inet_addr(pIp);
    sockAddr.sin_port = htons(iHost);
    if(-1 == (socketFd = socket(AF_INET, SOCK_STREAM, 0))){
        printf("create socket faild\n");
        return -1;
    }
    //设置socket ip 端口复用
    if(-1 == setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &nOpt, sizeof(nOpt))){
        printf("ngtServerInit setsockopt is failure!\n");
        close(socketFd);
        return -1;
    }
    if(-1 == bind(socketFd,(struct sockaddr *)&sockAddr,sizeof(sockAddr))){
        printf("bind socket error\n");
        close(socketFd);
        return -1;
    }
    if(-1 == listen(socketFd, MAX_CONNECT)){
        printf("listen socket error\n");
        close(socketFd);
        return -1;

    }

    printf("init socket ok,socket Fd:%d\n",socketFd);
    return socketFd;
}

/****************************************
*连接到指定的服务器
*成功返回连接后新的套接字描述符,失败返回-1
*****************************************/
int socket_connect_server(const char *pServIP, const int iPort){
    int socketFd;
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    inet_pton(AF_INET,pServIP,&sockAddr.sin_addr);
    sockAddr.sin_port = htons( iPort);
    if(-1 == (socketFd = socket(AF_INET,SOCK_STREAM,0))){
        printf("create socket error\n");
        return -1;

    }
    if(-1 == connect(socketFd, (struct sockaddr *)&sockAddr, sizeof(sockAddr))){
        printf("connect socket error\n");
        close(socketFd);
        return -1;
    }
    printf("connect %s ok\n",pServIP);
    return socketFd;

}




int init_udp_socket(char *bindIp, int bindPort)
{
    //创建套接字
    int sockFd = socket(AF_INET,SOCK_DGRAM,0);
    if (-1 == sockFd){
        printf("[initUdpMultiCastSender] socket fail\n");
        return -1;
    }

    struct sockaddr_in bindAddr;
    memset(&bindAddr,0,sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(bindPort);
    inet_pton(AF_INET, bindIp, &bindAddr.sin_addr);

    // 设置端口复用
    int opt = 1;
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));

    //绑定本地端口
    int ret = bind(sockFd,(struct sockaddr *)(&bindAddr),sizeof(struct sockaddr));

    if (-1 == ret){
        printf("[initUdpMultiCastSender] bind fail\n");
        close(sockFd);
        return -1;
    }
    return sockFd;
}

int init_udp_socket_and_join_group(char *bindIp, int bindPort, char *udpMultiCastIp)
{
    int sockFd = init_udp_socket(bindIp, bindPort);

    //设置组播地址并加入
    struct ip_mreq req;
    memset(&req, 0, sizeof(struct ip_mreq));
    req.imr_interface.s_addr = htonl(INADDR_ANY);
    req.imr_multiaddr.s_addr = inet_addr(udpMultiCastIp);
    int ret = setsockopt(sockFd, IPPROTO_IP,IP_ADD_MEMBERSHIP, &req, sizeof(struct ip_mreq));
    if (-1 == ret){
        perror("setsockopt fail\n");
        return -1;
    }

    return sockFd;
}

int send_udp_to_addr(int sockFd, char *destIp, int destPort, void *data, size_t len)
{
    struct sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_addr.s_addr = inet_addr(destIp);
    destAddr.sin_port = htons(destPort);
    int sendLen;
    sendLen = sendto(sockFd, data, len, 0, (struct sockaddr *) (&destAddr), sizeof(struct sockaddr));
    return sendLen;
}

