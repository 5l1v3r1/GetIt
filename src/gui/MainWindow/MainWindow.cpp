#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

#include <iostream>

using namespace getit::gui;

MainWindow::MainWindow(const std::shared_ptr<getit::domain::RequestFactory>& factory, QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    factory(factory)
{
    ui->setupUi(this);

    this->connectSignals();
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::connectSignals()
{
    this->connectHeadersSlots();
    this->connectCookiesSlots();
    this->connectFormdataSlots();
    this->connectSendSlot();
}


void MainWindow::connectHeadersSlots()
{
    connect(ui->btnAddHeader, &QPushButton::pressed,
            this, [=]() {
        const auto& row = new QTreeWidgetItem(ui->treeHeaders);
        row->setText(0, "Key");
        row->setText(1, "Value");
        row->setFlags(treeWidgetItemFlags);
    });

    connect(ui->btnRemoveHeader, &QPushButton::pressed,
            this, [=]() {
        delete ui->treeHeaders->currentItem();
    });
}

void MainWindow::connectCookiesSlots()
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

void MainWindow::connectFormdataSlots()
{
    connect(ui->treeBodyFormdata, &QTreeWidget::itemChanged,
            this, &MainWindow::formdataItemsChanged);

    connect(ui->treeBodyFormdataFiles, &QTreeWidget::itemChanged,
            this, &MainWindow::formdataItemsChanged);

    connect(ui->btnAddFormdata, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeBodyFormdata);
                row->setText(0, "Key");
                row->setText(1, "Value");
                row->setFlags(treeWidgetItemFlags);
            });

    connect(ui->btnRemoveFormdata, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeBodyFormdata->currentItem();
                ui->treeBodyFormdata->itemChanged(nullptr, 0);
            });

    connect(ui->btnAddFormdataFile, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeBodyFormdataFiles);
                row->setText(0, "Key");
                row->setFlags(treeWidgetItemFlags);

                emit ui->treeBodyFormdataFiles->itemDoubleClicked(row, 1);
            });

    connect(ui->btnRemoveFormdataFile, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeBodyFormdataFiles->currentItem();
            });

    connect(ui->treeBodyFormdataFiles, &QTreeWidget::itemDoubleClicked,
            this, [=](QTreeWidgetItem* selectedItem, int columnIndex) {
        if (columnIndex != 1) return;

        const auto& fileName = QFileDialog::getOpenFileUrl(this);

        if (!fileName.isEmpty()) {
            selectedItem->setText(1, fileName.toLocalFile());
        }

        if (selectedItem->text(1).isEmpty()) {
            delete selectedItem;
        }
    });
}

void MainWindow::connectSendSlot()
{
    connect(this, &MainWindow::requestSent, this, &MainWindow::setResponse);

    connect(ui->btnSend, &QPushButton::pressed,
            this, [=]() {
                const auto& method = ui->cbMethod->currentText().toStdString();
                const auto& uri = ui->textUri->text().toStdString();
                const auto& contentType = ui->textContentType->text().toStdString();
                const auto& bodyValue = ui->textBodyRaw->document()->toPlainText().toStdString();
                const auto& requestBody = std::make_shared<getit::domain::RawRequestBody>(contentType);
                const auto& request = factory->getRequest(method, uri);

                requestBody->setBody(bodyValue);
                request->setBody(requestBody);

                request->send([=](getit::domain::Response* response) {
                    emit requestSent(response);
                });
            });
}

void MainWindow::formdataItemsChanged(QTreeWidgetItem*, int)
{
    const auto& boundary = generateBoundary();
    const auto& data = std::make_unique<getit::domain::FormdataRequestBody>(boundary);

    for(int i = 0; i < ui->treeBodyFormdata->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeBodyFormdata->topLevelItem(i);
        const auto& formdataKey = item->text(0).toStdString();
        const auto& formdataValue = item->text(1).toStdString();

        data->addElement(formdataKey, formdataValue);
    }

    for(int i = 0; i < ui->treeBodyFormdataFiles->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeBodyFormdataFiles->topLevelItem(i);
        const auto& formdataKey = item->text(0).toStdString();
        const auto& filePath = item->text(1).toStdString();

        data->addFile(formdataKey, filePath);
    }

    ui->textContentType->setText(data->getContentType().c_str());
    ui->textBodyRaw->document()->setPlainText(data->getBody().c_str());
}

std::string MainWindow::generateBoundary()
{
    auto now = std::chrono::system_clock::now();
    auto millis = now.time_since_epoch().count();
    auto boundary = boost::format("%1%") % millis;

    return boundary.str();
}

void MainWindow::setResponse(getit::domain::Response* response)
{
    ui->listResponseHeaders->clear();
    ui->textResponseBody->document()->setPlainText(response->body.c_str());

    for (const auto& [header, value]: response->headers) {
        auto format = boost::format("%1% → %2%") % header % value;
        auto widget = new QListWidgetItem(ui->listResponseHeaders);

        widget->setText(format.str().c_str());
    }

    const auto& requestMethod = ui->cbMethod->currentText().toStdString();
    const auto& uri = ui->textUri->text().toStdString();
    const auto& requestMethodUri = requestMethod + " " + uri;
    ui->lblRequestMethodUri->setText(requestMethodUri.c_str());
}