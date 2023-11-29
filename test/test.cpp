#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <string>

#include "../lib/cppurl.hpp"

using namespace std;
using namespace marcelb;

int main () {

    // Curl rest;
    // string header_value = "jebiga";
    // rest.header("API", header_value);
    // cout << rest.get("https://reqres.in/api/users/2") << endl;

    // vector<thread> thr;

    // for (uint i=0; i<4; i++) {
    //     thr.push_back(thread([](){
    //         Curl rest;
    //         string header_value = "jebiga";
    //         rest.header("API", header_value);
    //         cout << rest.get("https://reqres.in/api/users/2") << endl;
    //     }));
    // }

    // for (uint i=0; i<thr.size(); i++) {
    //     thr[i].join();
    // }


    // thread t1([](){
    //     Curl rest;
    //     cout << rest.get("https://reqres.in/api/users/2") << endl;
    // });

    // // t1.join();

    // thread t2([](){
    //     Curl rest;
    //     cout << rest.get("https://reqres.in/api/users/2") << endl;
    // });

    // t1.join();
    // t2.join();

    vector<future<string>> debx_responses;

    for (uint i=0; i<4; i++) {
        debx_responses.push_back(async(launch::async, [&](){
            Curl rest;
            // rest.timeout(6000);
            rest.sslvalidate(false);
            return rest.get("https://lab-it.ddns.net");
        }));
    }

    for (uint i=0; i<4; i++) {
        cout << debx_responses[i].get() << endl << endl;
    }
 

}