AUTOMAKE_OPTIONS=foreign

SUBDIRS=src/redis
libredispp.a-local:
	g++ -std=c++11 -g -O3 -Isrc $(EXTRA_CXXFLAGS) -Werror -c src/redispp.cpp
	ar cr libredispp.a redispp.o
SUBDIRS=src
bin_PROGRAMS=redis_rest

redis_rest_SOURCES=src/curl_client.hpp src/client_http.hpp src/renesolalog.hpp src/serverResource.hpp src/main.cpp
redis_rest_LDADD=lib/librestbed.a libredispp.a