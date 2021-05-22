
#include "WebUiTask.hpp"
#include "DebugOut.hpp"
#include "DataLogger.hpp"
#include "TimeProvider.hpp"

#include <SPIFFS.h>

const char *ssid = "RC-Car-Logger";
WiFiServer server(80);

namespace
{
    String oneEntryTemplate(" \
  <div class=\"entry\"> \
    <h3>{{name}}<span>{{value}}</span> \
        <div>{{unit}}</div> \
    </h3> \
    <ul> \
        <li>min: <b>{{minValue}}{{unit}}</b></li> \
        <li>max: <b>{{maxValue}}{{unit}}</b></li> \
    </ul> \
  </div> \
");
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

void WebUiTask::run()
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
}

void WebUiTask::handleApiCall(WiFiClient &client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest)
{
    debugLog();
    debugLog() << httpRequest.getResource();
}

void WebUiTask::handleFileRequest(WiFiClient &client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest)
{
    debugLog();
    String object = httpRequest.getResource().toString();

    if (object == String('/'))
    {
        ArduinoHttpServer::StreamHttpReply httpReply(client, httpRequest.getContentType());
        httpReply.send(createIndexHtml());
    }
    else
    {
        if (SPIFFS.exists(object))
        {
            File fs = SPIFFS.open(object);

            if (fs)
            {
                debugLog() << "send page";
                ArduinoHttpServer::StreamHttpReply httpReply(client, httpRequest.getContentType());
                httpReply.send(fs.readString());
                fs.close();
            }
        }
        else
        {
            debugLog() << "send 404";

            ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType(), "404");
            String errorStr("Not found");

            httpReply.send(errorStr);
        }
    }
}

String WebUiTask::createIndexHtml() const
{
    File fs = SPIFFS.open("/index.html");
    String indexPage;

    if (fs)
    {
        indexPage = fs.readString();
        String entries;
        auto dataArray = DataLogger::getInstance().getLogDataArray();

        for (const DataLogger::LogData &dataElement : dataArray)
        {
            if (dataElement.m_Config)
            {
                String oneEntry = oneEntryTemplate;
                oneEntry.replace("{{name}}", dataElement.m_Config.getName());
                oneEntry.replace("{{unit}}", dataElement.m_Config.getUnit());

                if (dataElement.m_Indicators)
                {
                    oneEntry.replace("{{value}}", String(dataElement.m_Indicators.getLast()));
                    oneEntry.replace("{{minValue}}", String(dataElement.m_Indicators.getMin()));
                    oneEntry.replace("{{maxValue}}", String(dataElement.m_Indicators.getMax()));
                }
                else
                {
                    oneEntry.replace("{{value}}", String("---"));
                    oneEntry.replace("{{minValue}}", String("---"));
                    oneEntry.replace("{{maxValue}}", String("---"));
                }

                entries += oneEntry + "\n";

                debugLog() << "entry: " << oneEntry;
            }
        }

        indexPage.replace("{{version}}", "1.1.a");
        indexPage.replace("{{last_update}}", TimeProvider::getInstance().nowAsString());
        indexPage.replace("{{entries}}", entries);
    }

    debugLog() << "indexPage" << indexPage;
    return indexPage;
}
