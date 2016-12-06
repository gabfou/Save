#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "le.h"

class textedit : public QWidget
{
    Q_OBJECT
public:
    textedit();
    QTextEdit *edit;
    QString toPlainText();
    QString toHtml();
    void setText(QString text);
public slots:
    void bold();
    void underline();
};

#endif // TEXTEDIT_H
