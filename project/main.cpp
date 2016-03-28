
#include "serverResource.hpp"

int main() {
	try
	{
	//read config.ini
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini("config.ini", pt);
	unsigned short port=boost::lexical_cast<unsigned short>(pt.get<std::string>("webserver.port"));
	size_t threads=boost::lexical_cast<size_t>(pt.get<std::string>("webserver.threads"));
	url=pt.get<std::string>("webserver.url");
	redisHost=pt.get<std::string>("redis.host");
	redisPort=pt.get<std::string>("redis.port");
	
	//redisPassword=pt.get<std::string>("redis.password");
	redisPassword="";
	/*Connection conn(redisHost, redisPort, redisPassword);
	connRedis=&conn;*/
    //HTTP-server at port 8080 using 4 threads
    HttpServer server(port,threads);
    //serverResource(server);
    serverRedisResource(server,redisHost,redisPort,redisPassword,url);
    thread server_thread([&server](){
        //Start server
        server.start();
    });


	/////////test http client start ////////////////////////////////////////////////////////////////////////////
	 //Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(3));
	//HttpClient client("localhost:8080");
    // curl -X POST http://localhost:8080/t_function_get -d "{\"function_id\":\"A1\"}"
 //  { string json="{\"operation\":\"CREATE_SESSION\",\"requestData\":[{\"sessionId\":\"0\",\"value\":{}}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
 //   stringstream ss(json);    
 //   auto r2=client.request("POST", "/apollo", ss);
 //   cout << r2->content.rdbuf() << endl;
 //  }
 //  cout<<"*****************************************"<<endl;
	/////////////test http client end /////////////////////////////////////////////////////////////////////////////
	//{
	//	string json="{\"operation\":\"ADD_USERID_UNDER_SESSION\",\"requestData\":[{\"sessionId\":\"0\",\"value\":{\"userId\":\"0\"}}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	/*cout<<"*****************************************"<<endl;
	{
		string json="{\"operation\":\"DELETE_SESSION\",\"requestData\":[{\"sessionId\":\"0\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/
	/*cout<<"*****************************************"<<endl;
	{
		string json="{\"operation\":\"QUERY_SESSION\",\"requestData\":[{\"sessionId\":\"0\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}
	cout<<"*****************************************"<<endl;
	{
		string json="{\"operation\":\"QUERY_SESSION\",\"requestData\":[{\"sessionId\":\"0\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}
	cout<<"*****************************************"<<endl;
	{
		string json="{\"operation\":\"UPDATE_SESSION_DEADLINE\",\"requestData\":[{\"sessionId\":\"0\",\"value\":{\"userId\":\"0\",\"deadline\":\"2015-05-26 08:00:00\"}}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}
	cout<<"*****************************************"<<endl;
	{
		string json="{\"operation\":\"UPDATE_SESSION_DEADLINE\",\"requestData\":[{\"sessionId\":\"0\",\"value\":{\"userId\":\"01234567890123456789\",\"deadline\":\"2015-05-26 08:00:00\"}}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/
	//cout<<"*****************************************"<<endl;
	////////////////////test基本档案///////////////////////////
	//{
	//	string json="{\"operation\":\"BATCH_CREATE_AREAS\",\"requestData\":[{\"id\":\"1\",\"areaCode\":\"23\",\"fullName\":\"Europe\",\"shortName\":\"EU\",\"children\":[{\"id\":\"2345678901\",\"areaCode\":\"24\",\"fullName\":\"East Europe\",\"shortName\":\"EE\",\"dr\":0,\"dataVersion\":1}],\"dr\":0,\"dataVersion\":1},{\"id\":\"2\",\"areaCode\":\"23\",\"fullName\":\"Europe\",\"shortName\":\"EU\",\"children\":[{\"id\":\"2345678901\",\"areaCode\":\"24\",\"fullName\":\"East Europe\",\"shortName\":\"EE\",\"dr\":0,\"dataVersion\":1}],\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_AREAS_BY_KEYS\",\"requestData\":[{\"id\":\"1234567890\"},{\"id\":\"12345678901\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_AREAS_BY_KEYS\",\"requestData\":[{\"id\":\"1234567890\"},{\"id\":\"123\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_AREAS_BY_KEYS\",\"requestData\":[{\"id\":\"1\"},{\"id\":\"2\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_AREAS_BY_KEYWORDS\",\"requestData\":[{\"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
 //   {//,{\"id\":\"12345678901\"}
	//	string json="{\"operation\":\"DELETE_AREAS_BY_KEYS\",\"requestData\":[{\"id\":\"1\"},{\"id\":\"3\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"DELETE_AREAS_BY_KEYWORDS\",\"requestData\":[{\"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"BATCH_CREATE_LANGUAGE\",\"requestData\":[{\"id\":\"1\",\"languageCode\":\"12345678901234567890\",\"fullName\":\"Chinese\",\"shortName\":\"Chinese\",\"status\":0,\"dr\":0,\"dataVersion\":1},{\"id\":\"2\",\"languageCode\":\"09876543210987654321\",\"fullName\":\"English\",\"shortName\":\"English\",\"status\":0,\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_LANGUAGE_BY_KEYS\",\"requestData\":[{\"id\":\"1\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_LANGUAGE_BY_KEYWORDS\",\"requestData\":[{\"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"BATCH_CREATE_SHIPVIA\",\"requestData\":[{\"id\":\"1\",\"shipViaCode\":\"1\",\"fullName\":\"Sea\",\"shortName\":\"Sea\",\"status\":0,\"dr\":0,\"dataVersion\":1},{\"id\":\"2\",\"shipViaCode\":\"2\",\"fullName\":\"Air\",\"shortName\":\"Air\",\"status\":0,\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_SHIPVIA_BY_KEYS\",\"requestData\":[{\"id\":\"1\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}
	//cout<<"*****************************************"<<endl;
	//{
	//	string json="{\"operation\":\"LIST_SHIPVIA_BY_KEYWORDS\",\"requestData\":[{\"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
	//	stringstream ss(json);    
	//	auto r2=client.request("POST", "/apollo", ss);
	//	cout << r2->content.rdbuf() << endl;
	//}

	/*{
		string json="{\"operation\":\"BATCH_CREATE_TRADETERM\",\"requestData\":[{\"id\":\"12345678901234567890\",\"tradeTermCode\":\"1\",\"fullName\":\"Free On Board\",\"shortName\":\"FOB\",\"status\":0,\"dr\":0,\"dataVersion\":1},{\"id\":\"09876543210987654321\",\"tradeTermCode\":\"2\",\"fullName\":\"Ex Works\",\"shortName\":\"EXW\",\"status\":0,\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/			
	/*{
		string json="{\"operation\":\"LIST_TRADETERM_BY_KEYS\",\"requestData\":[{\"id\":\"12345678901234567890\"},{\"id\":\"09876543210987654321\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/
	/*{
		string json="{\"operation\":\"LIST_TRADETERM_BY_KEYWORDS\",\"requestData\":[{\"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/
	/*{
		string json="{\"operation\":\"BATCH_CREATE_SEAPORT\",\"requestData\":[{\"id\":\"12345678901234567890\",\"seaportCode\":\"AESP01\",\"fullName\":\"Abu Dhabi\",\"shortName\":\"Abu Dhabi\",\"countryId\": \"12345678901234567890\",\"status\":0,\"dr\":0,\"dataVersion\":1},{\"id\":\"09876543210987654321\",\"seaportCode\":\"ASSP01\",\"fullName\":\"Apia\",\"shortName\":\"Apia\",\"countryId\": \"09876543210987654321\",\"status\":0,\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}

	{
		string json="{\"operation\":\"LIST_SEAPORT_BY_KEYS\",\"requestData\":[{\"id\":\"12345678901234567890\"},{\"id\":\"09876543210987654321\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}
	{
		string json="{\"operation\":\"BATCH_CREATE_WAREHOUSE\",\"requestData\":[{\"id\":\"12345678901234567890\",\"companyId\":\"12345678901234567890\",\"code\":\"CANGKU01\",\"name\":\"CANGKU01\",\"type\":0,\"binControl\":1,\"warehouseKeeperId\":\"12345678901234567890\",\"keeperContactWay\":\"1234567890123456SHSH\",\"address\":\"shanghai\",\"countryId\":\"12345678901234567890\",\"areaId\":\"12345678901234567890\",\"stateProvinceCountry\":\"12345678901234567890\",\"cityId\":\"12345678901234567890\",\"zipCode\":\"0110\",\"defaultSeaport\":\"12345678901234567890\",\"seaportToWarehouseLeadTime\":2,\"defaultAirport\":\"12345678901234567890\",\"airportToWarehouseLeadTime\":1,\"note\":\"仓库管理\",\"dr\":0,\"dataVersion\":1},{\"id\":\"09876543210987654321\",\"companyId\":\"09876543210987654321\",\"code\":\"CANGKU02\",\"name\":\"CANGKU02\",\"type\":0,\"binControl\":1,\"warehouseKeeperId\":\"09876543210987654321\",\"keeperContactWay\":\"09876543210987654321\",\"address\":\"zhejiang\",\"countryId\":\"09876543210987654321\",\"areaId\":\"09876543210987654321\",\"stateProvinceCountry\":\"09876543210987654321\",\"cityId\":\"09876543210987654321\",\"zipCode\":\"1111\",\"defaultSeaport\":\"09876543210987654321\",\"seaportToWarehouseLeadTime\":3,\"defaultAirport\":\"09876543210987654321\",\"airportToWarehouseLeadTime\":4,\"note\":\"仓库a\",\"dr\":0,\"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/
////////////////////////test cluster
	/*{
		string json="{\"operation\":\"BATCH_CREATE_TAX_SCHEDULES\",   \"requestData\":[{      \"id\":\"1111\",      \"code\":\"123\",      \"description\":\"abcdef\",      \"taxFileChildren\":[{         \"taxId\":\"4567890123\",         \"code\":\"22\",         \"description\":\"增值税\",        \"levyingBureau\":\"上海市长宁区财税局\",         \"deductible\":1,         \"isSuperposedTax\":1,         \"calculationMethod\":0,         \"taxRate\":0.17,         \"taxAmount\":0.0,\"dr\":0,\"dataVersion\":1}],   \"dr\":0,   \"dataVersion\":1},{      \"id\":\"2\",      \"code\":\"123\",      \"description\":\"abcdef\",      \"taxFileChildren\":[],   \"dr\":0,   \"dataVersion\":1}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/

	/*{
		string json="{\"operation\":\"LIST_TAX_SCHEDULES_BY_KEYS\",   \"requestData\":[{      \"id\":\"1111\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}
	{
		string json="{   \"operation\":\"LIST_TAX_SCHEDULES_BY_KEYWORDS\",   \"requestData\":[{      \"keyword\":\"id\",\"value\":\"APOLLO-ALL\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}";
		stringstream ss(json);    
		auto r2=client.request("POST", "/apollo", ss);
		cout << r2->content.rdbuf() << endl;
	}*/


//******************test redis cluster*******************8

	/*try
    {
        processCommandPool();
    } catch ( const RedisCluster::ClusterException &e )
    {
        cout << "Cluster exception: " << e.what() << endl;
    }*/

	
	server.initsink->flush();
    server_thread.join();
	delete cluster_p;
	}
	catch(exception& e) {
            cout<< e.what();
        }
	catch(...) 
	{
         
	}
    return 0;
}