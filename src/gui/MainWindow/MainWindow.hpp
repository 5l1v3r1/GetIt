#pragma once

#include <boost/format.hpp>
#include <memory>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/Request.hpp"
#include "domain/RequestFactory.hpp"
#include "domain/Response.hpp"

#include "gui/widget/BodyWidget/BodyWidget.hpp"
#include "gui/widget/RequestInfoWidget/RequestInfoWidget.hpp"

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
        void connectSendSlot();

        Ui::MainWindow* ui;
        std::shared_ptr<widget::RequestInfoWidget> requestInfoWidget;
        std::shared_ptr<widget::BodyWidget> bodyWidget;
        const std::shared_ptr<getit::domain::RequestFactory>& factory;

    private slots:
        void setResponse(getit::domain::Response* response);

    signals:
        void requestSent(getit::domain::Response* response);
    };
}