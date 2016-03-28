#ifndef WEBCLIENT_HPP
#define	WEBCLIENT_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>

class WebClient {
public:
    WebClient();
	WebClient(const std::string&, std::string user, std::string password);
	WebClient(const std::string&, std::string user, std::string password,std::string def);
    bool makeRequest();
    bool makePost();
    bool makeGet();
    bool makeDelete();
    void postField(std::string, std::string);
	void add_header(std::string h)
	{
		m_headerlist = curl_slist_append(m_headerlist, h.c_str());
	}
    std::string getResult() { return m_data; }
    void reset();
    void setURL(const std::string&);
    virtual ~WebClient();
protected:
    CURL* m_curl;
    std::string m_data;
    std::map<std::string, std::string> m_postfields;
    std::string urlEncode(const std::string&);
    char * encodedPostFields;
	struct curl_slist *m_headerlist;
public:
	size_t writeData(const char* buffer, size_t size, size_t nmemb); 
protected:
    std::string encodePostFields();
    static size_t writeDataCallback(char*, size_t, size_t, void*);
    
private:
    WebClient(const WebClient& orig);
};


#include <cstdio>

WebClient::WebClient() {
	curl_global_init(CURL_GLOBAL_ALL);
	encodedPostFields = NULL;
	m_curl = curl_easy_init();
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeDataCallback);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
	m_headerlist = NULL;

#ifdef DEBUG
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
}

WebClient::WebClient(const std::string& url, std::string user, std::string password) : WebClient() {
	setURL(url);
	curl_easy_setopt(m_curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
	std::string userpassword = user + ":" + password;
	//std::cout << "384\n" << userpassword << std::endl;
	curl_easy_setopt(m_curl, CURLOPT_USERPWD, userpassword.c_str());
	//curl_easy_setopt(m_curl, CURLOPT_USERPWD, "admin:admin");
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);
}
WebClient::WebClient(const std::string& url, std::string user,std::string password,std::string def) : WebClient() {
	setURL(url);
	//curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false); // https请求 不验证证书和hosts
	//curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
	//curl_easy_setopt(m_curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
	 string userpass = user + ":" + password;
	//curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
	//curl_easy_setopt(m_curl, CURLOPT_USERPWD, userpass.c_str());
	////curl_easy_setopt(m_curl, CURLOPT_TLSAUTH_USERNAME, user.c_str());
	////curl_easy_setopt(m_curl, CURLOPT_TLSAUTH_PASSWORD, password.c_str());
	//curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);
	/*cout <<__LINE__<<":"<< userpassword << endl;
	cout <<__LINE__<<":"<<  m_data << endl;*/


	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
	curl_easy_setopt(m_curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
	curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);

	curl_easy_setopt(m_curl, CURLOPT_USERPWD, userpass.c_str());
	//curl_easy_setopt(m_curl, CURLOPT_SSLVERSION, 3);

	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);

	//curl_easy_setopt(m_curl, CURLINFO_HEADER_OUT, true);
	//curl_easy_setopt(m_curl, CURLOPT_RETURNTRANSFER, true);
	/*curl_easy_setopt(m_curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 10);*/
	

}
WebClient::WebClient(const WebClient& orig) {}

/**
* Generic make request. As default it's a GET request.
*
* @return
*/
bool WebClient::makeRequest() {
	m_data.clear();
	return 0 == curl_easy_perform(m_curl);
}

/**
* Make the post request
*
* @return bool
*/
bool WebClient::makePost() {

	if (encodedPostFields != NULL) {
		delete encodedPostFields;
	}

	encodedPostFields = strdup(encodePostFields().c_str());

	curl_easy_setopt(m_curl, CURLOPT_POST, 1);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, encodedPostFields);
	cout << __LINE__<<":"<<m_data << endl;
	return makeRequest();
}

/**
* Make the get request
*
* @return bool
*/
bool WebClient::makeGet() {
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);

	return makeRequest();
}

/**
* Make delete request
*
* @return bool
*/
bool WebClient::makeDelete() {

	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");

	return makePost();
}

/**
*
* Add new post fields to the request
*
* @param key std::string
* @param value std::string
* @return void
*/
void WebClient::postField(std::string key, std::string value) {
	m_postfields[key] = value;
}

/**
* Reset the post fields
*/
void WebClient::reset() {
	m_postfields.clear();
}

/**
* Set url to the curl client
*
* @param url
*/
void WebClient::setURL(const std::string& url) {
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
}

/**
*  Encode query to work with curl client
*
* @param str
* @return std::string
*/
std::string WebClient::urlEncode(const std::string& str) {
	char * escaped = curl_easy_escape(m_curl, str.c_str(), str.size());
	std::string ret = std::string(escaped);
	curl_free(escaped);
	return std::string(ret);
}

/**
*
* Encodes the postfields
* @example username=test&password=test
*
* @return std::string
*/
std::string WebClient::encodePostFields() {

	std::string urlencoded = "";

	for (std::map<std::string, std::string>::iterator it = m_postfields.begin(); it != m_postfields.end(); ++it)
	{
		if (it != m_postfields.begin())
			urlencoded.append("&");
		urlencoded.append(it->first + "=" + it->second);
	}

	return urlencoded;
}

/**
* Static function used as a callback for receiving html/json content
*
* @param buffer
* @param size
* @param nmemb
* @param thisPtr
* @return
*/

size_t WebClient::writeDataCallback(char *buffer, size_t size, size_t nmemb, void* thisPtr) {
	if (thisPtr)
		return ((WebClient*)thisPtr)->writeData(buffer, size, nmemb);
	else
		return 0;
}

/**
* Function used to write the received html/json content to a c++ string.
*
* @param buffer
* @param size
* @param nmemb
* @return
*/
size_t WebClient::writeData(const char *buffer, size_t size, size_t nmemb) {
	int result = 0;
	if (buffer != 0){
		m_data.append(buffer, size*nmemb);
		result = size*nmemb;
	}
	/*cout <<__LINE__<<":"<<  buffer << endl;
	cout << __LINE__<<":"<< m_data << endl;*/
	return result;
}

WebClient::~WebClient() {

	if (encodedPostFields) {
		delete encodedPostFields;
	}

	curl_easy_cleanup(m_curl);
	curl_global_cleanup();
}


#endif	/* WEBCLIENT_HPP */

