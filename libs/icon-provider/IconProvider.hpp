
#pragma once

#include "Icon.hpp"


class IconProvider
{
public:
    enum class IconType{
        rccar,
        batterie,
        speed,
        satellite,
        garbage,
        checkmark,
        info
    };

    static const Icon& getIcon(IconType iconType);
};