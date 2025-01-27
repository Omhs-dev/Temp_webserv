#include "Parse/ConfigParser.hpp"
#include "Server/Server.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    // Check if the user provided a configuration file
    std::string configFile = "config/webserv.conf"; // Default config file
    if (argc == 2) {
        configFile = argv[1];
    } else if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [configuration_file]" << std::endl;
        return 1;
    }

    try {
        ConfigParser parser;
		parser.parseConfigFile(argv[1]);
        HTTPConfigs configs = parser.getHTTPConfigs();
		
		Logger::SpecifiqueForInt(parser.getHTTPConfigs().getServers().size(), "Number of servers 📏");
		
		for (auto &server : configs.getServers())
		{
			parser.printServerConfig(server);
		}
		
        Server server(configs);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
