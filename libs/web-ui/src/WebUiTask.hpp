
#pragma once

#include "WorkerTask.hpp"

#include <WiFi.h>
#include <ArduinoHttpServer.h>


class WebUiTask : public WorkerTask
{
public:
  using WorkerTask::WorkerTask;

  void setup() override;

private:
  void handleApiCall(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest);
  void handleFileRequest(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest);
  String createIndexHtml() const;

  void run() override;
};
