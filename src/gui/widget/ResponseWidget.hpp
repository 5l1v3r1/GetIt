#pragma once

#include <memory>

#include "domain/Response.hpp"

namespace getit::gui::widget
{
    struct ResponseWidget
    {
    public:
        virtual ~ResponseWidget() = default;

        virtual void setResponse(domain::Response*) = 0;
    };
}