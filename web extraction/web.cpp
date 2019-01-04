#include "web.hpp"

size_t web::write_data(void *ptr, size_t size, size_t nmemb, void *stream){
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

std::string web::ConvertPageToString(char* URL){
    CURL *curl_handle;
    static const char *headerfilename = "head.out";
    FILE *headerfile;
    static const char *bodyfilename = "body.out";
    FILE *bodyfile;
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    /* init the curl session */
    curl_handle = curl_easy_init();
    
    /* set URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, URL);
    /* no progress meter please */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    
    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    
    /* open the header file */
    headerfile = fopen(headerfilename, "wb");
    if(!headerfile) {
        curl_easy_cleanup(curl_handle);
        return "error";
    }
    
    /* open the body file */
    bodyfile = fopen(bodyfilename, "wb");
    if(!bodyfile) {
        curl_easy_cleanup(curl_handle);
        fclose(headerfile);
        return "error";
    }
    
    /* we want the headers be written to this file handle */
    curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, headerfile);
    
    /* we want the body be written to this file handle instead of stdout */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
    
    /* get it! */
    curl_easy_perform(curl_handle);
    
    /* close the header file */
    fclose(headerfile);
    
    /* close the body file */
    fclose(bodyfile);
    
    std::string page;
    std::ifstream file("body.out");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            page.append(line);
        }
        file.close();
    }
    else
        std::cout<<"error finding the file";
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    return page;
}

std::string web::ExtractTable(std::string s){
    std::string table;
    bool appendMode=false;
    for(int i = 0; i<s.length(); i++) {
        if (s[i]=='<' && s[i+1]=='t' && s[i+2]=='a' && s[i+3]=='b' && s[i+4]=='l' && s[i+5]=='e') {
            appendMode=true;
        }
        else if (s[i]=='<' && s[i+1]=='/' && s[i+2]=='t' && s[i+3]=='a' && s[i+4]=='b' && s[i+5]=='l') {
            appendMode=false;
        }
        if (appendMode) {
            table += (s[i]);
        }
    }
    return table;
}
