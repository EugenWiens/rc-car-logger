
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
        String currentLine = "";

        if (client.connected())
        {
            if (client.available())
            {
                ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(client);

                if (httpRequest.readRequest())
                {
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
    debugLog() << "handleApiCall:"  << httpRequest.getResource();
    auto& resource = httpRequest.getResource();

    if (resource[0] == String("api"))
    {
        if (resource[1] == String("clear-drag-indicators"))
        {
            DataLogger::getInstance().clearAllDragIndicators();
        }
        else if(resource[1] == String("data"))
        {
            sendRecordedData(client, httpRequest);
        }
    }
}

void WebUiTask::handleFileRequest(WiFiClient &client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest)
{
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

                oneEntry.replace("{{value}}", dataElement.m_Indicators.getLast().toString());
                oneEntry.replace("{{minValue}}", dataElement.m_Indicators.getMin().toString());
                oneEntry.replace("{{maxValue}}", dataElement.m_Indicators.getMax().toString());

                entries += oneEntry + "\n";
            }
        }

        String statusEntry = oneEntryTemplate;
        size_t usedEntries;
        size_t maxEntries;
        DataLogger::getInstance().getStoreStatus(usedEntries, maxEntries);
        statusEntry.replace("{{name}}", "storage");
        statusEntry.replace("{{unit}}", "");

        statusEntry.replace("{{value}}", String(usedEntries));
        statusEntry.replace("{{minValue}}", "");
        statusEntry.replace("{{maxValue}}", String(maxEntries));

        entries += statusEntry + "\n";

        indexPage.replace("{{version}}", VERSION_TAG);
        indexPage.replace("{{last_update}}", TimeProvider::getInstance().nowAsString());
        indexPage.replace("{{entries}}", entries);
    }

    return indexPage;
}

void WebUiTask::sendRecordedData(WiFiClient &client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest) const
{
    ArduinoHttpServer::StreamHttpReply httpReply(client, "text/csv");
    String data;
    DataLogger& dataLogger = DataLogger::getInstance();

    dataLogger.getExportDataHeader(data);
    data += '\n';
    dataLogger.getExportData(data);

    httpReply.send(data);
}