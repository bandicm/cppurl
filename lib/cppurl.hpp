#ifndef _CPPURL_
#define _CPPURL_

#include <curl/curl.h>
#include <string>

namespace marcelb {

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp); 

class Curl {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    

    public:
    // Curl();
    string request(const string& req);


};


}

#endif
