#pragma once

#include <memory>

#include "domain/Request.hpp"

namespace getit::gui::widget
{
    struct RequestWidget
    {
    public:
        virtual ~RequestWidget() = default;

        virtual void addToRequest(std::shared_ptr<domain::Request>) = 0;
    };
}