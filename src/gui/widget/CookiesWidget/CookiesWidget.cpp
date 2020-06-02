#include "gui/widget/CookiesWidget/CookiesWidget.hpp"
#include "./ui_CookiesWidget.h"

using namespace getit::gui::widget;

CookiesWidget::CookiesWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::CookiesWidget())
{
    ui->setupUi(this);

    this->connectSignals();
}

CookiesWidget::~CookiesWidget()
{
    delete ui;
}

void CookiesWidget::addToRequest(std::shared_ptr<domain::Request> request)
{
    for(int i = 0; i < ui->treeCookies->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeCookies->topLevelItem(i);
        const auto& cookie = item->text(0).toStdString();
        const auto& value = item->text(1).toStdString();

        request->addCookie(cookie, value);
    }
}

void CookiesWidget::connectSignals()
{
    connect(ui->btnAddCookie, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeCookies);
                row->setText(0, "Key");
                row->setText(1, "Value");
                row->setFlags(treeWidgetItemFlags);
            });

    connect(ui->btnRemoveCookie, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeCookies->currentItem();
            });
}