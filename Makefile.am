AUTOMAKE_OPTIONS=foreign

SUBDIRS=src/redis

bin_PROGRAMS=redis_rest

redis_rest_SOURCES=src/curl_client.hpp src/client_http.hpp src/renesolalog.hpp src/serverResource.hpp src/main.cpp
redis_rest_LDADD=lib/librestbed.a lib/libredispp.a