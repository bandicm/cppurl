 
#include "../lib/cppurl.hpp"

using namespace marcelb;

static size_t marcelb::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
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
}


string marcelb::Curl::get(const string& req){
    curl = curl_easy_init();

    readBuffer.clear();
    
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

Curl& marcelb::Curl::clearheader() {
    headers = NULL;
    return *this;
}

Curl& marcelb::Curl::clearuseragent() {
    _useragent.clear();
    return *this;
}
