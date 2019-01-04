#ifndef web_hpp
#define web_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <curl/curl.h>

class web{
public:
    std::string ConvertPageToString(char* URL);
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
    std::string ExtractTable(std::string page);
};


#endif /* web_hpp */
