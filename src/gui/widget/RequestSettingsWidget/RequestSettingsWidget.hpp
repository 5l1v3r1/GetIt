#pragma once

#include <memory>
#include <QWidget>

#include "domain/Request.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RequestSettingsWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class RequestSettingsWidget: public QWidget, public RequestWidget
    {
    public:
        explicit RequestSettingsWidget(QWidget* parent = nullptr);
        ~RequestSettingsWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Ui::RequestSettingsWidget* ui;
    };
}