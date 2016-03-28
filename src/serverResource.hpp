#ifndef SERVER_RESOURCE_HPP
#define	SERVER_RESOURCE_HPP
#define BOOST_SPIRIT_THREADSAFE
#include <boost/regex.hpp>
#include "renesolalog.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <condition_variable>
#include <assert.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>  
#include <boost/archive/iterators/binary_from_base64.hpp>  
#include <boost/archive/iterators/transform_width.hpp>
//Added for the default_resource example
#include<fstream>
using namespace std;
//Added for the json:
using namespace boost::property_tree;
using namespace boost::posix_time;
#include "client_http.hpp"
#include "server_http.hpp"
#include "client_https.hpp"
#include "server_https.hpp"
//#include "curl_client.hpp"
//#include "csv.h"
//using namespace restbed;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;
typedef SimpleWeb::Server<SimpleWeb::HTTPS> HttpsServer;
typedef SimpleWeb::Client<SimpleWeb::HTTPS> HttpsClient;
class server_resource
{
public:
	void operator() (boost::shared_ptr<HttpServer> server)
	{
		try
		{
			m_server = server;
			apollo();
			defaultindex();
		}
		catch (exception& e)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << e.what();
		}
		catch (...)
		{

		}
	}
	int apollo()
	{
		try
		{
			m_server->resource["^/admin/orders.json/[[:graph:]]+$"]["GET"] = [&](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) 
			{
				try 
				{
					if (!auth(request, "testapi@orderbot.com:ShinyElephant232#"))
					{
						string ret = "{\"Message\":\"Authorization has been denied for this request.\"}";
						response << "HTTP/1.1 401 Unauthorized\r\nContent-Length: " << ret.length() << "\r\n\r\n" << ret;
						return -1;
					}
					
					string param = request->path_match[0];
					cout << __LINE__ << ":" << param << endl;
					/*for (auto x = request->path_match.begin(); x != request->path_match.end(); ++x)
						cout << __LINE__ << ":" << x->str() << endl;*/

					string body = "test";
					BOOST_LOG_SEV(slg, boost_log->get_log_level()) << __LINE__;
					boost_log->get_initsink()->flush();

					response << "HTTP/1.1 200 OK\r\nContent-Length: " << body.length() << "\r\n\r\n" << body;
				}
				catch (json_parser_error& e)
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (exception& e) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (...) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
					return -1;
				}
			};
			m_server->resource["^/admin/orders.json/([0-9]+)$"]["GET"] = [&](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) 
			{
				try 
				{
					if (!auth(request, "testapi@orderbot.com:ShinyElephant232#"))
					{
						string ret = "{\"Message\":\"Authorization has been denied for this request.\"}";
						response << "HTTP/1.1 401 Unauthorized\r\nContent-Length: " << ret.length() << "\r\n\r\n" << ret;
						return -1;
					}
					string first = "{ \"order_id\":";
					string last = ", \"customer_po\" : null, \"order_date\" : \"2015-04-16\", \"last_modified\" : \"2015-08-13\", \"ship_date\" : \"2015-04-16\", \"shipping_method\" : \"UPS Ground\", \"order_status\" : \"unshipped\", \"customer_id\" : 1, \"order_tax_total\" : 0, \"shipping_total\" : 0, \"discount_total\" : 0, \"order_total\" : 0, \"notes\" : \"\", \"internal_notes\" : \"\", \"shipping_address\" : {			\"store_name\": null, \"full_name\" : \"John Smith\", \"street1\" : \"123 1st St.\", \"street2\" : \"\", \"city\" : \"San Francisco\", \"state\" : \"CA\", \"postal_code\" : \"11223\", \"country\" : \"US\", \"phone\" : \"5555555555\", \"fax\" : null, \"email\" : \"support@orderbot.com\", Orderbot API				November 23rd, 2015 12				\"website\" : null		}, \"billing_address\" : {				\"sales_channel\": \"DTC\", \"full_name\" : \"John Smith\", \"street1\" : \"123 1st St.\", \"street2\" : \"\", \"city\" : \"San Francisco\", \"state\" : \"CA\", \"postal_code\" : \"11223\", \"country\" : \"US\", \"phone\" : \"5555555555\", \"fax\" : null, \"email\" : \"support@orderbot.com\", \"website\" : null			}, \"payment\" : [{					\"payment_method\": \"Paid From Web\", \"amount_paid\" : 0.1				}, { \"payment_method\": \"VOID\", \"amount_paid\" : -24.96 }, { \"payment_method\": \"Credit\", \"amount_paid\" : 24.96 }, { \"payment_method\": \"Customer Service\", \"amount_paid\" : -0.1 }], \"items\" : [{				\"item_id\": 0, \"product_id\" : 96211, \"sku\" : \"ASDF123\", \"name\" : \"Test Product\", \"quantity\" : 1, \"unit_price\" : 0, \"discount\" : 0, \"product_tax\" : 0, \"product_tax_total\" : 0, \"product_total\" : 0, \"weight\" : 0.5			}], \"tracking_numbers\" : null, \"other_charges\" : null }";
					string number = request->path_match[1];
					string body = first + number + last;

					BOOST_LOG_SEV(slg, boost_log->get_log_level()) << __LINE__;
					boost_log->get_initsink()->flush();

					response << "HTTP/1.1 200 OK\r\nContent-Length: " << body.length() << "\r\n\r\n" << body;
				}
				catch (json_parser_error& e)
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (exception& e) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (...) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
					return -1;
				}
			};
			m_server->resource["^/admin/orders.json/([0-9]+)$"]["PUT"] = [&](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
			{
				try
				{
					if (!auth(request, "testapi@orderbot.com:ShinyElephant232#"))
					{
						string ret = "{\"Message\":\"Authorization has been denied for this request.\"}";
						response << "HTTP/1.1 401 Unauthorized\r\nContent-Length: " << ret.length() << "\r\n\r\n" << ret;
						return -1;
					}
					//cout << __LINE__ << endl;
					BOOST_LOG_SEV(slg, boost_log->get_log_level()) << __LINE__;
					boost_log->get_initsink()->flush(); 

					string body = "{ \"response_code\": 1, \"orderbot_order_id\" : 2, \"reference_order_id\" : null, \"success\" : true, \"message\" : \"Order has been updated successfully!\" }";
					response << "HTTP/1.1 200 OK\r\nContent-Length: " << body.length() << "\r\n\r\n" << body;
				}
				catch (json_parser_error& e)
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (exception& e) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (...) {
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
					return -1;
				}
			};
			return 0;
		}
		catch (exception& e)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << e.what();
			return -1;
		}
		catch (...)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << "unknown error";
			return -1;
		}
	}
	
	void defaultindex()
	{
		try
		{
			m_server->default_resource["GET"] = [](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
				string filename = "web";

				string path = request->path;

				//Replace all ".." with "." (so we can't leave the web-directory)
				size_t pos;
				while ((pos = path.find("..")) != string::npos) {
					path.erase(pos, 1);
				}

				filename += path;
				ifstream ifs;
				//A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
				if (filename.find('.') == string::npos) {
					if (filename[filename.length() - 1] != '/')
						filename += '/';
					filename += "index.html";
				}
				ifs.open(filename, ifstream::in);

				if (ifs) {
					ifs.seekg(0, ios::end);
					size_t length = ifs.tellg();

					ifs.seekg(0, ios::beg);

					response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";

					//read and send 128 KB at a time if file-size>buffer_size
					size_t buffer_size = 131072;
					if (length>buffer_size) {
						vector<char> buffer(buffer_size);
						size_t read_length;
						while ((read_length = ifs.read(&buffer[0], buffer_size).gcount())>0) {
							response.stream.write(&buffer[0], read_length);
							response << HttpServer::flush;
						}
					}
					else
						response << ifs.rdbuf();

					ifs.close();
				}
				else {
					string content = "Could not open file " + filename;
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
				}
			};

		}
		catch (exception& e)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << e.what();
		}
	}
	
