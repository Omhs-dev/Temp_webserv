#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

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
#include <iterator> // for std::istream_iterator
#include <numeric>	// for std::accumulate

#include "enumeration.hpp"

class LocationConfig
{
	private:
		std::string root;
		bool autoindex;
		std::string alias;
		std::string index;
		std::map<int, std::string> redirect;
		std::string locationPath;
		std::string clientMaxBodySize;
		std::map<int, std::string> errorPage;
		std::map<std::string, std::string> cgi;
		std::vector<std::string> allowMethods;

	public:
		LocationConfig();
		LocationConfig(const LocationConfig &other);
		LocationConfig &operator=(const LocationConfig &other);
		~LocationConfig();
		
		// Setters
		void setRoot(const std::string &root);
		void setAutoindex(bool value);
		void setAlias(const std::string &alias);
		void setIndex(const std::string &index);
		void setRedirect(const std::map<int, std::string> &redirect);
		void setLocationPath(const std::string &locationPath);
		void setClientMaxBodySize(const std::string &clientMaxBodySize);
		void setErrorPage(const std::map<int, std::string> &errorPage);
		void setCgi(const std::map<std::string, std::string> &cgi);
		void setAllowMethods(const std::vector<std::string> &allowMethods);
		
		std::string getRoot() const;
		bool getAutoindex() const;
		std::string getAlias() const;
		std::string getIndex() const;
		std::map<int, std::string> getRedirect() const;
		std::string getLocationPath() const;
		std::string getClientMaxBodySize() const;
		std::map<int, std::string> getErrorPage() const;
		std::map<std::string, std::string> getCgi() const;
		std::vector<std::string> getAllowMethods() const;
};

#endif