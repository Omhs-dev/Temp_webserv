#ifndef HTTPCONFIGS_HPP
#define HTTPCONFIGS_HPP

#include <cstring>
#include <vector>

#include "ServerConfig.hpp"

class HTTPConfigs
{
	private:
		std::vector<ServerConfig> _servers;

	public:
		HTTPConfigs();
		HTTPConfigs(const HTTPConfigs &copy);
		HTTPConfigs &operator=(const HTTPConfigs &copy);
		~HTTPConfigs();

		std::vector<ServerConfig> getServers() const;
		void pushBackServers(const ServerConfig &server);
};


#endif