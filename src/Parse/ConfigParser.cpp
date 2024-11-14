// ConfigParser.cpp

#include "ConfigParser.hpp"

ConfigParser::ConfigParser()
{
	this->httpConfigs = HTTPConfigs();
}
ConfigParser::~ConfigParser() {}

// void ConfigParser::initHTTPConfigs()
// {
// 	this->httpConfigs = HTTPConfigs(this->servers);
// }

HTTPConfigs ConfigParser::getHTTPConfigs()
{
    return this->httpConfigs;
}

void ConfigParser::parseConfigFile(const std::string &filename)
{
	// Logger::Itroduction("parseConfigFile 📂");
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
	
    std::string line;
    while (std::getline(file, line))
    {
        // Logger::Specifique(line, "Line 📜");
        if (line.empty() || line[0] == '#' || line == "{")
            continue;

        if (line == "http {")
        {
            removeWhiteSpace(line);
            parseHttpBlock(file);
        }
        else
        {
            throw std::runtime_error("Unexpected line: " + line);
        }
    }

    file.close();
}

// void ConfigParser::initConfigServer(ServerConfig &serverConf)
// {
//     serverConf._clientMaxBodySize = "100";

//     this->required.push_back("index");
//     this->required.push_back("root");
//     this->required.push_back("server_name");
//     this->required.push_back("listen");
//     this->required.push_back("autoindex");
//     this->required.push_back("allow_methods");
//     this->required.push_back("max_body_size");
//     this->required.push_back("error_page");
//     this->required.push_back("return");
//     this->required.push_back("location");
//     this->defined.clear();
// }

void ConfigParser::parseHttpBlock(std::ifstream &file)
{
    // Logger::Itroduction("parseHttpBlock");
    this->blockStack.push_back(HTTP);

    std::string line;
    Logger::SpecifiqueForInt(this->blockStack.size(), "BlockStack size");
    while (!blockStack.empty() && std::getline(file, line))
    {
        // Logger::Specifique(line, "Line 📜");
        line = trim(line);
        if (line.empty() || line[0] == '#' || line == "{")
            continue;
        if (line == "server {")
        {
            ServerConfig serverConfig;
            // initConfigServer(serverConfig);
            parseServerBlock(file, serverConfig);
            httpConfigs.pushBackServers(serverConfig);
        }
        else if (line == "}")
        {
            blockStack.pop_back();
        }
        else
        {
            throw std::runtime_error("Unexpected line inside http block: " + line);
        }
    }
}

void ConfigParser::parseServerBlock(std::ifstream &file, ServerConfig &serverConfig)
{
    this->blockStack.push_back(SERVER);

    std::string line;
    while (!this->blockStack.empty() && std::getline(file, line))
    {
        removeWhiteSpace(line);
        size_t found = line.find("location");
        if (line.empty() || line[0] == '#' || line == "{")
            continue;

        if (line.find("}") != std::string::npos)
        {
            this->blockStack.pop_back();
            break;
        }
        else if (found != std::string::npos)
        {
            LocationConfig confLoc;
            locationPath(line, confLoc);
            parseLocationBlock(file, confLoc);
            // std::vector<LocationConfig> locations;
            serverConfig.pushBackLocations(confLoc);
        }
        else
        {
            std::string key, value;
            setKeyValue(line, key, value);
            // Logger::Specifique(line, "Line 📜");
			// Logger::Specifique(key, "Key 🪜");
			// Logger::Specifique(value, "Value 🪜");
            if (key == "listen")
            {
                // Logger::Specifique(value, "Value 🪜");
                size_t found = value.find(":");
                if (found != std::string::npos)
                {
                    std::string serverName = value.substr(0, found);
                    std::string port = value.substr(found + 1);
                    serverConfig.setServerName(serverName);
                    serverConfig.setPort(port);
                }
                else
                {
                    serverConfig.setListen(value);
                    // Logger::Specifique(serverConfig.getListen(), "Server listen 🪜");
                }
            }
            else if (key == "server_name")
            {
                serverConfig.setServerName(value);
                Logger::Specifique(serverConfig.getServerName(), "Server Name 🪜");
            }
            else if (key == "root")
            {
                serverConfig.setRoot(value);
            }
            else if (key == "index")
            {
                serverConfig.setIndex(value);
            }
            else if (key == "client_max_body_size")
            {
                serverConfig.setClientMaxBodySize(value);
            }
            else if (key == "error_page")
            {
                size_t pos = value.find(" ");
                std::map<int, std::string> errorPage;
                if (pos != std::string::npos)
				{
					int code = std::stoi(value.substr(0, pos));
					std::string path = value.substr(pos + 1);
					errorPage[code] = path;
					serverConfig.setErrorPage(errorPage);
				}
            }
            else if (key == "allow_methods")
            {
                // Logger::Specifique(value, "Value 🪜");
                std::istringstream iss(value);
                std::string method;
                std::vector<std::string> allowMethods;
                while (iss >> method)
                {
                    // RequestType type = strToRequestType(trim(method));
                    // Logger::Specifique(method, "Method 🪜");
                    allowMethods.push_back(method);
                    serverConfig.setAllowMethods(allowMethods);
                }
            }
            else
            {
                throw std::runtime_error("Unknown directive in server block: " + key);
            }

            // this->defined.push_back(key);
            // this->required.erase(std::remove(this->required.begin(), this->required.end(), key), this->required.end());
        }
    }
	if (serverConfig.getServerName().empty() || serverConfig.getPort().empty()) {
        throw std::runtime_error("Missing server name or port in server block");
    }
}

