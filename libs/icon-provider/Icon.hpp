
#pragma once

#include "Adafruit_SSD1306.h"


class Icon
{
public:
  Icon(const unsigned char * const pointer, unsigned int width, unsigned int height);

  const unsigned char* getData() const;
  unsigned int getWidth() const;
  unsigned int getHight() const;
  void animate(Adafruit_SSD1306* const pHandler, int startX, int y, int endX, unsigned int animationDelay) const;

private:
  const unsigned char* const m_Pointer;
  unsigned int m_Width;
  unsigned int m_Hight;
};
