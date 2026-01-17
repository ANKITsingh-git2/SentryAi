#include<iostream>
#include<string>
#include <curl/curl.h>

// function to recieve the data coming back from server
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool check_internet_connection(){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        // Target URL (Google DNS) just to test connection
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        
        // Don't verify SSL certificates for this simple test (simplifies things)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        
        // Define where to store the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        
        // Cleanup
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return false;
        }
    }
    
    // If we got data back, we are online!
    return readBuffer.length() > 0;
}