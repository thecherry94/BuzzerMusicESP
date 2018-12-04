#pragma once

#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"


#include <map>
#include <functional>

void* connectAP(void*);
void* createAP(void*);


struct SClientInfo
{
    uint32_t id;
    std::map<std::string, void*> data;
};


struct SConnectAPParams
{
    // WiFi Network
    std::string ssid;
    std::string pass;

    int numRetries;
    int timeout_time;

    // Thread options
    std::function<void(bool)> onDone;
};


struct SThread
{
    void* returnValue;
    pthread_t thread;
};

typedef std::function<void(AsyncWebSocketClient*, JsonObject&)> WebSocketEventHandler_t;

class CWebServer
{
    private:
        AsyncWebServer* _pHttpServer;
        AsyncWebSocket* _pWebSocket;

        std::map<uint32_t, SClientInfo> _clients;
        
        std::map<std::string, WebSocketEventHandler_t> _events;

        void initHttpServer();
        void initWebSockets();

        // Functions triggered by events
        void onConnectedToAP(bool);

        void onWebSocketMessageReceived(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);

        bool _ready;

    public:
        CWebServer();

        void createSoftAP(std::string, std::string);
        void connectToAP(std::string, std::string);

        void addURL(std::string url, ArRequestHandlerFunction);
        void addWebSocketEvent(std::string type, WebSocketEventHandler_t);
        
        bool isReady() { return _ready; }

        void reset();
};