#include "LocationConfig.hpp"

LocationConfig::LocationConfig()
{
	root = "";
	autoindex = false;
	alias = "";
	index = "";
	redirect = {};
	locationPath = "";
	clientMaxBodySize = "";
	errorPage = {};
	cgi = {};
	allowMethods = {};
	// std::cout << "LocationConfig default constructor" << std::endl;
}

LocationConfig::LocationConfig(const LocationConfig &other)
{
	root = other.root;
	autoindex = other.autoindex;
	alias = other.alias;
	index = other.index;
	redirect = other.redirect;
	locationPath = other.locationPath;
	clientMaxBodySize = other.clientMaxBodySize;
	errorPage = other.errorPage;
	cgi = other.cgi;
	allowMethods = other.allowMethods;
	// std::cout << "LocationConfig copy constructor" << std::endl;
}

LocationConfig &LocationConfig::operator=(const LocationConfig &other)
{
	if (this != &other)
	{
		root = other.root;
		autoindex = other.autoindex;
		alias = other.alias;
		index = other.index;
		redirect = other.redirect;
		locationPath = other.locationPath;
		clientMaxBodySize = other.clientMaxBodySize;
		errorPage = other.errorPage;
		cgi = other.cgi;
		allowMethods = other.allowMethods;
	}
	// std::cout << "LocationConfig assignation operator" << std::endl;
	return *this;
}

LocationConfig::~LocationConfig()
{
	// std::cout << "LocationConfig destructor" << std::endl;
}

// Setters

void LocationConfig::setRoot(const std::string &root)
{
	this->root = root;
}

void LocationConfig::setAlias(const std::string &alias)
{
	this->alias = alias;
}

void LocationConfig::setIndex(const std::string &index)
{
	this->index = index;
}

void LocationConfig::setRedirect(const std::map<int, std::string> &redirect)
{
	this -> redirect = redirect;
}

void LocationConfig::setLocationPath(const std::string &locationPath)
{
	this->locationPath = locationPath;
}

void LocationConfig::setClientMaxBodySize(const std::string &clientMaxBodySize)
{
	this->clientMaxBodySize = clientMaxBodySize;
}

void LocationConfig::setErrorPage(const std::map<int, std::string> &errorPage)
{
	this->errorPage = errorPage;
}

void LocationConfig::setCgi(const std::map<std::string, std::string> &cgi)
{
	this->cgi = cgi;
}

void LocationConfig::setAllowMethods(const std::vector<std::string> &allowMethods)
{
	this->allowMethods = allowMethods;
}

//Getters

std::string LocationConfig::getRoot() const
{
	return root;
}

bool LocationConfig::getAutoindex() const
{
	return autoindex;
}

void LocationConfig::setAutoindex(bool value)
{
	autoindex = value;
}

std::string LocationConfig::getAlias() const
{
	return alias;
}

std::string LocationConfig::getIndex() const
{
	return index;
}

std::map<int, std::string> LocationConfig::getRedirect() const
{
	return redirect;
}

std::string LocationConfig::getLocationPath() const
{
	return locationPath;
}

std::string LocationConfig::getClientMaxBodySize() const
{
	return clientMaxBodySize;
}

std::map<int, std::string> LocationConfig::getErrorPage() const
{
	return errorPage;
}

std::map<std::string, std::string> LocationConfig::getCgi() const
{
	return cgi;
}

std::vector<std::string> LocationConfig::getAllowMethods() const
{
	return allowMethods;
}
