#pragma once

#include <memory>
#include <QWidget>

#include "domain/Request.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AuthenticationWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class AuthenticationWidget: public QWidget, public RequestWidget
    {
    public:
        explicit AuthenticationWidget(QWidget* parent = nullptr);
        ~AuthenticationWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Ui::AuthenticationWidget* ui;
    };
}