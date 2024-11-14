#include "HTTPConfigs.hpp"

HTTPConfigs::HTTPConfigs()
{
	    this->_servers = std::vector<ServerConfig>();
}

HTTPConfigs::HTTPConfigs(const HTTPConfigs &copy)
{
	this->_servers = copy._servers;
	// std::cout << "HTTPConfigs copy constructor" << std::endl;
}

HTTPConfigs &HTTPConfigs::operator=(const HTTPConfigs &copy)
{
	if (this != &copy)
	{
		this->_servers = copy._servers;
	}
	// std::cout << "HTTPConfigs assignation operator" << std::endl;
	return *this;
}

std::vector<ServerConfig> HTTPConfigs::getServers() const
{
	return this->_servers;
}

void HTTPConfigs::pushBackServers(const ServerConfig &server)
{
	this->_servers.push_back(server);
}

HTTPConfigs::~HTTPConfigs()
{
	// std::cout << "HTTPConfigs destructor" << std::endl;
}