void ConfigParser::parseLocationBlock(std::ifstream &file, LocationConfig &confLocation)
{
    this->blockStack.push_back(LOCATION);

    std::string line;
    std::string key, value;
    while (!this->blockStack.empty() && std::getline(file, line))
    {
        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        if (line == "}")
        {
            this->blockStack.pop_back();
            break;
        }
        else
        {
            setKeyValue(line, key, value);

            if (key == "allow_methods")
            {
                std::istringstream iss(value);
                std::string method;
                std::vector<std::string> allowMethods;
                while (iss >> method)
                {
                    // RequestType type = strToRequestType(trim(method));
                    allowMethods.push_back(method);
                    confLocation.setAllowMethods(allowMethods);
                }
            }
            else if (key == "root")
            {
                confLocation.setRoot(value);
            }
            else if (key == "autoindex")
            {
                if (value == "on")
				{
					confLocation.setAutoindex(true);
				}
				else if (value == "off")
				{
					confLocation.setAutoindex(false);
				}
            }
            else if (key == "alias")
            {
                confLocation.setAlias(value);
                // Logger::Specifique(confLocation.getAlias(), "Alias in the parser");
            }
            else if (key == "index")
            {
                confLocation.setIndex(value);
            }
            else if (key == "cgi")
            {
                std::istringstream iss(value);
                std::string extension, path;
                std::map<std::string, std::string> cgi;
                if (iss >> extension >> path)
                {
                    cgi[extension] = path;
                    confLocation.setCgi(cgi);
                }
            }
            else if (key == "error_page")
            {
                size_t pos = value.find(" ");
                std::map<int, std::string> errorPage;
                if (pos != std::string::npos)
                {
                    int code = std::stoi(value.substr(0, pos));
                    std::string path = value.substr(pos + 1);
                    errorPage[code] = path;
                    confLocation.setErrorPage(errorPage);
                }
            }
            else if (key == "client_max_body_size")
            {
                confLocation.setClientMaxBodySize(value);
            }
            else if (key == "return")
            {
                size_t pos = value.find(" ");
                std::map<int, std::string> redirect;
				if (pos != std::string::npos)
				{
					int code = std::stoi(value.substr(0, pos));
					std::string path = value.substr(pos + 1);
					redirect[code] = path;
					confLocation.setRedirect(redirect);
				}
            }
            else
            {
                throw std::runtime_error("Unknown directive in location block: " + key);
            }
        }
    }
}

void ConfigParser::locationPath(const std::string &line, LocationConfig &confLocation)
{
    size_t pos = line.find('{');
    if (pos != std::string::npos)
    {
        size_t pos2 = line.find('/');
        confLocation.setLocationPath(line.substr(pos2, pos - pos2));
        // Logger::Specifique(confLocation.getLocationPath(), "Location Path in the parser");
        // removeWhiteSpace(confLocation.getLocationPath());
    }
    else
    {
        throw std::runtime_error("Invalid location line: " + line);
    }
}

// ---------------------------------------- UTILS ----------------------------------------- //

