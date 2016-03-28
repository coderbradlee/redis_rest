//#include "include.hpp"
#include "config.hpp"
#include "serverResource.hpp"
#include <boost/asio/yield.hpp>
#include <boost/asio/coroutine.hpp>

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
		{
			 //HTTP-server at port 8080 using 4 threads
		    HttpServer server(port,threads);
		    //serverResource(server);
		    serverRedisResource(server,redisHost,redisPort,redisPassword,url);
		    thread server_thread([&server](){
		        //Start server
		        server.start();
		    });
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