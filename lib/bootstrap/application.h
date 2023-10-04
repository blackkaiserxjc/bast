#pragma once

#include <map>
#include <string>

class application
{
public:
    std::string id() const;
    std::string name() const;
    std::string version() const;
    std::map<std::string, std::string> meta_data();

    void start();
    bool run();
    void stop();

private:
};
