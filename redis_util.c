#include "redis_util.h"
redisContext *redis_connect(unsigned char *ip, int port) {
    unsigned char useIp[16] = {0};
    int usePort = -1;
    ip == NULL? memcpy(useIp, DEFAULT_IP, strlen(DEFAULT_IP)) : memcpy(useIp, ip, strlen(ip));
    usePort = port == NULL? DEFAULT_PORT : port;
    redisContext *c;
    c = redisConnect(useIp, usePort);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return NULL;
    }
    return c;
}

int redis_set_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key, unsigned char *value, int value_len, int value_type){
    if(c == NULL){
        printf("can't connect redis server!");
        return -1;
    }
    if(hashKey == NULL || key == NULL){
        printf("hashKey or key is NULL");
        return -1;
    }
    redisReply *reply;
    switch (value_type) {
        case STRING:
        {
            reply = redisCommand(c,"hset %s %s %s",hashKey,key, value);
            break;
        }
        case BINARY_STRING:
        {
            reply = redisCommand(c,"hset %s %s %b",hashKey,key, value, (size_t)value_len);
            break;
        }
        case INTEGER:
        {
            reply = redisCommand(c,"hset %s %s %d",hashKey,key, value);
            break;
        }
        default:
            break;
    }
    if(reply->type == REDIS_REPLY_ERROR){
        freeReplyObject(reply);
        return -2;
    }
    freeReplyObject(reply);
    return 0;
}

int redis_get_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key, void *value, int *valueLen){
    if(c == NULL ){
        printf("can't connect redis server or valve is NULL!");
        return -1;
    }
    if(hashKey == NULL ||key == NULL){
        printf("hashKey or key is NULL\n");
        return -1;
    }
    redisReply *reply;
    reply = redisCommand(c, "hget %s %s", hashKey, key);
//    if(reply->str)
    switch (reply->type) {
        case REDIS_REPLY_STRING:
        {
            if(value == NULL ){
                freeReplyObject(reply);
                return -1;
            }
            memcpy(value, reply->str, reply->len);
            if(valueLen != NULL)
                *valueLen = reply->len;
            break;
        }
        case REDIS_REPLY_INTEGER:
        {
            *(int *)(value) = reply->integer;
            break;
        }
        case REDIS_REPLY_ERROR: {
            freeReplyObject(reply);
            return -1;
            break;
        }
        default:
            break;
    }
    freeReplyObject(reply);
    return 0;
}

int redis_del_hash_key(redisContext *c, unsigned char *hashKey, unsigned char *key){
    if(c == NULL){
        printf("can't connect redis server or valve is NULL!");
        return -1;
    }
    if(hashKey == NULL ||key == NULL){
        printf("hashKey or key is NULL\n");
        return -1;
    }
    redisReply *reply;
    reply = redisCommand(c, "hdel %s %s", hashKey, key);
    if(reply->type == REDIS_REPLY_ERROR){
        freeReplyObject(reply);
        return -1;
    }
    freeReplyObject(reply);
    return 0;
}

void redis_free_connect(redisContext *c){
    redisFree(c);
}
