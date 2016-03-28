all: libredispp.a libredispp.so apolloCache

daemon:libredispp.a libredispp.so apolloCacheDaemon

CXXFLAGS ?= -std=c++11 -g -O3 -Isrc -L/usr/local/lib -L. $(EXTRA_CXXFLAGS) -Werror -lboost_program_options -lboost_filesystem -lboost_coroutine -lboost_system -lboost_thread -lpthread -lboost_context -lboost_date_time -lboost_log_setup -lboost_log -lredispp -lhiredis
# -DREDIS_DISABLE_CLUSTER

CXXFLAGS2 ?= -std=c++11 -g -O3 -Isrc -L/usr/local/lib -L. $(EXTRA_CXXFLAGS) -Werror -lboost_program_options -lboost_filesystem -lboost_coroutine -lboost_system -lboost_thread -lpthread -lboost_context -lboost_date_time -lboost_log_setup -lboost_log -lredispp  -lhiredis -DDAEMON 
#-DREDIS_DISABLE_CLUSTER

smallFlags=-std=c++11 -g -O3 -Isrc $(EXTRA_CXXFLAGS) -Werror -c



VPATH += src project

apolloCacheDaemon: project/main.cpp project/client_http.hpp project/server_http.hpp project/serverResource.hpp libredispp.a renesolalog.o
	g++ $(CXXFLAGS2) libredispp.a renesolalog.o project/client_http.hpp project/server_http.hpp project/serverResource.hpp project/main.cpp -oapolloCacheDaemon
	rm -f *.o

apolloCache: project/main.cpp project/client_http.hpp project/server_http.hpp project/serverResource.hpp libredispp.a renesolalog.o
	g++ $(CXXFLAGS) libredispp.a renesolalog.o project/client_http.hpp project/server_http.hpp project/serverResource.hpp project/main.cpp -oapolloCache
	rm -f *.o

redispp.o: src/redispp.cpp
	g++ $(smallFlags) src/redispp.cpp
renesolalog.o: src/renesolalog.cpp
	g++ $(smallFlags) src/renesolalog.cpp
libredispp.a: redispp.o
	ar cr libredispp.a redispp.o

redispp.pic.o: src/redispp.cpp
	g++ -fPIC $(smallFlags) src/redispp.cpp -oredispp.pic.o

libredispp.so: redispp.pic.o
	g++ -shared redispp.pic.o -o libredispp.so

clean:
	rm -f *.o
cleanall:
	rm -f *.o libredispp.a libredispp.so apolloCache
