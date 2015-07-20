#include <QtGui>
#include "generated/ui_pattern-matrix.h"

#include <iostream>
#include <string>
#include "interpreter.h"

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:

private slots:

    void warp_change(int s) { m_size=s; rebuild(); }

    void weft_colour1() {
        QColor color = QColorDialog::getColor();
        char t[2048];
        snprintf(t,2048,"background-color: rgb(%i, %i, %i);",color.red(),color.green(),color.blue());
        m_Ui.pushButton->setStyleSheet(QString(t));
    }

    void button_pressed(bool s) {
        char first[4096];
        snprintf(first,4096,"(loom-update-size! loom %i (list ",m_size);

        string code = first;

        for (vector<QPushButton*>::iterator i=m_buttons.begin(); i!=m_buttons.end(); ++i) {
            if ((*i)->isChecked()) {
                code+="1 ";
            } else {
                code+="0 ";
            }
        }
        code+="))";

        interpreter::eval(code);
    }

private:
    Ui_MainWindow m_Ui;

    int m_size;
    vector<QPushButton*> m_buttons;

    void rebuild() {
        if (m_size>0) {
            clear_layout(m_Ui.verticalLayoutMatrix);
            m_buttons.clear();

            for (int warp = 0; warp<m_size; warp++) {
                QHBoxLayout *row_layout = new QHBoxLayout;
                row_layout->setSpacing(0);
                row_layout->setMargin(0);
                row_layout->setContentsMargins(0,0,0,0);

                for (int weft = 0; weft<m_size; weft++) {

                    QPushButton *pushButton = new QPushButton();
                    pushButton->setObjectName(QString::fromUtf8("pushButton"));
                    QIcon icon;
                    icon.addFile(QString::fromUtf8(":/images/images/black.png"), QSize(), QIcon::Normal, QIcon::Off);
                    icon.addFile(QString::fromUtf8(":/images/images/white.png"), QSize(), QIcon::Normal, QIcon::On);
                    pushButton->setIcon(icon);
                    pushButton->setIconSize(QSize(64, 64));
                    pushButton->setCheckable(true);
                    pushButton->setContentsMargins(0,0,0,0);
                    pushButton->setAutoFillBackground(false);
                    pushButton->setStyleSheet("background-color: rgba(255,255,255,0%);");


                    connect(pushButton, SIGNAL(toggled(bool)), this, SLOT(button_pressed(bool)));
                    m_buttons.push_back(pushButton);
                    row_layout->addWidget(pushButton);
                }
                m_Ui.verticalLayoutMatrix->addLayout(row_layout);
            }
        }
    }



    void clear_layout(QLayout *layout) {
        QLayoutItem *item;
        while((item = layout->takeAt(0))) {
            if (item->layout()) {
                clear_layout(item->layout());
                delete item->layout();
            }
            if (item->widget()) {
                delete item->widget();
            }
            //delete item;
        }
    }
};
