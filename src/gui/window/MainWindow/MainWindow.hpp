#pragma once

#include <QPushButton>
#include <QMainWindow>

#include "domain/RequestFactory.hpp"
#include "gui/widget/HeadersWidget/HeadersWidget.hpp"
#include "gui/widget/BodyWidget/BodyWidget.hpp"
#include "gui/widget/ResponseWidget/ResponseWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::gui::window
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(getit::domain::RequestFactory* requestFactory, QWidget* parent = nullptr);
            ~MainWindow() override;

        private:
            Ui::MainWindow* ui;
            getit::domain::RequestFactory* requestFactory;

            widget::HeadersWidget* headersController;
            widget::BodyWidget* bodyController;
            widget::ResponseWidget* responseController;

        signals:
            void requestSent(domain::Response* response);
    };
}
