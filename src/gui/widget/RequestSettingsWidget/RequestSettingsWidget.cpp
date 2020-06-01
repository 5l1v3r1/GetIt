#include "gui/widget/RequestSettingsWidget/RequestSettingsWidget.hpp"
#include "./ui_RequestSettingsWidget.h"

using namespace getit::gui::widget;

RequestSettingsWidget::RequestSettingsWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::RequestSettingsWidget())
{
    ui->setupUi(this);
}

RequestSettingsWidget::~RequestSettingsWidget()
{
    delete ui;
}

void RequestSettingsWidget::addToRequest(std::shared_ptr<domain::Request> request)
{

}