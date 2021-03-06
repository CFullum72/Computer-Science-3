#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

class Logger
{
public:
    // singleton function
    static Logger &instance()
    {
        static Logger log;
        if (!out.is_open())
        {
            out.open("log.txt", std::fstream::out | std::fstream::app);
        }
        return log;
    }

    ~Logger()
    {
        out.flush();
        out.close();
    }
    // appends string to file
    static void report(const string &str) { out << str << endl; };

private:
    // make sure these cannot be accessed
    Logger() {}
    Logger(const Logger &) {}
    Logger &operator=(const Logger &) {}

    static ofstream out;
};

ofstream Logger::out;

int main(int argc, char const *argv[])
{
    Logger::instance().report("I hate sand. Its corse, rough and it gets everywhere");
    return 0;
}
