#include <iostream>

#include "../lib/cppurl.hpp"

using namespace std;
using namespace marcelb;

int main () {

    Curl rest;

    rest.header("Baba", "Janja").useragent("Dinio api client v1.1.0 - bitelex@bitelex.co");
    cout << rest.get("http://localhost:5000/?param1=tvt&param2=2023") << endl;
    // cout << rest.request("https://reqres.in/api/users/2") << endl;


}