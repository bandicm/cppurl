
# Rest client library, using libcurl

A small framework for simple client-side REST API requests for C++. It uses libcurl. It got its name from a play on the words curl and cpp.

## Features

- Object oriented
- Adjustable headers
- Configurable user agent
- Adjustable timeout
- Native C++ containers: map, string
- QA object
- Curl and HTTP code status
- It is possible to turn off certificate validation
- A configurable version of the HTTP protocol

## Installation

Just download the latest release and unzip it into your project. You can turn it on with:

```
#include "cppurl/lib/cppurl.hpp"
using namespace marcelb;
```

## Usage

```c++
// init, and sets
Curl rest;
string header_value = "3849f438uf9uedu8ejweoijwejd09230";
rest.header("API", header_value).timeout(700)
    .httpv(HTTP2).sslverifyoff();
// execute and print
cout << rest.get("https://reqres.in/api/users/2") << endl << 
    "Curl status " << rest.curlStatus << endl << 
    "HTTP status " << rest.httpStatus << endl;

for (auto header : rest.responseHeader) {
    cout << header.first << " " << header.second << endl;
}

```
## License

[APACHE 2.0](http://www.apache.org/licenses/LICENSE-2.0/)


## Support & Feedback

For support and any feedback, contact the address: marcelb96@yahoo.com.

## Contributing

Contributions are always welcome!

Feel free to fork and start working with or without a later pull request. Or contact for suggest and request an option.

