#include "textedit.h"

textedit::textedit()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *hlayout = new QHBoxLayout();
    edit = new QTextEdit();
    QPushButton *bold = new QPushButton("Gras");
    QPushButton *underline = new QPushButton("souligner");

    hlayout->addWidget(bold);
    hlayout->addWidget(underline);
    layout->addLayout(hlayout);
    layout->addWidget(edit);
    connect(bold, SIGNAL(clicked(bool)), this, SLOT(bold()));
    connect(underline, SIGNAL(clicked(bool)), this, SLOT(underline()));

    this->setLayout(layout);
}

void textedit::bold()
{
    edit->setText(edit->toPlainText().replace(edit->textCursor().selectionStart(), edit->textCursor().selectionEnd() - edit->textCursor().selectionStart(), "<b>" + edit->textCursor().selectedText() + "</b>"));
}

void textedit::setText(QString text)
{
    edit->setText(text);
}

QString textedit::toHtml()
{
    return edit->toHtml();
}

QString textedit::toPlainText()
{
    return edit->toPlainText();
}

void textedit::underline()
{
    edit->setText(edit->toPlainText().replace(edit->textCursor().selectionStart(), edit->textCursor().selectionEnd() - edit->textCursor().selectionStart(), "<u>" + edit->textCursor().selectedText() + "</u>"));
}
