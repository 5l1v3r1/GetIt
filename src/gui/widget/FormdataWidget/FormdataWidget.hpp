#pragma once

#include <QFileDialog>
#include <QWidget>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class FormdataWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class FormdataWidget: public QWidget
    {
        Q_OBJECT

        public:
            explicit FormdataWidget(QWidget* parent = nullptr);
            ~FormdataWidget() override;

            bool isFile();
            std::string getKey();
            std::string getValue();

        private:
            Ui::FormdataWidget* ui;

            const int textTypeIndex = 0;
            const int fileTypeIndex = 1;
    };
}
