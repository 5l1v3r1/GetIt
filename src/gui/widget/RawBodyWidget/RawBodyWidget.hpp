#pragma once

#include <string>

#include "domain/RawRequestBody.hpp"
#include "domain/RequestBody.hpp"
#include "gui/widget/BodyWidget/Body.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RawBodyWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class RawBodyWidget: public Body
    {
        Q_OBJECT

        public:
            explicit RawBodyWidget(QWidget* parent = nullptr);
            ~RawBodyWidget() override;

            std::string getName() override;
            getit::domain::RequestBody* getRequestBody() override;

        private:
            Ui::RawBodyWidget* ui;
            
            getit::domain::RawRequestBody body;
            const std::string name = "Raw";
    };
}