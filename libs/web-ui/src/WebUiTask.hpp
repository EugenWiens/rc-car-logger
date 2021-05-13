
#pragma once

#include <TaskSchedulerDeclarations.h>

#include <WiFi.h>
#include <ArduinoHttpServer.h>


class WebUiTask : public Task
{
public:
  WebUiTask(Scheduler* pScheduler, unsigned long interval);

  void setup();
  virtual bool Callback() override;

private:
  void handleApiCall(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest);
  void handleFileRequest(WiFiClient& client, const ArduinoHttpServer::StreamHttpRequest<1024> &httpRequest);
};
