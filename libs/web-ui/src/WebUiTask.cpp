
#include "WebUiTask.hpp"
#include "DebugOut.hpp"

#include <SPIFFS.h>

const char *ssid = "RC-Car-Logger";
WiFiServer server(80);


WebUiTask::WebUiTask(Scheduler* pScheduler, unsigned long interval)
    : Task(interval, TASK_FOREVER, pScheduler, true)
{
  debugLog();
}

void WebUiTask::setup()
{
  WiFi.softAP(ssid);
  SPIFFS.begin();

  debugLog() << "Setting AP (Access Point)...";
  WiFi.softAP(ssid);

  IPAddress ipAddress = WiFi.softAPIP();
  debugLog() << "AP is ready, IP address: " << ipAddress;

  server.begin();
}

bool WebUiTask::Callback()
{
  WiFiClient client = server.available();

  if (client)
  {
    debugLog() << "New Client...";
    String currentLine = "";

    if (client.connected())
    {
      if (client.available())
      {
        debugLog() << "...connected";
        ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(client);

        if (httpRequest.readRequest())
        {
          debugLog() << httpRequest.getResource();
          debugLog() << static_cast<int>(httpRequest.getMethod());

          if (httpRequest.getResource()[0] == String("api"))
          {
            handleApiCall(client, httpRequest);
          }
          else
          {
            if (httpRequest.getMethod() == ArduinoHttpServer::Method::Get)
            {
              handleFileRequest(client, httpRequest);
            }
          }
        }
        else
        {
          ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());

          const char *pErrorStr(httpRequest.getError().cStr());
          String errorStr(pErrorStr);

          httpReply.send(errorStr);
        }
        client.stop();
      }
    }
  }

  return true;
}


void WebUiTask::handleApiCall(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest)
{
  debugLog();
  debugLog() << httpRequest.getResource();
}

void WebUiTask::handleFileRequest(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest)
{
  debugLog();
  String object = httpRequest.getResource().toString();

  if (object == String('/'))
  {
    object = "/index.html";
  }

  File fs = SPIFFS.open(object);

  if (fs)
  {
    debugLog() << "send page";
    ArduinoHttpServer::StreamHttpReply httpReply(client, httpRequest.getContentType());
    httpReply.send(fs.readString());
    fs.close();
  }
  else
  {
    debugLog() << "send 404";

    ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType(), "404");
    String errorStr("Not found");

    httpReply.send(errorStr);
  }
}