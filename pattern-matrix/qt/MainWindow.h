#include <QtGui>
#include "generated/ui_pattern-matrix.h"

#include <iostream>
#include <string>
#include "interpreter.h"
#include "SyntaxHighlight.h"

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    int dance_colour;

protected:

    void update_colours() {
        char t[2048];
        snprintf(t,2048,"(set-weft-yarn! loom (list (vector %f %f %f) (vector %f %f %f)))",
                 m_weft_colour[0].red()/255.0,
                 m_weft_colour[0].green()/255.0,
                 m_weft_colour[0].blue()/255.0,
                 m_weft_colour[1].red()/255.0,
                 m_weft_colour[1].green()/255.0,
                 m_weft_colour[1].blue()/255.0);
        interpreter::eval(t);
        snprintf(t,2048,"(set-warp-yarn! loom (list (vector %f %f %f) (vector %f %f %f)))",
                 m_warp_colour[0].red()/255.0,
                 m_warp_colour[0].green()/255.0,
                 m_warp_colour[0].blue()/255.0,
                 m_warp_colour[1].red()/255.0,
                 m_warp_colour[1].green()/255.0,
                 m_warp_colour[1].blue()/255.0);
        interpreter::eval(t);
        update_interface_colours();
    }

    void update_interface_colours() {
        char t[2048];
        snprintf(t,2048,"background-color: rgb(%i, %i, %i);",
                 m_weft_colour[0].red(),
                 m_weft_colour[0].green(),
                 m_weft_colour[0].blue());
        m_Ui.pushButtonWeft1->setStyleSheet(QString(t));
        snprintf(t,2048,"background-color: rgb(%i, %i, %i);",
                 m_weft_colour[1].red(),
                 m_weft_colour[1].green(),
                 m_weft_colour[1].blue());
        m_Ui.pushButtonWeft2->setStyleSheet(QString(t));
        snprintf(t,2048,"background-color: rgb(%i, %i, %i);",
                 m_warp_colour[0].red(),
                 m_warp_colour[0].green(),
                 m_warp_colour[0].blue());
        m_Ui.pushButtonWarp1->setStyleSheet(QString(t));
        snprintf(t,2048,"background-color: rgb(%i, %i, %i);",
                 m_warp_colour[1].red(),
                 m_warp_colour[1].green(),
                 m_warp_colour[1].blue());
        m_Ui.pushButtonWarp2->setStyleSheet(QString(t));
    }

private slots:

    void warp_change(int s) { m_size=s; rebuild(); }

    void weft_colour1() {
        m_weft_colour[0] = QColorDialog::getColor();
        update_colours();
    }
    void weft_colour2() {
        m_weft_colour[1] = QColorDialog::getColor();
        update_colours();
    }
    void warp_colour1() {
        m_warp_colour[0] = QColorDialog::getColor();
        update_colours();
    }
    void warp_colour2() {
        m_warp_colour[1] = QColorDialog::getColor();
        update_colours();
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

    void eval() {
        interpreter::eval(m_text_editor->toPlainText().toUtf8().constData());
    }

    void keyPressEvent( QKeyEvent *k )
    {
      /*
      int button_num = -1;

      if (k->key() == Qt::Key_Left) button_num = 3;
      if (k->key() == Qt::Key_Right) button_num = 5;
      if (k->key() == Qt::Key_Up) button_num = 1;
      if (k->key() == Qt::Key_Down) button_num = 7;

      if (button_num == -1) {
        if (k->text()=="q")  button_num = 0;
        if (k->text()=="e")  button_num = 2;
        if (k->text()=="s")  button_num = 4;
        if (k->text()=="z")  button_num = 6;
        if (k->text()=="c")  button_num = 8;
      }

      if (button_num != -1) {
        m_buttons[button_num%m_buttons.size()]->setChecked(true);
      }
      setFocus();

      bool colour_change = false;

      if (k->key() == Qt::Key_Escape) {
        dance_colour=(dance_colour+1)%4;
        colour_change = true;
      }
      if (k->key() == Qt::Key_Return) {
        dance_colour=(dance_colour-1)%4;
        if (dance_colour<0) dance_colour=3;
        colour_change = true;
      }

      if (colour_change) {
        switch (dance_colour) {
        case 0:
          m_weft_colour[0] = QColor(255,255,0);
          m_weft_colour[1] = QColor(0,0,255);
          m_warp_colour[0] = QColor(255,255,0);
          m_warp_colour[1] = QColor(0,0,255);
          break;
        case 1:
          m_weft_colour[0] = QColor(255,255,0);
          m_weft_colour[1] = QColor(0,0,255);
          m_warp_colour[0] = QColor(0,0,255);
          m_warp_colour[1] = QColor(255,255,0);
          break;
        case 2:
          m_weft_colour[0] = QColor(255,255,0);
          m_weft_colour[1] = QColor(255,255,0);
          m_warp_colour[0] = QColor(0,0,255);
          m_warp_colour[1] = QColor(0,0,255);
          break;
        case 3:
          m_weft_colour[0] = QColor(255,255,0);
          m_weft_colour[1] = QColor(255,255,0);
          m_warp_colour[0] = QColor(0,0,255);
          m_warp_colour[1] = QColor(0,0,255);
          break;
        }

        update_colours();
      }
      */
    }

    void keyReleaseEvent( QKeyEvent *k )
    {
      int button_num = -1;

      if (k->key() == Qt::Key_Left) button_num = 3;
      if (k->key() == Qt::Key_Right) button_num = 5;
      if (k->key() == Qt::Key_Up) button_num = 1;
      if (k->key() == Qt::Key_Down) button_num = 7;

      if (button_num == -1) {
        if (k->text()=="q")  button_num = 0;
        if (k->text()=="e")  button_num = 2;
        if (k->text()=="s")  button_num = 4;
        if (k->text()=="z")  button_num = 6;
        if (k->text()=="c")  button_num = 8;
      }

      if (button_num != -1) {
        m_buttons[button_num%m_buttons.size()]->setChecked(false);
      }
      setFocus();

    }




private:
    Ui_MainWindow m_Ui;
    QTextEdit *m_text_editor;
    SyntaxHighlight *m_highlighter;

    int m_size;
    vector<QPushButton*> m_buttons;
    vector<QColor> m_weft_colour;
    vector<QColor> m_warp_colour;

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
                    //icon.addFile(QString::fromUtf8(":/images/images/bsquare.png"), QSize(), QIcon::Normal, QIcon::Off);
                    //icon.addFile(QString::fromUtf8(":/images/images/wsquare.png"), QSize(), QIcon::Normal, QIcon::On);
                    pushButton->setIcon(icon);
		    if (m_size>5) {
		      pushButton->setIconSize(QSize(32, 32));
		    } else {
		      pushButton->setIconSize(QSize(64, 64));
		    }
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
