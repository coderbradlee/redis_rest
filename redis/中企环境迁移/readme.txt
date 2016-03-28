172.30.1.5
su redis
redis-server /etc/redis/redis-6380.conf
redis-server /etc/redis/redis-6381.conf
redis-server /etc/redis/redis-7382.conf

172.30.1.3
su redis
redis-server /etc/redis/redis-6382.conf
redis-server /etc/redis/redis-7380.conf
redis-server /etc/redis/redis-7381.conf

redis-cli -h 127.0.0.1 -p 6380
