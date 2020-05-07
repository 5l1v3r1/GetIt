#pragma once

#include <ctime>
#include <string>
#include <boost/format.hpp>

#include "domain/FormdataRequestBody.hpp"
#include "domain/RequestBody.hpp"
#include "gui/widget/BodyWidget/Body.hpp"
#include "gui/widget/FormdataWidget/FormdataWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class FormdataBodyWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class FormdataBodyWidget: public Body
    {
        Q_OBJECT
        
        public:
            explicit FormdataBodyWidget(QWidget* parent = nullptr);
            ~FormdataBodyWidget() override;

            std::string getName() override;
            getit::domain::RequestBody* getRequestBody() override;

        private:
            Ui::FormdataBodyWidget* ui;

            static std::string generateBoundary();
            getit::domain::FormdataRequestBody body;
            const std::string name = "Formdata";
    };
}
