AUTOMAKE_OPTIONS=foreign

lib_LIBRARIES = libredispp.a
redispp_a_SOURCES =src/redis/redispp.cpp

bin_PROGRAMS=redis_rest

redis_rest_SOURCES=src/curl_client.hpp src/client_http.hpp src/renesolalog.hpp src/serverResource.hpp src/main.cpp
redis_rest_LDADD=lib/librestbed.a libredispp.a