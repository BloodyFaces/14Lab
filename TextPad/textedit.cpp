#include "textedit.h"
#include <QtWidgets>

TextEdit::TextEdit(QWidget *wdg): QWidget(wdg)
{
    //выделяю память под layoutы
    hblay=new QHBoxLayout;
    hbtxtlay=new QHBoxLayout;
    vblay=new QVBoxLayout;

    //создаю изображения для кнопок, точнее выкачиваю из файла ресурсов images.qrc
    QPixmap pix1(":/open.png");
    QPixmap pix2(":/save.png");
    QPixmap pix3(":/copy.png");
    QPixmap pix4(":/cut.png");
    QPixmap pix5(":/paste.png");
    QPixmap pix6(":/clean.png");
    QPixmap pix7(":/exit.png");

    //open
    open=new QPushButton;
    open->setIcon(pix1);
    open->setIconSize(pix1.size());
    connect(open, SIGNAL(clicked(bool)), SLOT(slotOpenFile())); //connect - основа Qt: работа с
                                                                //сигналами и слотами
    //save
    save=new QPushButton;
    save->setIcon(pix2);
    save->setIconSize(pix2.size());
    connect(save, SIGNAL(clicked(bool)), SLOT(slotSave()));

    //copy
    copy=new QPushButton;
    copy->setIcon(pix3);
    copy->setIconSize(pix3.size());
    connect(copy, SIGNAL(clicked(bool)), &text, SLOT(copy()));

    //cut
    cut=new QPushButton;
    cut->setIcon(pix4);
    cut->setIconSize(pix4.size());
    connect(cut, SIGNAL(clicked(bool)), &text, SLOT(cut()));

    //paste
    paste=new QPushButton;
    paste->setIcon(pix5);
    paste->setIconSize(pix5.size());
    connect(paste, SIGNAL(clicked(bool)), &text, SLOT(paste()));

    //clean
    clean=new QPushButton;
    clean->setIcon(pix6);
    clean->setIconSize(pix6.size());
    connect(clean, SIGNAL(clicked(bool)), &text, SLOT(clear()));

    //exit
    exit=new QPushButton;
    exit->setIcon(pix7);
    exit->setIconSize(pix7.size());
    connect(exit, SIGNAL(clicked(bool)), SLOT(slotClose()));

    //добавляю горизонтальному layoutу все кнопки
    hblay->addWidget(open);
    hblay->addWidget(save);
    hblay->addWidget(copy);
    hblay->addWidget(cut);
    hblay->addWidget(paste);
    hblay->addWidget(clean);
    hblay->addWidget(exit);

    //добавляю 2-ому горизонтальному layoutу текстовое поле
    hbtxtlay->addWidget(&text);

    //объединяю 2 layoutа в вертикальный
    vblay->addLayout(hblay);
    vblay->addLayout(hbtxtlay);

    //устанавливаю для текущего иджета layout
    this->setLayout(vblay);
}

void TextEdit::slotOpenFile()
{
    QString file="output.txt"; //имя файла
    QFile fn(file); //класс, содержащий инфу о файле
    if(fn.open(QIODevice::ReadOnly | QIODevice::Text))//открываем файл
    {
        QTextStream stream(&fn);//запускаем поток по адресу файла
        text.document()->setPlainText(stream.readAll());//записываю содержимое файла в текстовое поле
    }
    fn.close();//закрываю поток
}

void TextEdit::slotSave()
{
    QString file="output.txt";
    QFile fn(file);
    if(fn.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&fn);
        stream << text.document()->toPlainText();
    }
    fn.close();
}

void TextEdit::slotClose()
{
    dlg=new QDialog;
    dlg->setModal(true);
    QHBoxLayout* hlay1=new QHBoxLayout;
    QHBoxLayout* hlay2=new QHBoxLayout;
    QVBoxLayout* vlay=new QVBoxLayout;
    QLabel* lbl=new QLabel("You have unsaved changes, do you want to save them?");

    QPushButton *b1=new QPushButton("Save");
    QPushButton *b2=new QPushButton("Exit");
    QPushButton *b3=new QPushButton("Cancel");

    hlay1->addWidget(lbl);
    hlay2->addWidget(b1);
    hlay2->addWidget(b2);
    hlay2->addWidget(b3);
    vlay->addLayout(hlay1);
    vlay->addLayout(hlay2);
    dlg->setLayout(vlay);

    connect(b1, SIGNAL(clicked(bool)), SLOT(slotSaveAndCancel()));
    connect(b2, SIGNAL(clicked(bool)), SLOT(slotJustClose()));
    connect(b3, SIGNAL(clicked(bool)), SLOT(slotCancel()));

    dlg->show();
}

void TextEdit::slotCancel()
{
    delete dlg;
}

void TextEdit::slotSaveAndCancel()
{
    delete dlg;
    slotSave();
    close();
}

void TextEdit::slotJustClose()
{
    delete dlg;
    close();
}
