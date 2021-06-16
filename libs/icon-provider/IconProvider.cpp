
#include "IconProvider.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// icons
#include "noun_Remote_Control_Car_1136461.h"
#include "icons8-autobatterie-30.h"
#include "satellite-30.h"
#include "icons8-speed-30.h"

namespace {
    const Icon iconStore[] = {
        Icon(bitmap_s6eano, S6EANO_BMPWIDTH, S6EANO_BMPWIDTH),
        Icon(bitmap_lisqle, LISQLE_BMPWIDTH, LISQLE_BMPWIDTH),
        Icon(bitmap_a5vuxg, A5VUXG_BMPWIDTH, A5VUXG_BMPWIDTH),
        Icon(bitmap_a5t6y8i, A5T6Y8I_BMPWIDTH, A5T6Y8I_BMPWIDTH)
    };
}

const Icon& IconProvider::getIcon(IconType iconType)
{
    return iconStore[static_cast<unsigned int>(iconType)];
}
