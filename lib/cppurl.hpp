#ifndef _CPPURL_
#define _CPPURL_

#include <curl/curl.h>
#include <string>
#include <string.h>
#include <map>
#include <iostream>

namespace marcelb {

using namespace std;

static size_t bodyCallback(void *contents, size_t size, size_t nmemb, void *body_ptr); 
static size_t headerCallback(char* buffer, size_t size, size_t nitems, void* header_ptr); 
enum http_version { DEFAULT, HTTP1_0, HTTP1_1, HTTP2, HTTP2TLS, HTTP2PK, HTTP3 = 30};

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
    CURLcode curlStatus;
    long httpStatus;
    map<string, string> responseHeader;
    string body;

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
     * Omogući/onemogući validaciju certifikata kod SSL veza
    */

    Curl& sslverifyoff();

    /**
     * Postavi verziju HTTP protokola
     * HTTP1_0 - HTTP1_1 - HTTP2 - HTTP2TLS - HTTP2PK - HTTP3 
    */

    Curl& httpv(const http_version protocol_v);

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
