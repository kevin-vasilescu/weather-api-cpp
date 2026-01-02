#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getWeather(const std::string& city, const std::string& apiKey) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    
    if (curl) {
        std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    std::string city = "London";
    std::string apiKey = "YOUR_API_KEY_HERE";
    
    std::string result = getWeather(city, apiKey);
    
    try {
        json data = json::parse(result);
        std::cout << "City: " << data["name"] << std::endl;
        std::cout << "Temperature: " << data["main"]["temp"] << "°C" << std::endl;
        std::cout << "Weather: " << data["weather"][0]["main"] << std::endl;
        std::cout << "Humidity: " << data["main"]["humidity"] << "%" << std::endl;
    } catch (json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    
    return 0;
}
