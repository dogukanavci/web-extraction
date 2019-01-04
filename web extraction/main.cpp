#include <stdio.h>
#include <iostream>
#include "web.hpp"

int main(void)
{
    web web;
    std::string page=web.ConvertPageToString("https://www.contextures.com/xlSampleData01.html");
    std::string table=web.ExtractTable(page);
    std::cout<<table;
    return 0;
}
