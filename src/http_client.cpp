#include "../include/http_client.h"
#include<iostream>
#include<string>
#include <curl/curl.h>

// Standard callback to capture the server's response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string send_groq_request(const std::string& json_payload, const std::string& api_key) {
    CURL* curl;
    CURLcode res;
    std::string response_buffer;

    // The Groq API Endpoint (Compatible with OpenAI format)
    std::string url = "https://api.groq.com/openai/v1/chat/completions";

    curl = curl_easy_init();
    if(curl) {
        // 1. Set the Headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        // Auth Header: "Authorization: Bearer <YOUR_KEY>"
        std::string auth_header = "Authorization: Bearer " + api_key;
        headers = curl_slist_append(headers, auth_header.c_str());

        // 2. Configure curl
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L); // Use POST
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str()); // Attach JSON
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Attach Headers
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);
        
        // 3. Perform the request
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            std::cerr << "Request Failed: " << curl_easy_strerror(res) << std::endl;
            response_buffer = "ERROR";
        }

        // 4. Cleanup memory
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return response_buffer;
}