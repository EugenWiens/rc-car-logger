
#pragma once

#include "Icon.hpp"


class IconProvider
{
public:
    enum class IconType{
        rccar,
        batterie,
        speed,
        satellite
    };

    static const Icon& getIcon(IconType iconType);
};