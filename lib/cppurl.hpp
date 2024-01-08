#ifndef _CPPURL_
#define _CPPURL_

#include <curl/curl.h>
#include <string>
#include <string.h>
#include <map>
#include <iostream>

namespace marcelb {

using namespace std;

/**
 * Callback function for parsing the HTTP body
*/
static size_t bodyCallback(void *contents, size_t size, size_t nmemb, void *body_ptr); 

/**
 * Callback function for parsing HTTP headers
*/
static size_t headerCallback(char* buffer, size_t size, size_t nitems, void* header_ptr); 

/**
 * HTTP supported protocols
*/
enum http_version { DEFAULT, HTTP1_0, HTTP1_1, HTTP2, HTTP2TLS, HTTP2PK, HTTP3 = 30};

/**
 * Class for curl request and response
*/
class Curl {
    // input

    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    string _useragent;
    long _timeout = 0;
    bool _sslverifyoff = false;
    http_version _protocol_v = DEFAULT;

    public:

    // output

    // Curl code response status
    CURLcode curlStatus;
    // HTTP code response status
    long httpStatus;
    // HTTP response headers
    map<string, string> responseHeader;
    // HTTP body
    string body;

    /**
     * Set header with key and value
     * New calls do not delete old headers, repeated ones are overwritten
    */
    Curl& header(const string& key, const string& value);

    /**
     * Set headers from folder
     * The redial will overwrite those headers that exist
    */
    Curl& header(const map<string, string> &_headers);

    /**
     * Set in User-Agent header
    */
    Curl& useragent(const string& useragent_);

    /**
     * Set request timeout
    */
    Curl& timeout(const long _timeout);

    /**
     * Disable certificate validation for SSL connections
    */
    Curl& sslverifyoff();

    /**
     * Set HTTP protocol version
     * HTTP1_0 - HTTP1_1 - HTTP2 - HTTP2TLS - HTTP2PK - HTTP3
    */
    Curl& httpv(const http_version protocol_v);

    /**
     * Executable HTTP GET request
     * Returns the HTTP body as string
    */
    string get(const string& req);

    /**
     * Clear saved headers
    */
    Curl& clearheader();

    /**
     * Clear the current User-Agent
    */
    Curl& clearuseragent();

};


}

#endif
