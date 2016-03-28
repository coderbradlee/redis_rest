#ifndef ORDERBOT_HPP
#define	ORDERBOT_HPP

#include  "include.hpp"
//#define DEBUG

class orderbot
{
public:
	orderbot(const std::string& user, const std::string& password, const std::string& url) : m_username(user), m_password(password), m_url(url), m_data_parse_callback(nullptr)
	{
		//register callback
		register_callback();
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
		string user_pass = m_username + ":" + m_password;
		curl_easy_setopt(m_curl, CURLOPT_USERPWD, user_pass.c_str());
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
		//curl(m_download_url, "GET", filename, true);

		if (!share_handle)
		{
			share_handle = curl_share_init();
			curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
		}
		curl_easy_setopt(m_curl, CURLOPT_SHARE, share_handle);
		curl_easy_setopt(m_curl, CURLOPT_DNS_CACHE_TIMEOUT, 60 * 5);
	}
	virtual ~orderbot()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();
	}
	void request(const std::string& method, const std::string& path, const std::string& param, const std::string& content)
	{
		//find data parser callback
		for (auto& res : m_opt_resource)
		{
			if (method == res.first)
			{
				for (auto& res_path : res.second)
				{
					std::smatch sm_res;
					string temp = path + "?" + param;
					//cout<<temp<<endl;
					// cout<<res.first<<endl;

					//cout<<res_path.first<<endl;
					//cout<<res_path.second<<endl;
					if (std::regex_match(temp, sm_res, res_path.first))
					{
						path_match = std::move(sm_res);
						// write_response(socket, request, res_path.second);
						//cout<<__LINE__<<endl;
						m_data_parse_callback = res_path.second;
						// return;
					}
				}
			}
		}
		curl(path, method, param, content);
	}
	string get_data()
	{
		return m_data;
	}
protected:

	static size_t request_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			//cout << __LINE__ << endl;
			return ((orderbot*)thisPtr)->request_write_data(buffer, size, nmemb);
		}

		else
		{
			//cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t request_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			//m_data.clear();
			m_data.append(buffer, size * nmemb);
			// cout<<"m_data:"<<m_data.size()<<endl;
			// cout<<"max_size:"<<m_data.max_size() <<endl;
			// cout<<"capacity:"<<m_data.capacity()<<endl;
			result = size * nmemb;
			// boost::asio::streambuf write_buffer;

		}
		return result;
	}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& param = "", const std::string& content = "")
	{
		set_url(m_url + uri + "?" + param);
		//cout << __LINE__ << ":" << uri << endl;

#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
#endif
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, request_callback);
		curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());

		//curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS,0L);
		curl_easy_setopt(m_curl, CURLOPT_CLOSESOCKETFUNCTION, close_socket_callback);

		curl_easy_setopt(m_curl, CURLOPT_CLOSESOCKETDATA, this);
		on_request();

	}
	void set_url(const std::string& url) const
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	}
	bool on_request()
	{
		m_data.clear();
		return 0 == curl_easy_perform(m_curl);
	}
	static int close_socket_callback(void *clientp, curl_socket_t item)
	{
		if (clientp)
		{
			//cout << __LINE__ << endl;
			((orderbot*)clientp)->process_content();
		}

	}
	void process_content()
	{

		//cout<<m_data<<endl;
		//find right call back
		if (m_data_parse_callback)
		{
			cout << __LINE__ << endl;
			m_data_parse_callback();
		}

	}
	void register_callback()
	{
		m_resource["^/admin/products.json/[[:graph:]]+$"]["GET"] = [&]()
		{
			try
			{
				//parse m_data and update mysql
				ptree pt;
				std::istringstream content(m_data);
				read_json(content, pt);
				for (auto p = pt.begin(); p != pt.end(); ++p)
				{
					cout << p->second.get<int>("product_category_id") << endl;
					cout << p->second.get<string>("product_category") << endl;
					cout << p->second.get<int>("product_group_id") << endl;
					cout << p->second.get<string>("product_group") << endl;
					cout << p->second.get<int>("product_id") << endl;
					cout << p->second.get<string>("product_name") << endl;
					cout << p->second.get<string>("sku") << endl;


					ptree pChild = p->second.get_child("inventory_quantities");

					for (auto it = pChild.begin(); it != pChild.end(); ++it)
					{
						cout << "--------------------------" << endl;
						cout << it->second.get<int>("distribution_center_id") << endl;
						cout << it->second.get<string>("distribution_center_name") << endl;
						cout << it->second.get<double>("inventory_quantity") << endl;
						//scout<<"--------------------------"<<endl;
					}
					cout << "#####################################################" << endl;
				}

				//cout<<m_data<<endl;
				BOOST_LOG_SEV(slg, boost_log->get_log_level()) << __LINE__;
				boost_log->get_initsink()->flush();

			}
			catch (json_parser_error& e)
			{
				cout << e.what() << endl;
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			catch (...)
			{

			}
		};
		copy_opt();
	}
	void copy_opt()
	{
		//Copy the resources to opt_resource for more efficient request processing
		m_opt_resource.clear();
		for (auto& res : m_resource)
		{
			for (auto& res_method : res.second)
			{
				auto it = m_opt_resource.end();
				for (auto opt_it = m_opt_resource.begin(); opt_it != m_opt_resource.end(); opt_it++)
				{
					if (res_method.first == opt_it->first)
					{
						it = opt_it;
						break;
					}
				}
				if (it == m_opt_resource.end())
				{
					m_opt_resource.emplace_back();
					it = m_opt_resource.begin() + (m_opt_resource.size() - 1);
					it->first = res_method.first;
				}
				it->second.emplace_back(std::regex(res.first), res_method.second);
			}
		}
	}
protected:
	std::string m_data;
	CURL* m_curl;
	std::string m_url;
	std::string m_username;
	std::string m_password;
	static CURLSH* share_handle;
	std::unordered_map<std::string, std::unordered_map<std::string,
	    std::function<void()> > >  m_resource;
	std::vector<std::pair<std::string, std::vector<std::pair<std::regex,
	    std::function<void()> > > > > m_opt_resource;
	std::function<void()> m_data_parse_callback;
	std::smatch path_match;
};
CURLSH* orderbot::share_handle = NULL;
#endif

