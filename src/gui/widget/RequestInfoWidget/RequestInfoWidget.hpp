#pragma once

#include <memory>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

#include "domain/Request.hpp"
#include "gui/widget/AuthenticationWidget/AuthenticationWidget.hpp"
#include "gui/widget/CookiesWidget/CookiesWidget.hpp"
#include "gui/widget/HeadersWidget/HeadersWidget.hpp"
#include "gui/widget/RequestSettingsWidget/RequestSettingsWidget.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RequestInfoWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class RequestInfoWidget: public QWidget, public RequestWidget
    {
        Q_OBJECT

    public:
        explicit RequestInfoWidget(QWidget* parent = nullptr);
        ~RequestInfoWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        Ui::RequestInfoWidget* ui;

        std::unique_ptr<HeadersWidget> headersWidget;
        std::unique_ptr<CookiesWidget> cookiesWidget;
        std::unique_ptr<AuthenticationWidget> authenticationWidget;
        std::unique_ptr<RequestSettingsWidget> requestSettingsWidget;
    };
}