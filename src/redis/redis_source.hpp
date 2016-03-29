#ifndef REDIS_RESOURCE_HPP
#define	REDIS_RESOURCE_HPP
#define BOOST_SPIRIT_THREADSAFE

#include "renesolalog.hpp"
#include "redispp.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <condition_variable>
#include <assert.h>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "server_http.hpp"
#include "client_http.hpp"
#include "hirediscommand.h"
#include "redis_errorcode.hpp"
#include "shared.hpp"
#include "redis_thread_pool.hpp"
//Added for the default_resource example
using namespace std;
using namespace boost::property_tree;
using namespace RedisCluster;
using namespace redispp;
using namespace boost::posix_time;
typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;


/////////general method 
// string GENERAL_BATCH_CREATE(const ptree& pt,string keyTitle,string operation)
// {
// 	try
// 	{	std::lock_guard<std::mutex> locker(lockRedis);
// 		ptree pChild = pt.get_child("requestData");
		
// 		string key="",keyall;
// 		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
// 		{
// 			std::ostringstream buf; 
// 			write_json(buf,(it->second),false);
// 			std::string json = buf.str();
// 			//cout<<json<<endl;
// 			key=it->second.get<string>("id");
// 			////cout<<key<<endl;

// 			string tempkey=keyTitle+":"+key;
// 			//cout<<__LINE__<<":"<<tempkey<<endl;
// 			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
// 			int retint=exists->integer;
// 			freeReplyObject(exists);
// 			if(retint)
// 			{
// 				////cout<<"adfadgagdadgafdadfafda"<<endl;
// 				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
// 				//conn.del(tempkey);
// 			}
			
			
// 			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
// 			//if(!conn.hset(tempkey, "value", json))
// 			{
// 				throw std::runtime_error(std::string("error set to redis"));
// 			}
// 			keyall+=tempkey+",";
// 		}
// 		basic_ptree<std::string, std::string> retJson;
// 		retJson.put<int>("errorCode",200);
// 		retJson.put<std::string>("message",operation+" to cache[KV_MF] successfully");
// 		retJson.put<std::string>("replyData",keyall);
// 		retJson.put<std::string>("replier","apollo-cache");

// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		return ss.str();
// 	}
// 	catch(json_parser_error& e) 
// 	{
// 		basic_ptree<std::string, std::string> retJson;
// 		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
// 		retJson.put<std::string>("message",operation+" to cache[KV_MF]:json read or write error");
// 		retJson.put<std::string>("replyData",e.what());
// 		retJson.put<std::string>("replier","apollo-cache");

// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
//         BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
//          boost_log->get_initsink()->flush();

// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		return ss.str();
// 	}
// 	catch(exception& e) 
// 	{
// 		basic_ptree<std::string, std::string> retJson;
// 		retJson.put<int>("errorCode",UNKNOWN_ERROR);
// 		retJson.put<std::string>("message",operation+" to cache[KV_MF] unknown error");
// 		retJson.put<std::string>("replyData",e.what());
// 		retJson.put<std::string>("replier","apollo-cache");

// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
//        BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
//          boost_log->get_initsink()->flush();

// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		return ss.str();
// 	}
// }
// string GENERAL_LIST_BY_KEYS(const ptree& pt,string keyTitle,string operation)
// {
// 	try
// 	{	std::lock_guard<std::mutex> locker(lockRedis);
// 		ptree pChild = pt.get_child("requestData");
		
// 		string key="",keyall;
// 		basic_ptree<std::string, std::string> retJson,retchidren;
// 		retJson.put<int>("errorCode",200);
// 		retJson.put<std::string>("message",operation+" from cache[KV_MF] successfully");
// 		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
// 		{
// 			std::ostringstream buf; 
// 			write_json(buf,(it->second),false);
// 			std::string json = buf.str();
// 			//cout<<json<<endl;
// 			key=it->second.get<string>("id");

// 			string tempkey=keyTitle+":"+key;
// 			//cout<<tempkey<<endl;
// 			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
// 			int retint=exists->integer;
// 			freeReplyObject(exists);
// 			if(retint)
// 			{
// 				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
// 				string value="";
// 				if(reply->str!=nullptr)
// 				{
// 					string value(reply->str);
				
// 					//cout<<"value:"<<value<<endl;
// 					//freeReplyObject( reply );
// 					//string value=conn.hget(tempkey,"value");
// 					value = value.substr(0, value.length()-1);
				
// 					ptree valuePtree;
// 					istringstream valueStream(value);
// 					read_json(valueStream, valuePtree);
// 					retchidren.push_back(std::make_pair("", valuePtree));
// 				}
// 				freeReplyObject(reply);
// 			}	
// 		}
// 		retJson.add_child("replyData", retchidren);
// 		retJson.put<std::string>("replier","apollo-cache");
// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
// 		string temp=ss.str();
// 		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
// 		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
// 		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
// 		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
// 		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
// 		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
// 		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
// 		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
// 		////cout<<__LINE__<<":"<<temp<<endl;
// 		return temp;
// 	}
// 	catch(json_parser_error& e) 
// 	{
// 		basic_ptree<std::string, std::string> retJson;
// 		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
// 		retJson.put<std::string>("message",operation+" from cache[KV_MF]:json read or write error");
// 		retJson.put<std::string>("replyData",e.what());
// 		retJson.put<std::string>("replier","apollo-cache");

// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
//         BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
//          boost_log->get_initsink()->flush();

// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		return ss.str();
// 	}
// 	catch(exception& e) 
// 	{
// 		basic_ptree<std::string, std::string> retJson;
// 		retJson.put<int>("errorCode",UNKNOWN_ERROR);
// 		retJson.put<std::string>("message",operation+" from cache[KV_MF] unknown error");
// 		retJson.put<std::string>("replyData",e.what());
// 		retJson.put<std::string>("replier","apollo-cache");

// 		ptime now = second_clock::local_time();  
// 		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
// 		////cout<<now_str<<endl;
// 		retJson.put<std::string>("replyTime",now_str);
//         BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
//          boost_log->get_initsink()->flush();

// 		std::stringstream ss;
// 		write_json(ss, retJson);
// 		return ss.str();
// 	}
// }
string GENERAL_LIST_BY_KEYWORDS(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF] successfully");

		//获取所有key
		string tempkey=keyTitle+":*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		//HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		////cout<<__LINE__<<":"<<reply->type<<endl;
		////cout<<__LINE__<<":"<<reply->integer<<endl;

		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*//cout<<__LINE__<<":"<<reply->type<<endl;
		//cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"hget %s value", retkey[i]->str));
				string value= tempreply->str;
				value = value.substr(0, value.length()-1);
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
			
				retchidren.push_back(std::make_pair("", valuePtree));	
				freeReplyObject(tempreply);
			}
		}
		freeReplyObject(reply);
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
         boost_log->get_initsink()->flush();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
         boost_log->get_initsink()->flush();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

int apollo(HttpServer& server,string url)
{
	try
	{
    server.resource["^/"+url+"$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        try {
            ptree pt;
			////cout<<__LINE__<<endl;
		    read_json(request->content, pt);
			
			////cout<<__LINE__<<endl;
			string operation=pt.get<string>("operation");
			//string dataType=pt.get<string>("dataType");
			string retString;
			bool retBool;
			if((operation.compare("LIST_TRADETERM_BY_KEYWORDS")==0))
            {
                
                retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:trade","LIST_TRADETERM_BY_KEYWORDS");
                retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
                response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
            }
            // else if((operation.compare("LIST_WEBSITE_BY_KEYS")==0))
            // {
                
            //     retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:website","LIST_WEBSITE_BY_KEYS");
            //     retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            //     response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
            // }
            // else if((operation.compare("BATCH_CREATE_SEAPORT")==0))
            // {
                
            //     retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:seaport","BATCH_CREATE_SEAPORT");
            //     retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            //     response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
            // }
        }
		catch(json_parser_error& e) 
		{
			//cout<<e.what()<<endl;
			//{"errorCode":200,"message":"session read from cache[2] successfully","replyData":[{"sessionId":"01234567890123456789","value":{"userId":"01234567890123456789"}}],"replier":"apollo-cache","replyTime":"2015-05-25 08:00:00"}
			ptree retJson;
			retJson.put("errorCode",JSON_READ_OR_WRITE_ERROR);
			retJson.put("message","json parser error");
			retJson.put("replyData",e.what());
			retJson.put("replier","apollo-cache");

			ptime now = second_clock::local_time();  
			string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
			////cout<<now_str<<endl;
			retJson.put<std::string>("replyTime",now_str);
			std::stringstream ss;
			write_json(ss, retJson);
			////cout<<ss.str();
			string retString=ss.str();
			retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
			response <<"HTTP/1.1 400 Bad Request\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
			return -1;
		}
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
			return -1;
        }
		catch(...) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
			return -1;
        }
    };
		return 0;
	}
	catch(exception& e) 
	{
          BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
         boost_log->get_initsink()->flush();
		  return -1;
	}
	catch(...) 
	{
        BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<"unknown error";
         boost_log->get_initsink()->flush();
         
		  return -1;
	}
}
void defaultindex(HttpServer& server)
{
    try
    {
        std::lock_guard<std::mutex> locker(lockRedis);
         server.default_resource["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        string filename="web";
        
        string path=request->path;
        
        //Replace all ".." with "." (so we can't leave the web-directory)
        size_t pos;
        while((pos=path.find(".."))!=string::npos) {
            path.erase(pos, 1);
        }
        
        filename+=path;
        ifstream ifs;
        //A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
        if(filename.find('.')==string::npos) {
            if(filename[filename.length()-1]!='/')
                filename+='/';
            filename+="index.html";
        }
        ifs.open(filename, ifstream::in);
        
        if(ifs) {
            ifs.seekg(0, ios::end);
            size_t length=ifs.tellg();
            
            ifs.seekg(0, ios::beg);

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";
            
            //read and send 128 KB at a time if file-size>buffer_size
            size_t buffer_size=131072;
            if(length>buffer_size) {
                vector<char> buffer(buffer_size);
                size_t read_length;
                while((read_length=ifs.read(&buffer[0], buffer_size).gcount())>0) {
                    response.stream.write(&buffer[0], read_length);
                    response << HttpServer::flush;
                }
            }
            else
                response << ifs.rdbuf();

            ifs.close();
        }
        else {
            string content="Could not open file "+filename;
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };

    }
    catch(exception& e) 
    {
          BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
         boost_log->get_initsink()->flush();
    }
}
void serverRedisResource(HttpServer& server,string redisHost,unsigned int redisPort,string redisPassword,string url)
{
	try
	{
		//init redis connection pool

		 cluster_p = HiredisCommand<ThreadPoolCluster>::createCluster( redisHost.c_str(),boost::lexical_cast<int>(redisPort));

		apollo(server,url);
		defaultindex(server);
	}
	catch(exception& e) 
	{
        
          BOOST_LOG_SEV(slg, severity_level::error) <<__LINE__<<":"<<e.what();
         boost_log->get_initsink()->flush();
	}
	catch(...) 
	{
         
	}
}

 
#endif	