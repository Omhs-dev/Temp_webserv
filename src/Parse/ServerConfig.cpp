#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
    : _root("/"),  // Default root path
      _serverName("localhost"),  // Default server name
      _listen("0.0.0.0"),  // Default listen address
      _port("8080"),  // Default port
      _index("index.html"),  // Default index file
      _redirect(),  // Default empty map
      _clientMaxBodySize("10M"),  // Default client max body size
      _errorPage(),  // Default empty map
      _allowMethods({"GET", "POST", "DELETE"}), // Default allowed methods
      _locations()  // Default empty vector
{
    // Initialize other members to defaults if necessary
}


ServerConfig::ServerConfig(const ServerConfig &other)
{
    _root = other._root;
    _serverName = other._serverName;
    _listen = other._listen;
    _port = other._port;
    _index = other._index;
    _redirect = other._redirect;
    _errorPage = other._errorPage;
    _allowMethods = other._allowMethods;
    _locations = other._locations;
    _clientMaxBodySize = other._clientMaxBodySize;
}

ServerConfig &ServerConfig::operator=(const ServerConfig &other)
{
    if (this != &other)
    {
        _root = other._root;
        _serverName = other._serverName;
        _listen = other._listen;
        _port = other._port;
        _index = other._index;
        _redirect = other._redirect;
        _errorPage = other._errorPage;
        _allowMethods = other._allowMethods;
        _locations = other._locations;
        _clientMaxBodySize = other._clientMaxBodySize;
    }
    return *this;
}

ServerConfig::~ServerConfig() {}

void ServerConfig::setRoot(const std::string &root)
{
    _root = root;
}

void ServerConfig::setServerName(const std::string &serverName)
{
    _serverName = serverName;
}

void ServerConfig::setListen(const std::string &listen)
{
    _listen = listen;
}

void ServerConfig::setPort(const std::string &port)
{
    _port = port;
}

void ServerConfig::setIndex(const std::string &index)
{
    _index = index;
}

void ServerConfig::setRedirect(const std::map<int, std::string> &redirect)
{
    _redirect = redirect;
}

void ServerConfig::setClientMaxBodySize(const std::string &clientMaxBodySize)
{
    _clientMaxBodySize = clientMaxBodySize;
}

void ServerConfig::setErrorPage(const std::map<int, std::string> &errorPage)
{
    _errorPage = errorPage;
}

void ServerConfig::setAllowMethods(const std::vector<std::string> &allowMethods)
{
    _allowMethods = allowMethods;
}

void ServerConfig::setLocations(const std::vector<LocationConfig> &locations)
{
    _locations = locations;
}

void ServerConfig::pushBackLocations(const LocationConfig &location)
{
    _locations.push_back(location);
}

std::string ServerConfig::getRoot() const
{
    return _root;
}

std::string ServerConfig::getServerName() const
{
    return _serverName;
}

std::string ServerConfig::getListen() const
{
    return _listen;
}

std::string ServerConfig::getPort() const
{
    return _port;
}

std::string ServerConfig::getIndex() const
{
    return _index;
}

std::map<int, std::string> ServerConfig::getRedirect() const
{
    return _redirect;
}

std::string ServerConfig::getClientMaxBodySize() const
{
    return _clientMaxBodySize;
}

std::map<int, std::string> ServerConfig::getErrorPage() const
{
    return _errorPage;
}

std::vector<std::string> ServerConfig::getAllowMethods() const
{
    return _allowMethods;
}

std::vector<LocationConfig> ServerConfig::getLocations() const
{
    return _locations;
}
