/*
 * 文件功能：socket tcp、udp通信相关函数
 */

#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
/*************************************************
 * 函数名：                        init_udp_socket
 * 函数功能描述：                   UDP-ipv4套接字初始化
 * @param  bindIp 				  待绑定的ip
 * @param  bindPort				  待绑定的端口
 * @return [int]                  成功: 套接字fd
 *                                失败: 小于0的错误码
 * 作者：                          zono
 * 函数创建日期：                   2020年7月7日
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 * 		绑定本机端口使用 "0.0.0.0"
**************************************************/
int init_udp_socket(char *bindIp, int bindPort);

/*************************************************
 * 函数名：                        init_udp_socket_and_join_group
 * 函数功能描述：                   UDP-ipv4套接字初始化并加入组播
 * @param  bindIp 				  待绑定的ip
 * @param  bindPort				  待绑定的端口
 * @param  bindIp 				  待加入的组播地址
 * @return [int]                  成功: 套接字fd
 *                                失败: 小于0的错误码
 * 作者：                          zono
 * 函数创建日期：                   2020年7月7日
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 * 		绑定本机端口使用 "0.0.0.0"
**************************************************/
int init_udp_socket_and_join_group(char *bindIp, int bindPort, char *udpMultiCastIp);

/*************************************************
 * 函数名：                        send_udp_to_addr
 * 函数功能描述：                   使用udp套接字向显式所给的地址发送消息
 * @param  sockFd 				  已初始化的udp套接字fd
 * @param  destIp				  目标ip
 * @param  destPort 			  目标端口
 * @param  data				      发送数据
 * @param  len				      发送数据长度
 * @return [int]                  成功: 成功发送的数据长度
 *                                失败: 小于等于0的错误码
 * 作者：                          zono
 * 函数创建日期：                   2020年7月7日
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 *
**************************************************/
int send_udp_to_addr(int sockFd, char *destIp, int destPort, void *data, size_t len);

#endif