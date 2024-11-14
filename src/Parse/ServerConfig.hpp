#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <limits>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cstring>
#include <iterator>
#include <numeric>

#include "enumeration.hpp"
#include "LocationConfig.hpp"

class ServerConfig
{
	private:
		std::string     _root;
		std::string     _serverName;
		std::string     _listen;
		std::string     _port;
		std::string     _index;
		std::map<int, std::string> _redirect;
		std::string     _clientMaxBodySize;
		std::map<int, std::string>  _errorPage;
		std::vector<std::string>    _allowMethods;
		std::vector<LocationConfig> _locations;

	public:
		ServerConfig();
		ServerConfig(const ServerConfig &other);
		ServerConfig &operator=(const ServerConfig &other);
		~ServerConfig();
		
		void pushBackLocations(const LocationConfig &location);
		
		// Setters
		void setRoot(const std::string &root);
		void setServerName(const std::string &serverName);
		void setListen(const std::string &listen);
		void setPort(const std::string &port);
		void setIndex(const std::string &index);
		void setRedirect(const std::map<int, std::string> &redirect);
		void setClientMaxBodySize(const std::string &clientMaxBodySize);
		void setErrorPage(const std::map<int, std::string> &errorPage);
		void setAllowMethods(const std::vector<std::string> &allowMethods);
		void setLocations(const std::vector<LocationConfig> &locations);
		
		// Functions
		std::string getRoot() const;
		std::string getServerName() const;
		std::string getListen() const;
		std::string getPort() const;
		std::string getIndex() const;
		std::map<int, std::string> getRedirect() const;
		std::string getClientMaxBodySize() const;
		std::map<int, std::string> getErrorPage() const;
		std::vector<std::string> getAllowMethods() const;
		std::vector<LocationConfig> getLocations() const;
		// bool getAutoindex() const;
};

#endif