private:
		boost::shared_ptr<HttpServer> m_server;
		
		bool auth(std::shared_ptr<HttpServer::Request> request,const string& user_pass)
	{
		string encode_user_pass;
		if (!SimpleWeb::Base64Encode(user_pass, &encode_user_pass))
			return false;
		for (auto& h : request->header)
		{
			cout << h.first << ":" << h.second << endl;
			if (h.first == "Authorization")
			{
				if (h.second == ("Basic " + encode_user_pass))
				{
					return true;
				}
			}
		}
		return false;
	}
};

class servers_resource
{
public:
	servers_resource(boost::shared_ptr<HttpsServer> server)
	{
		try
		{
			m_server = server;
			apollo();
			defaultindex();
		}
		catch (exception& e)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << e.what();
		}
		catch (...)
		{

		}
	}
	int apollo()
	{
		try
		{
			m_server->resource["^/v1/oauth2/token$"]["POST"] = [](HttpsServer::Response& response, std::shared_ptr<HttpsServer::Request> request)
			{
				try
				{
					/*string encode_user_pass;
					if (!SimpleWeb::Base64Encode(user_pass, &encode_user_pass))
						return false;*/
					for (auto& h : request->header)
					{
						cout << h.first << ":" << h.second << endl;
						/*if (h.first == "Authorization")
						{
							if (h.second == ("Basic " + encode_user_pass))
							{
								return true;
							}
						}*/
					}
					stringstream ss;
					ss << request->content.rdbuf();
					string content=ss.str();
					cout << content << endl;
					
					/*BOOST_LOG_SEV(slg, boost_log->get_log_level()) << content;
					boost_log->get_initsink()->flush();*/
					string body = "{\"scope\":\"https://uri.paypal.com/services/subscriptions https://api.paypal.com/v1/payments/.* https://api.paypal.com/v1/vault/credit-card https://uri.paypal.com/services/applications/webhooks openid https://uri.paypal.com/payments/payouts https://api.paypal.com/v1/vault/credit-card/.*\",\"nonce\":\"2016-03-02T01:35:46ZVE_OhmUsT5Vet3P2_cfdNCJgtyAklDR25q-gpGOGz0Q\",\"access_token\":\"A101.ommTBLGTeWL-kV_w1GM21nkCPhryvD-GnRKq0elXjtWeRAkSGYiIFfAQt-Y406QZ.gAqorjqLhDOmv4PEw7trNR3L5Ua\",\"token_type\":\"Bearer\",\"app_id\":\"APP-80W284485P519543T\",\"expires_in\":32400}";
					response << "HTTP/1.1 200 OK\r\nContent-Length: " << body.length() << "\r\n\r\n" << body;
				}
				catch (json_parser_error& e)
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (exception& e) 
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
					return -1;
				}
				catch (...) 
				{
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
					return -1;
				}
			};
		}
		catch (...) 
		{
			return -1;
		}
	}

	void defaultindex()
	{
		try
		{
			m_server->default_resource["GET"] = [](HttpsServer::Response& response, std::shared_ptr<HttpsServer::Request> request) {
				string filename = "web";

				string path = request->path;

				//Replace all ".." with "." (so we can't leave the web-directory)
				size_t pos;
				while ((pos = path.find("..")) != string::npos) {
					path.erase(pos, 1);
				}

				filename += path;
				ifstream ifs;
				//A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
				if (filename.find('.') == string::npos) {
					if (filename[filename.length() - 1] != '/')
						filename += '/';
					filename += "index.html";
				}
				ifs.open(filename, ifstream::in);

				if (ifs) {
					ifs.seekg(0, ios::end);
					size_t length = ifs.tellg();

					ifs.seekg(0, ios::beg);

					response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";

					//read and send 128 KB at a time if file-size>buffer_size
					size_t buffer_size = 131072;
					if (length>buffer_size) {
						vector<char> buffer(buffer_size);
						size_t read_length;
						while ((read_length = ifs.read(&buffer[0], buffer_size).gcount())>0) {
							response.stream.write(&buffer[0], read_length);
							response << HttpServer::flush;
						}
					}
					else
						response << ifs.rdbuf();

					ifs.close();
				}
				else {
					string content = "Could not open file " + filename;
					response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
				}
			};

		}
		catch (exception& e)
		{
			//BOOST_LOG(test_lg::get()) << __LINE__ << ": " << e.what();
		}
	}

private:
	boost::shared_ptr<HttpsServer> m_server;
};

#endif	