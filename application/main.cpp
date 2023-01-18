#include "argparse.h"
#include <string>
#include <iostream>
#include <curl/curl.h>


auto parse_args(int argc, char const * const argv[])
{
    auto parser = argparse::ArgumentParser();
    parser.add_argument("data").help("data to send");
    parser.add_argument("--access-token").help("access token");
    return parser.parse_args(argc, argv);
}

auto write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t
{
    ((std::string*)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

auto send(std::string const & data, std::string const & token)
{
    auto const token_header = "X-Rollbar-Access-Token: " + token;
    curl_slist * headers = nullptr;
    headers = curl_slist_append(headers, token_header.c_str());
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "content-type: application/json");

    auto handle = curl_easy_init();
    auto buffer = std::string();

    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(handle, CURLOPT_URL, "https://api.rollbar.com/api/1/item/");
    curl_easy_setopt(handle, CURLOPT_POST, 1);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer);

    auto res = curl_easy_perform(handle);
    if (res != CURLE_OK)
    {
        std::cout << "Curl failed: '" << curl_easy_strerror(res) << "'\n";
    }
    else
    {
        int status_code;
        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status_code);

        std::cout << "Curl succeeded: " << status_code << ", reponse: '" << buffer << "'\n";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
}

auto main(int argc, char * argv[]) -> int
{
    auto const args = parse_args(argc, argv);
    auto const data = args.get_value("data");
    auto const token = args.get_value("access_token");
    send(data, token);

    return 0;
}
