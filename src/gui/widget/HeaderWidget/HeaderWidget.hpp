#pragma once

#include <string>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HeaderWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class HeaderWidget: public QWidget
    {
        Q_OBJECT

        public:
            explicit HeaderWidget(QWidget* parent = nullptr);
            ~HeaderWidget() override;

            std::string getKey();
            std::string getValue();

        private:
            Ui::HeaderWidget* ui;
    };
}