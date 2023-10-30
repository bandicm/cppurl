#include <iostream>

#include "../lib/cppurl.hpp"

using namespace std;
using namespace marcelb;

int main () {

    Curl rest;

    cout << rest.request("https://reqres.in/api/unknown/2") << endl;

    cout << rest.request("https://reqres.in/api/users/2") << endl;


}