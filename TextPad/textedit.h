#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#pragma once
#include <QtWidgets>

class TextEdit: public QWidget
{
    Q_OBJECT //необходимо для реализации сигналов и слотов
private:
    QDialog* dlg;

    //создаю layoutы
    QHBoxLayout *hblay;
    QVBoxLayout *vblay;
    QHBoxLayout *hbtxtlay;

    //создаю кнопки для управления приложением
    QPushButton* open;
    QPushButton* save;
    QPushButton* copy;
    QPushButton* cut;
    QPushButton* paste;
    QPushButton* clean;
    QPushButton* exit;

    //здесь само текстовое поле
    QTextEdit text;

public:
    TextEdit(QWidget* wdg=0); //конструктор

    //слоты для открытия и сохранения файла
public slots:
    void slotOpenFile();
    void slotSave();
    void slotClose();
    void slotCancel();
    void slotSaveAndCancel();
    void slotJustClose();
};

#endif // TEXTEDIT_H
