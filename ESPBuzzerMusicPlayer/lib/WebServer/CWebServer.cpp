#include "CWebServer.h"
#include <WiFi.h>

#include "global.h"


CWebServer::CWebServer()
{

}



void CWebServer::initHttpServer()
{
    _pHttpServer = new AsyncWebServer(80);
    _pHttpServer->begin();
}





void CWebServer::initWebSockets()
{
    _pWebSocket = new AsyncWebSocket("/ws");
    
    AwsEventHandler handler = std::bind(&CWebServer::onWebSocketMessageReceived, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6);
    _pWebSocket->onEvent(handler);
}



void CWebServer::addURL(std::string url, ArRequestHandlerFunction func)
{
    if (_pHttpServer == nullptr)
        return;
    
    _pHttpServer->on(url.c_str(), func);
}



void CWebServer::addWebSocketEvent(std::string type, WebSocketEventHandler_t func)
{
    if (_pWebSocket == nullptr)
        return;
    
    _events[type] = func;
}



void CWebServer::onWebSocketMessageReceived(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len)
{
    AwsFrameInfo* info = (AwsFrameInfo*)arg;
    if (info->opcode == WS_TEXT)
    {
        data[len] = 0;
        char* d = (char*)data;

        // JSON PARSING
    }
}




void CWebServer::createSoftAP(std::string ssid, std::string pass)
{
    WiFi.softAP(ssid.c_str(), pass.c_str());

    initHttpServer();
    initWebSockets();
}


void CWebServer::onConnectedToAP(bool success)
{
    Serial.printf("Local IP: %s", WiFi.localIP().toString());

    initHttpServer();
    initWebSockets();
}


void CWebServer::connectToAP(std::string ssid, std::string pass)
{
    SConnectAPParams* thread_params = new SConnectAPParams();
    thread_params->ssid = ssid;
    thread_params->pass = pass;
    thread_params->numRetries = 3;
    thread_params->timeout_time = 5000;
    thread_params->onDone = std::bind(&CWebServer::onConnectedToAP, this, std::placeholders::_1);

    SThread thrConnect;
    pthread_create(&thrConnect.thread, nullptr, &connectAP, thread_params);
}

// This function should always be used in a separate thread
//
void* connectAP(void* param)
{
    SConnectAPParams* p;
    p = reinterpret_cast<struct SConnectAPParams*>(param);

    const char* ssid = p->ssid.c_str();
    const char* pass = p->pass.c_str();
    Serial.printf("%s | %s", ssid, pass);

    long t_start = millis();
    int numTry = 0;
    bool connection_success = false;

    while (numTry < p->numRetries && !connection_success)
    {
        DEBUG_PRINTF("WiFi connection try #%d\n", numTry+1);

        WiFi.begin("Cherry", "4991Pk1994");
        
        while (WiFi.status() != WL_CONNECTED)
        {
            if (millis() - t_start >= p->timeout_time)
            {
                DEBUG_PRINT("Wifi connection timeout");
                numTry++;
                t_start = millis();
                break;
            }      
        }

        connection_success = WiFi.status() == WL_CONNECTED;    
    }
    
    delete p;
    p = nullptr;

    p->onDone(connection_success);
    return 0;
}

void* createAP(void*)
{

}


void CWebServer::reset()
{
    if (_pHttpServer == nullptr)
        return;
    
    delete _pHttpServer;
    _pHttpServer = nullptr;

    delete _pWebSocket;
    _pWebSocket = nullptr;

    WiFi.disconnect();
    _events.clear();
}






