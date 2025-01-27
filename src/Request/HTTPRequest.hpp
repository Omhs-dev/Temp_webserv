#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <map>

#include "../Server/Client.hpp"
#include "../Parse/LocationConfig.hpp"
#include "../Parse/ServerConfig.hpp"
#include "../Logger/Logger.hpp"
#include "../Parse/HTTPConfigs.hpp"
#include "../Parse/ServerConfig.hpp"
#include "../Parse/LocationConfig.hpp"

#define REQUEST_DEFAULT_STATE_CODE 200

// class Logger;
class Client;

//--------------------------------------------------------
// to do:
// a function to parse the body
	// if the body is normal body parse it
		// check of if Content-Length is present in the Header
			// if yes determine the exact numbers of bytes the body needs
			// then read and extract the exact number of bytes needed by the body from the request stream and store them as body
			// marque the body as complete once the bytes are read
	// if the body is chunked body parse it
	

// a timeout function for the request

// a function to define the body destination

class HTTPRequest
{
	friend class HTTPRequestTest;
	friend class Logger;
	public:
		enum ParseState
        { 
            START,
            IS_REQUEST_LINE,
            IS_METHODE,
            IS_PATH,
            IS_VERSION,
            IS_HEADERS,
            IS_HEADERS_END,
            IS_BODY_START,
            IS_BODY_NORMAL,
            IS_BODY_CHUNKED,
            IS_BODY_END,
            COMPLETE 
        };
	private:
		Client          *_client;
		LocationConfig  *_location;
		ServerConfig    *_server;
		
		// Request Line
		std::string     _method;
		std::string     _uriPath;
		std::string     _version;
		
		// Headers
		std::string     _query;
		std::string     _rawRequest;
		std::string     _body;
		std::map<std::string, std::string>  _headers;
		std::string     _headerKey;
		std::string     _headerValue;
		bool            _isChunked;
		std::string     _contentLength;
		unsigned long long _iscontentLength;
		int             _chunkSize;
		time_t          _timeout;
		int             _stateCode;
		
		// --- Parse Request Line ---
		void        parseRequestLine(const std::string &line);
		
		// --- Parse Headers ---
		void        parseHeaderLine(const std::string &line);
		
		// --- Parse Body ---
		void        parseBody(std::istringstream stream);
		void        parseNormalBody(const std::string &line);
		void        parseChunkedBody(const std::string &line);
		
		
		// --- UTILS ---
		std::vector<std::string> getAllPathsLocation();
		
		// --- ENUM ---
        ParseState _state;

	public:
		HTTPRequest(Client *client);
		HTTPRequest(const HTTPRequest &src);
		HTTPRequest &operator=(const HTTPRequest &src);
		~HTTPRequest();
		void parseRequest(const std::string &requestData);
		
		// --- CHECKERS ---
		bool    checkHttpVersion();
		bool    checkHostHeader();
		int     checkTransferEncoding();
		int     checkContentLength();
		int     checkMethod();
		int     checkCgi();
		// --- GETTERS ---
		Client          *getClient() const;
		LocationConfig  *getLocation() const;
		ServerConfig    *getServer() const;
		
		// --- Request Line ---
		std::string     getMethod() const;
		std::string     getPath() const;
		std::string     getVersion() const;
		// --- Headers ---
		
		std::map<std::string, std::string> getHeaders() const;
		std::string     getHeaderKey() const;
		std::string     getHeaderValue() const;
		std::string     getBody() const;
		std::string     getQuery() const;
		std::string     getRawRequest() const;
		bool getIsChunked() const;
		unsigned long long getContentLength() const;
		int getChunkSize() const;
		time_t getTimeout() const;
		int getStateCode() const;

		//Setters
		void setStateCode(int stateCode) {_stateCode = stateCode;}
		// --- UTILS ---
		std::string getLineSanitizer(std::stringstream &ss);
		void EnumState(HTTPRequest::ParseState state);
		void errorOccur(int code);
		bool validateLocation(const std::string& path);
		LocationConfig* findLocationConfig(const std::string& path);
		void parseMultipartBody(const std::string& bodyData);
		void saveFile(const std::string& filename, const std::string& content);
		std::string getBoundary();
};

#endif
