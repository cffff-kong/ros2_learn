#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "cpp-httplib/httplib.h"
#include "rclcpp/rclcpp.hpp"

class Downloader
{
public:
    void Download(const std::string &host, const std::string &path,
                  const std::function<void(const std::string &, const std::string &)> &callback_word_count)
    {
        std::cout << "线程" << std::this_thread::get_id() << std::endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if(response && response->status==200){
            callback_word_count(path, response->body);
        }
    };

    void StartDownload(const std::string &host, const std::string &path,
                       const std::function<void(const std::string &, const std::string &)> &callback_word_count) 
    {
        auto download_fun=std::bind(&Downloader::Download, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        std::thread thread(download_fun,host,path,callback_word_count);
        thread.detach();
    };
};

int
main(int argc, char **argv)
{
    auto downloader = Downloader();
    auto word_count = [](const std::string &path, const std::string &result) -> void
    {
        std::cout << "下载完成" << std::endl;
        std::cout << path << " " << result.length() << std::endl;
    };

    downloader.StartDownload("http://0.0.0.0:8000", "novel1.txt", word_count);
    downloader.StartDownload("http://0.0.0.0:8000", "novel2.txt", word_count);
    downloader.StartDownload("http://0.0.0.0:8000", "novel3.txt", word_count);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}