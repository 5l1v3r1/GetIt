#include "RequestInfoWidget.hpp"
#include "./ui_RequestInfoWidget.h"

using namespace getit::gui::widget;

RequestInfoWidget::RequestInfoWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::RequestInfoWidget()),
    authenticationWidget(std::make_unique<AuthenticationWidget>(this)),
    cookiesWidget(std::make_unique<CookiesWidget>(this)),
    headersWidget(std::make_unique<HeadersWidget>(this)),
    requestSettingsWidget(std::make_unique<RequestSettingsWidget>(this))
{
    ui->setupUi(this);

    this->ui->layoutAuthentication->addWidget(authenticationWidget.get());
    this->ui->layoutCookies->addWidget(cookiesWidget.get());
    this->ui->layoutHeaders->addWidget(headersWidget.get());
    this->ui->layoutRequestSettings->addWidget(requestSettingsWidget.get());
}

RequestInfoWidget::~RequestInfoWidget()
{
    delete ui;
}

void RequestInfoWidget::addToRequest(std::shared_ptr<domain::Request> request)
{
    this->authenticationWidget->addToRequest(request);
    this->cookiesWidget->addToRequest(request);
    this->headersWidget->addToRequest(request);
    this->requestSettingsWidget->addToRequest(request);
}