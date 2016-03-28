$cd lib_acl; make
$cd lib_protocol; make
$cd lib_acl_cpp; make

example:

CFLAGS = -c -g -W -O3 -Wall -Werror -Wshadow \
-Wno-long-long -Wpointer-arith -D_REENTRANT \
-D_POSIX_PTHREAD_SEMANTICS -DLINUX2 \
-I ./lib_acl_cpp/include
BASE_PATH=./acl
LDFLAGS = -L$(BASE_PATH)/lib_acl_cpp/lib -l_acl_cpp \
    -L$(BASE_PATH)/lib_protocol/lib -l_protocol \
    -L$(BASE_PATH)/lib_acl/lib -l_acl \
    -lpthread
test: main.o
    gcc -o main.o $(LDFLAGS)
main.o: main.cpp
    gcc $(CFLAGS) main.cpp -o main.o



记得free掉reply
如何将单机的redis数据导入到redis cluster



bug修复
1、修复query_session时value为空的情况
2、去除response的json的\n
3、修复children等子树为空时返回[]


1、定义宏确定是否开启Daemon模式 ok
2、添加默认页 ok
3、make install
4、动态添加模块 boost plugin
5、日志删除能否自建 目前为循环日志，大小16m 达到一定大小后放到logs目录下面去
6、日志开关 
7、增加日志等级

1、主备
2、主发送数据给备机,备机保存aof文件per sec

策略：
两台机器做redis cluster，一个机器是两master实例，一个slave实例；另一个机器是两个slave实例，一个master实例，配置aof持久化文件，每秒钟持久化一次。

需要redis版本3.0以上，目前已经在自己电脑实验部署好cluster，后面需要：
1、升级测试用机器的redis版本，另一台新装机器需要部署环境
2、redis cluster部署完后，需要改写代码，将原来的写一个redis实例的代码更改为写redis cluster




reponse log ok
request log post ok
request log get 未取到数据，待查


#主库配置
url_master=jdbc:mysql://172.18.22.202:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_master=renesola
password_master=renesola

#从库配置
url_slave=jdbc:mysql://172.18.22.203:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_slave=renesola
password_slave=renesola



1、redis 主从设置
2、request get时request不能写日志，只有请求全部为post即可
3、redis设置过期时间问题（用于session）
4、redis数据持久化问题
save 900 1

save 300 10

save 60 10000

#   after 900 sec (15 min) if at least 1 key changed

#   after 300 sec (5 min) if at least 10 keys changed

#   after 60 sec if at least 10000 keys changed
可能会有数据丢失


5、本程序主从
考虑可以一台主redis，N台read-only的slave，每台上面都部署程序
或者一主一备，二主二备皆可，每台都提供程序

6、数据存放是否需要不同的redis数据库，默认是select 0



