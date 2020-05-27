#include "gui/widget/ResponseWidget/ResponseWidget.hpp"
#include "./ui_ResponseWidget.h"

using namespace getit::gui::widget;

ResponseWidget::ResponseWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseWidget())
{
    ui->setupUi(this);
}

ResponseWidget::~ResponseWidget()
{
    delete ui;
}

void ResponseWidget::setResponse(getit::domain::Response* response)
{
    setBody(response);
    setHeaders(response);
}

void ResponseWidget::setBody(getit::domain::Response* response)
{
    ui->body->setText(response->body.c_str());
}

void ResponseWidget::setHeaders(getit::domain::Response* response)
{
    ui->headers->clear();

    for (const auto& [header, value] : response->headers) {
        auto format = boost::format("%1% → %2%") % header % value;
        auto widget = new QListWidgetItem(ui->headers);

        widget->setText(format.str().c_str());
    }
}
