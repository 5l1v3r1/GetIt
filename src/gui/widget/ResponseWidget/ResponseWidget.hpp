#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include <boost/format.hpp>

#include "domain/Response.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class ResponseWidget: public QWidget
    {
        Q_OBJECT

        public:
            explicit ResponseWidget(QWidget* parent = nullptr);
            ~ResponseWidget() override;

        private:
            Ui::ResponseWidget* ui;

            void setBody(domain::Response* response);
            void setHeaders(domain::Response* response);

        public slots:
            void setResponse(domain::Response* response);
    };
}
