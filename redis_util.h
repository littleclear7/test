/************************************************
*Copyright (c) :
*文件名: redis_util.h
*文件描述: redis 增删改查连接封装
*作者: 朱彤
*版本号: 1.0.0
*创建日期: 2020/9/15
*修订日期：
*修订者：
*修订内容简述
***********************************************/
#ifndef REDIS_UTIL_H
#define REDIS_UTIL_H
#include "hiredis.h"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 6379
#define STRING 0
#define BINARY_STRING 1
#define INTEGER 2

/*************************************************
 * 函数名：              redis_connect
 * 函数功能描述：         连接redis
 * 函数参数：
 * @param  				ip redis_ip
 * @param
 *
 * 函数返回值
 * @return                redisContext  连接成功
 *                        NULL          连接失败
 * 作者：                          zt
 * 函数创建日期：                   2020/9/15
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 *
**************************************************/
redisContext *redis_connect(unsigned char *ip, int port);

/*************************************************
 * 函数名：
 * 函数功能描述：                  redis加入hash健值
 * 函数参数：
 * @param  				          hashKey hash表名
 * 函数返回值
 * @return
 * 作者：                          zt
 * 函数创建日期：                   2020/9/15
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 *
**************************************************/
int redis_set_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key, unsigned char *value, int value_len, int value_type);

/*************************************************
 * 函数名：
 * 函数功能描述：                   redis获取hash表名为hashKey的key的value
 * 函数参数：
 * @param  				          hashKey hash表名
 * 函数返回值
 * @return                       0:get success
 *                              -1:get error
 * 作者：                          zt
 * 函数创建日期：                   2020/9/15
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:                          查询到的value都为string格式的
 *
**************************************************/
int redis_get_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key, void *value, int *valueLen);

/*************************************************
 * 函数名：
 * 函数功能描述：                  删除hash表名为hashKey的key
 * 函数参数：
 * @param
 * 函数返回值
 * @return                       0:delete success
 *                              -1:delete error
 * 作者：                          zt
 * 函数创建日期：                   2020/9/15
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 *
**************************************************/
int redis_del_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key);

/*************************************************
 * 函数名：
 * 函数功能描述：                  释放redis连接
 * 函数参数：
 * @param
 * 函数返回值
 * @return
 * 作者：                          zt
 * 函数创建日期：                   2020/9/15
 * 目前版本：                       v1.0.0
 * 历史版本：                       v1.0.0
 * 备注:
 *
**************************************************/
void redis_free_connect(redisContext *c);
#endif //REDIS_UTIL_H
