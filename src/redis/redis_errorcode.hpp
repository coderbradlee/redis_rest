#ifndef REDIS_ERRORCODE_HPP
#define	REDIS_ERRORCODE_HPP

///定义redis库
#define KV_SYS_PARAMS 0
#define KV_MF 1
#define KV_SESSION 2
#define KV_VISIT_RECORDS 3
#define KV_SHOPPING_CART 4
#define KV_OBJ_SNAPSHOT 5
#define KV_OPERATION_LOG 6
// response error code define -8001 ~ -9000 隔-10或-5
//JSON_READ_OR_WRITE_ERROR(-8010, "json read or write error", "json 格式问题")
#define JSON_READ_OR_WRITE_ERROR -8010
//CREATE_SESSION_UNKNOWN_ERROR(-8020, "create session unknown error", "创建session时未知的错误")
#define CREATE_SESSION_UNKNOWN_ERROR -8020
//CREATE_SESSION_KEY_EXIST(-8025, "key already exist when create session", "创建session时key已经存在")
#define CREATE_SESSION_KEY_EXIST -8025
//ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR(-8030, "add userid unknown error", "增加userid时未知的错误")
#define ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR -8030
//ADD_USERID_KEY_NOT_EXIST(-8035, "key does not exist when add userid", "增加userid时key不存在")
#define ADD_USERID_KEY_NOT_EXIST -8035
//DELETE_SESSION_UNKNOWN_ERROR(-8040, "del session unknown error", "删除session时未知的错误")
#define DELETE_SESSION_UNKNOWN_ERROR -8040
//DELETE_SESSION_KEY_NOT_EXIST(-8045, "key does not exist when del session", "删除session时key不存在")
#define DELETE_SESSION_KEY_NOT_EXIST -8045
//QUERY_SESSION_UNKNOWN_ERROR(-8050, "unknown error when query session ", "查询session时未知的错误")
#define QUERY_SESSION_UNKNOWN_ERROR -8050
//QUERY_SESSION_KEY_NOT_EXIST(-8055, "key does not exist when query session", "查询session时key不存在")
#define QUERY_SESSION_KEY_NOT_EXIST -8055
//UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR(-8060, "update session unknown error", "更新session时未知的错误")
#define UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR -8060
//UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST(-8065, "key does not exist when update session", "更新session时key不存在")
#define UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST -8065
//*********************************************************
//BATCH_CREATE_AREAS_KEY_EXIST(-8070, "key already exists when batch create areas", "批量增加地区key时key已经存在")
#define BATCH_CREATE_AREAS_KEY_EXIST -8070
//BATCH_CREATE_AREAS_UNKNOWN_ERROR(-8080, "unknown error when batch create areas", "批量增加地区key时未知错误")
#define BATCH_CREATE_AREAS_UNKNOWN_ERROR -8080
//UNKNOWN_ERROR(-8085, "unknown error", "未知错误")
#define UNKNOWN_ERROR -8085


#endif	