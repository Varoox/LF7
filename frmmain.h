/*
 Datei : frmmain.h
 Inhalt: Formular für Bank (Thema Arrays)
 Autor : Armin Honig
 Datum : 2024-01-29
*/

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>

namespace Ui {
class FrmMain;
}

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private slots:
    void on_btnAnlegen_clicked();

    void on_btnUeberweisen_clicked();

    void on_comboBox_activated(int index);

    void on_btnAuszahlung_clicked();

    void on_btnEinzahlung_clicked();

private:
    Ui::FrmMain *ui;
    QList<int>kontonummer;
    QList<QString>nachname;
    QList<QString>vorname;
    QList<double>kontostand;

    void sortierenNachKontonummer();
    void sortierenNachName();

    bool ausgabeKonten();
    bool istDoppelt(const QList<QString>& liste, const QString& wert);
    bool istDoppelt(const QList<int>& liste, int wert);

    int getIndexFromKontonummer(int kontonummer);
};

#endif // FRMMAIN_H
