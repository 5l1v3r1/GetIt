#include "gui/widget/AuthenticationWidget/AuthenticationWidget.hpp"
#include "./ui_AuthenticationWidget.h"

using namespace getit::gui::widget;

AuthenticationWidget::AuthenticationWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::AuthenticationWidget())
{
    ui->setupUi(this);
}

AuthenticationWidget::~AuthenticationWidget()
{
    delete ui;
}

void AuthenticationWidget::addToRequest(std::shared_ptr<domain::Request> request)
{

}