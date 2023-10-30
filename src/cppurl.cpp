 
#include "../lib/cppurl.hpp"

using namespace marcelb;

// marcelb::Curl::Curl() {
// }


string marcelb::Curl::request(const string& req){
    curl = curl_easy_init();

    readBuffer.clear();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}


static size_t marcelb::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}