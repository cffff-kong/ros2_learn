#include <iostream>
#include <functional>
void save_with_free_fun(const std::string &filename)
{
    std::cout << "函数" << filename << std::endl;
}

class FileSaver
{
public:
    void save(const std::string &filename)
    {
        std::cout << "这里是类内方法" << std::endl;
    }
};

int main()
{
    FileSaver *file_saver= new FileSaver();
    auto save_with_lambda = [](const std::string& file_name) -> void
    {
        std::cout << "这里是lambda表达式" << std::endl;
    };

    std::function<void(const std::string&)> save1 = save_with_free_fun;
    std::function<void(const std::string&)> save2 = std::bind(&FileSaver::save, file_saver,
        std::placeholders::_1); //最后一个是参数占位符
    std::function<void(const std::string&)> save3 = save_with_lambda;
    save1("test.txt");
    save2("test.txt");
    save3("test.txt");
    return 0;
}
