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



�ǵ�free��reply
��ν�������redis���ݵ��뵽redis cluster



bug�޸�
1���޸�query_sessionʱvalueΪ�յ����
2��ȥ��response��json��\n
3���޸�children������Ϊ��ʱ����[]


1�������ȷ���Ƿ���Daemonģʽ ok
2�����Ĭ��ҳ ok
3��make install
4����̬���ģ�� boost plugin
5����־ɾ���ܷ��Խ� ĿǰΪѭ����־����С16m �ﵽһ����С��ŵ�logsĿ¼����ȥ
6����־���� 
7��������־�ȼ�

1������
2�����������ݸ�����,��������aof�ļ�per sec

���ԣ�
��̨������redis cluster��һ����������masterʵ����һ��slaveʵ������һ������������slaveʵ����һ��masterʵ��������aof�־û��ļ���ÿ���ӳ־û�һ�Ρ�

��Ҫredis�汾3.0���ϣ�Ŀǰ�Ѿ����Լ�����ʵ�鲿���cluster��������Ҫ��
1�����������û�����redis�汾����һ̨��װ������Ҫ���𻷾�
2��redis cluster���������Ҫ��д���룬��ԭ����дһ��redisʵ���Ĵ������Ϊдredis cluster




reponse log ok
request log post ok
request log get δȡ�����ݣ�����


#��������
url_master=jdbc:mysql://172.18.22.202:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_master=renesola
password_master=renesola

#�ӿ�����
url_slave=jdbc:mysql://172.18.22.203:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_slave=renesola
password_slave=renesola



1��redis ��������
2��request getʱrequest����д��־��ֻ������ȫ��Ϊpost����
3��redis���ù���ʱ�����⣨����session��
4��redis���ݳ־û�����
save 900 1

save 300 10

save 60 10000

#   after 900 sec (15 min) if at least 1 key changed

#   after 300 sec (5 min) if at least 10 keys changed

#   after 60 sec if at least 10000 keys changed
���ܻ������ݶ�ʧ


5������������
���ǿ���һ̨��redis��N̨read-only��slave��ÿ̨���涼�������
����һ��һ�������������Կɣ�ÿ̨���ṩ����

6�����ݴ���Ƿ���Ҫ��ͬ��redis���ݿ⣬Ĭ����select 0



