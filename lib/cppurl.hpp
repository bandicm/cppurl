#ifndef _CPPURL_
#define _CPPURL_

#include <curl/curl.h>
#include <string>
#include <map>

namespace marcelb {

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp); 

class Curl {
    CURL *curl;
    CURLcode res;
    string readBuffer;
    struct curl_slist *headers = NULL;
    string _useragent;
    long _timeout = 0;

    public:

    /**
     * Postavi zaglavlje s ključem i vrijednošću
     * Novi pozivi ne brišu stara zaglavlja, ponovljena se prepišu
    */
    Curl& header(const string& key, const string& value);

    /**
     * Postavi zaglavlja iz mape
     * Ponovan poziv prepisat će ona zaglavlja koja postoje
    */
    Curl& header(const map<string, string> &_headers);

    /**
     * Postavi u zaglavlje User-Agent
    */
    Curl& useragent(const string& useragent_);

    /**
     * Postavi vrijeme isteka zahtjeva
    */

    Curl& timeout(const long _timeout);

    /**
     * Izvršiv HTTP GET zahtjev
     * Vraća string HTTP tjela
    */
    string get(const string& req);

    /**
     * Obriši spremljeno zaglavlje
    */
    Curl& clearheader();

    /**
     * Obrši trenutnog User-Agent -a
    */
    Curl& clearuseragent();

};


}

#endif
