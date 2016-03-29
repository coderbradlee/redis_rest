//#include "include.hpp"
#include "config.hpp"
#include "serverResource.hpp"
#include <boost/asio/yield.hpp>
#include <boost/asio/coroutine.hpp>
#include "redis/redis_source.hpp"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/any.hpp>
#include "orderbot.hpp"

#define BOOST_DATE_TIME_SOURCE
//#include "credit_ontime.hpp"

using namespace boost::asio;
using namespace std;

int main()
{
	try
	{
	
		//HTTP-server at port 8080 using 4 threads
		HttpServer server(get_config->m_webserver_port, get_config->m_threads);
		//serverResource(server);
		serverRedisResource(server, get_config->m_redis_host, get_config->m_redis_port, get_config->m_redis_password, get_config->m_webserver_url);
		thread server_thread([&server]() {
			//Start server
			server.start();
		});


		{
			this_thread::sleep_for(chrono::seconds(3));
			HttpClient client("localhost:8888");
		    //curl -X POST http://localhost:8888/apollo -d "{\"operation\": \"LIST_TRADETERM_BY_KEYWORDS\",						\"requestData\": [ {\"keyword\":\"id\",					\"value\":\"APOLLO-ALL\"}],\"requestor\": \"apollo-employee-portal\",\"requestTime\": \"2015-05-25 08:00:00\"}"
		  { string json="{\"operation\": \"LIST_TRADETERM_BY_KEYWORDS\",						\"requestData\": [ {\"keyword\":\"id\",					\"value\":\"APOLLO-ALL\"}],\"requestor\": \"apollo-employee-portal\",\"requestTime\": \"2015-05-25 08:00:00\"}";
		   stringstream ss(json);    
		   auto r2=client.request("POST", "/apollo", ss);
		   cout << r2->content.rdbuf() << endl;
		  }
		}

		{
			boost::timer::cpu_timer pass;
			pass.start();

			//orderbot 接口
			boost::shared_ptr<orderbot> order = boost::shared_ptr<orderbot>(new orderbot(get_config->m_orderbot_username, get_config->m_orderbot_password, get_config->m_orderbot_url));
			//order->request("GET", "/admin/products.json/", "class_type=sales&category_name=Rings", "");

			//cout<<order->get_data().length()<<":"<<order->get_data()<<endl;
			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}

		server_thread.join();
	}
	catch (std::exception& e)
	{
		//cout << diagnostic_information(e) << endl;
		cout << e.what() << endl;
	}
	catch (...)
	{

	}
	return 0;
}