#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "le.h"

// cette classe est un editeur de texte utiliser pour ecrire les description;

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
