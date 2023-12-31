#pragma once

#include <boost/asio/signal_set.hpp>
#include <boost/url.hpp>
#include <string>

class options
{
private:
    std::string id_;
    std::string name_;
    std::string version_;
    std::vector<boost::url> endpoints_;

    boost::asio::signal_set signals_;
};
