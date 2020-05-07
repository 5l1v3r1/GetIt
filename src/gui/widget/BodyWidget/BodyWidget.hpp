#pragma once

#include <QTabWidget>
#include <vector>
#include <memory>

#include "gui/widget/BodyWidget/Body.hpp"
#include "gui/widget/FormdataBodyWidget/FormdataBodyWidget.hpp"
#include "gui/widget/RawBodyWidget/RawBodyWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class BodyWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class BodyWidget: public QTabWidget
    {
        Q_OBJECT

        public:
            explicit BodyWidget(QWidget* parent = nullptr);
            ~BodyWidget() override;

            getit::domain::RequestBody* getRequestBody();

        private:
            Ui::BodyWidget* ui;

            const std::vector<Body*> bodies {
                new FormdataBodyWidget(this),
                new RawBodyWidget(this)
            };
    };
}