void ConfigParser::setKeyValue(std::string &line, std::string &key, std::string &value)
{
    key = "";
    value = "";

    line = trim(line);

    size_t keyEnd = line.find_first_of(" \t");
    if (keyEnd == std::string::npos) {
        key = line; // The entire line is the key
    } else {
        key = line.substr(0, keyEnd);
        size_t valueStart = line.find_first_not_of(" \t", keyEnd);
        if (valueStart != std::string::npos) {
            value = line.substr(valueStart);
        }
    }

    key = trim(key);
    value = trim(value);
}

void ConfigParser::removeWhiteSpace(std::string& line)
{
    const std::string whiteSpace = " \n\r\t\f\v";
    size_t start = line.find_first_not_of(whiteSpace);
    size_t end = line.find_last_not_of(whiteSpace);
    if (start == std::string::npos || end == std::string::npos) {
        line.clear(); // If line is entirely whitespace, clear it
    } else {
        line = line.substr(start, end - start + 1);
    }
}

std::string ConfigParser::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }
    return str.substr(start, end - start + 1);
}


std::string ConfigParser::toUpperCase(const std::string& str)
{
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

RequestType ConfigParser::strToRequestType(const std::string& str)
{
    std::string trimmedStr = trim(str);
    std::string upperStr = toUpperCase(trimmedStr);
    
    if (upperStr == "GET")
        return GET;
    if (upperStr == "POST")
        return POST;
    if (upperStr == "DELETE")
        return DELETE;
    throw std::runtime_error("Unsupported request: " + str);
}

void ConfigParser::printRequestTypes(const std::vector<RequestType>& requestTypes)
{
    for (std::vector<RequestType>::const_iterator it = requestTypes.begin(); it != requestTypes.end(); ++it)
    {
        switch (*it) {
            case GET:
                std::cout << "GET ";
                break;
            case POST:
                std::cout << "POST ";
                break;
            case DELETE:
                std::cout << "DELETE ";
                break;
        }
    }
    std::cout << std::endl;
}

void ConfigParser::printLocationConfig(const LocationConfig& location)
{
    std::cout << "  Location Path: " << location.getLocationPath() << std::endl;
    std::cout << "  {" << std::endl;
    const auto & allowMethods = location.getAllowMethods();
    std::cout << "      Allow Methods: ";
    for (auto it = allowMethods.begin(); it != allowMethods.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
    if (!location.getRoot().empty()) {
        std::cout << "      Root: " << location.getRoot() << std::endl;
    }
    std::cout << "      Autoindex: " << (location.getAutoindex() ? "on" : "off") << std::endl;
    if (!location.getAlias().empty()) {
        std::cout << "      Alias: " << location.getAlias() << std::endl;
    }
    if (!location.getIndex().empty()) {
        std::cout << "      Index: " << location.getIndex() << std::endl;
    }
    if (!location.getCgi().empty()) {
        std::cout << "      CGI: ";
        const auto cgi = location.getCgi();
		for (auto it = cgi.begin(); it != cgi.end(); ++it) {
		    std::cout << it->first << " -> " << it->second << ", ";
		}
        std::cout << std::endl;
    }
    if (!location.getRedirect().empty()) {
        std::cout << "      Redirect: " << location.getRedirect().begin()->first << " -> " << location.getRedirect().begin()->second << std::endl;
    }
    std::cout << "  }" << std::endl;
}

void ConfigParser::printServerConfig(const ServerConfig& server)
{
    std::cout << "Server {" << std::endl;
    std::cout << "  Listen: " << server.getListen() << std::endl;
    std::cout << "  Server Name: " << server.getServerName() << std::endl;
    std::cout << "  Root: " << server.getRoot() << std::endl;
    std::cout << "  Index: " << server.getIndex() << std::endl;
    std::cout << "  Max Body Size: " << server.getClientMaxBodySize() << std::endl;
    const auto & allowMethods = server.getAllowMethods();
    std::cout << "  Allow Methods: ";
    for (auto it = allowMethods.begin(); it != allowMethods.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
    const auto &error = server.getErrorPage();
    for (auto it = error.begin(); it != error.end(); ++it) {
		std::cout << "  Error Page: " << it->first << " -> " << it->second << std::endl;
	}
	const auto &locations = server.getLocations();
	for (auto it = locations.begin(); it != locations.end(); ++it) {
	    printLocationConfig(*it);
	}
    std::cout << "}" << std::endl;
}
