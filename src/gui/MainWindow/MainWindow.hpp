#pragma once

#include <boost/format.hpp>
#include <memory>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/FormdataRequestBody.hpp"
#include "domain/RawRequestBody.hpp"
#include "domain/Request.hpp"
#include "domain/RequestFactory.hpp"
#include "domain/Response.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::gui
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(const std::shared_ptr<getit::domain::RequestFactory>& factory, QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        void connectSignals();
        void connectHeadersSlots();
        void connectCookiesSlots();
        void connectFormdataSlots();
        void connectSendSlot();
        static std::string generateBoundary();

        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        Ui::MainWindow* ui;
        const std::shared_ptr<getit::domain::RequestFactory>& factory;

    private slots:
        void formdataItemsChanged(QTreeWidgetItem*, int);
        void setResponse(getit::domain::Response* response);

    signals:
        void requestSent(getit::domain::Response* response);
    };
}