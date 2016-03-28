#ifndef PAYPAL_HPP
#define	PAYPAL_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
//#define DEBUG
#include "serverResource.hpp"
class taxfile
{
	// The filename of the uploaded file
private:
	std::string filename;

	// The size of the uploaded file
	int size;

	// The ressource to the file
	std::ofstream fp;
	//std::mutex conLock_;
	/**
	* Constructs a new File Upload
	* @param $filename : the name of the file
	* @param $size : the size of the file
	*/
	/*public function __construct($filename, $size) {
	$this->setFilename($filename);
	$this->setSize($size);

	$this->fp = fopen('/tmp/'.$filename, 'w+');
	}*/
public:
	taxfile(std::string filename, int size, bool bin = false)
	{
		this->setFilename(filename);
		this->setSize(size);
		/*if (bin)
		{
		this->fp = std::ofstream(filename, std::ios::app);
		}
		else
		{
		this->fp = std::ofstream(filename, std::ios::app | std::ios::binary);
		}*/
		if (bin)
		{
			this->fp = std::ofstream(filename, std::ios::binary);
		}
		else
		{
			this->fp = std::ofstream(filename);
		}
	}
	/**
	* Updates the name of the file
	* @param $filename : the new name
	*/
	/*public function setFilename($filename) {
	$this->filename = $filename;
	}*/
	void setFilename(std::string filename)
	{
		this->filename = filename;
	}
	/**
	* Updates the size of the file
	* @param $size : the new size of the file
	*/
	/*public function setSize($size) {
	$this->size = $size;
	}*/
	void setSize(int size)
	{
		this->size = size;
	}
	/**
	* Adds data to the file
	* @param $data : the data to add to the file
	*/
	/*public function addData($data) {
	fwrite($this->fp, $data);
	}*/
	void addData(std::string data)
	{

		this->fp.write(data.c_str(), data.length());
		//std::cout << data << std::endl;
	}
	/**
	* Close the file
	*/
	/*public function close() {
	fclose($this->fp);
	}*/
	~taxfile()
	{
		//std::unique_lock<std::mutex> locker(conLock_);
		this->fp.close();
	}
};

bool create_dir(std::string dir)
{
	try
	{
		return boost::filesystem::create_directories(dir);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cout << "unknown error" << std::endl;
		return false;
	}
}

class download_tax_from_taxrate
{
public:
	download_tax_from_taxrate(const std::string& filename, const std::string& save_path) :path(save_path)
	{
		m_taxfile = boost::shared_ptr<taxfile>(new taxfile(path+"/"+filename, 22));
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
		
		curl(m_download_url, "GET", filename, true);
	}
	virtual ~download_tax_from_taxrate()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();	
	}
	
protected:	
	static size_t download_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			//cout << __LINE__ << endl;
			return ((download_tax_from_taxrate*)thisPtr)->download_write_data(buffer, size, nmemb);
		}

		else
		{
			//cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t download_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.clear();
			m_data.append(buffer, size*nmemb);
			m_taxfile->addData(m_data);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		//cout << __LINE__ << ":" << m_data << endl;
		
		return result;
	}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& filename="", bool auth=false)
	{		
		set_url(uri+filename);		
		//cout << __LINE__ << ":" << uri << endl;
		
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
#endif
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, download_callback);
		curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		cout << __LINE__ << "request:"<<filename << endl;
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
	
protected:	
	std::string m_data;
	CURL* m_curl;
	static const std::string m_download_url;
	boost::shared_ptr<taxfile> m_taxfile;
	std::string path;
};
const string download_tax_from_taxrate::m_download_url = "http://taxrates.csv.s3.amazonaws.com/";
boost::mutex download_mutex;

void thread_download(std::string& filename, std::string& save_path)
{
	//boost::mutex::scoped_lock lock(download_mutex);
	//cout << save_path << ":" << filename << endl;
	BOOST_LOG_SEV(slg, boost_log->get_log_level()) << save_path << "/" << filename;
	boost_log->get_initsink()->flush();
	boost::shared_ptr<download_tax_from_taxrate> p = boost::shared_ptr<download_tax_from_taxrate>(new download_tax_from_taxrate(filename, save_path));
}
string uploads_init_dir()
{
	/*ptime now = second_clock::local_time();
	string now_str = to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());*/
	string default_save_path = "/";
	try
	{
		string fullpath = boost::filesystem::initial_path<boost::filesystem::path>().string();
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(fullpath + "/config.ini", pt);

		string path = boost::lexical_cast<std::string>(pt.get<std::string>("nfs.path"));

		boost::filesystem::path p(path);
		//p.remove_filename();
		std::cout << __LINE__ << ":" << p.string() << std::endl;
		if (!boost::filesystem::exists(p))
		{
			if (!boost::filesystem::create_directories(p.string()))
			{
				return default_save_path;
			}
		}
		else
		{
			long int i = remove_all(p);
			cout <<"delete:"<< i <<" files"<< endl;;
		}

		return path;
	}
	catch (exception& e)
	{

		return default_save_path;
	}
}

#endif	/* PAYPAL_HPP */

