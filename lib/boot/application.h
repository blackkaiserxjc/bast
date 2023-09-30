#pragma once

class application
{
public:
    std::string id() const;
    std::string name() const;
    std::string version() const;
    std::map<string, string> meta_data();

    void start();
    bool run();
    void stop();

private:
};
