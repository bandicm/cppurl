 
#include "../lib/cppurl.hpp"

using namespace marcelb;

static size_t marcelb::bodyCallback(void *contents, size_t size, size_t nmemb, void *body_ptr) {
    ((string*)body_ptr)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static size_t marcelb::headerCallback(char* buffer, size_t size, size_t nitems, void* header_ptr) {
    string header_member = string(buffer);
    string key, value;

    auto doublepoint = header_member.find(": ");
    if (doublepoint < header_member.length()){
        key = header_member.substr(0, doublepoint);
        value = header_member.substr(doublepoint+2, header_member.length()-2);
        ((map<string, string>*)header_ptr)->insert(make_pair(key, value));
    }
    
    return nitems * size;
}


Curl& marcelb::Curl::header(const string& key, const string& value) {
    headers = curl_slist_append(headers, string(key + ": " + value).c_str());
    return *this;
}

Curl& marcelb::Curl::header(const map<string, string> &_headers) {
    for (auto h : _headers) {
        header(h.first, h.second);
    }

    return *this;
}

Curl& marcelb::Curl::useragent(const string& useragent_) {
    _useragent = useragent_;
    return *this;
}

Curl& marcelb::Curl::timeout(const long timeout_) {
    _timeout = timeout_;
    return *this;
}

Curl& marcelb::Curl::sslverifyoff() {
    _sslverifyoff = true;
    return *this;
}

Curl& marcelb::Curl::httpv(const http_version protocol_v) {
    _protocol_v = protocol_v;
    return *this;
}

string marcelb::Curl::get(const string& req){
    curl = curl_easy_init();

    body.clear();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        if (headers != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        if (!_useragent.empty()) {
            curl_easy_setopt(curl, CURLOPT_USERAGENT, _useragent.c_str());
        }
        if (_timeout > 0) {
            curl_easy_setopt (curl, CURLOPT_TIMEOUT_MS , _timeout);
        }
        if (_sslverifyoff) {
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, _sslverifyoff ? 0 : 1);
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, _sslverifyoff ? 0 : 1);
        }
        if (_protocol_v > DEFAULT) {
            curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)_protocol_v);
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bodyCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeader);
        
        curlStatus = curl_easy_perform(curl);
        if(curlStatus == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatus);
        }
        curl_easy_cleanup(curl);
    }

    return body;
}

Curl& marcelb::Curl::clearheader() {
    headers = NULL;
    return *this;
}

Curl& marcelb::Curl::clearuseragent() {
    _useragent.clear();
    return *this;
}
