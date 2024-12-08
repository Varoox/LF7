/*
 Datei : frmmain.cpp
 Inhalt: Formular für Bank (Thema Arrays)
 Autor : Armin Honig
 Datum : 2024-01-29
*/

#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);

   // tester(); //wird einmalig beim Erzeugen des Formulars aufgerufen!
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::sortierenNachKontonummer()
{
    //Sortieren nach Kontonummer
    //einfacher Bubble-Sort
    int anz = kontonummer.size();
    for (int x = 0; x < anz-1; x++)
    {
        for (int i = 0; i < anz-1-x; i++)
        {
            if (kontonummer[i] > kontonummer[i+1])
            {
                kontonummer.move(i,i+1);
                nachname.move(i,i+1);
                vorname.move(i,i+1);
                kontostand.move(i,i+1);
            } //if
        } //for i
    } //for x
}

void FrmMain::sortierenNachName()
{
    // Sortieren nach Nachname und dann Vorname
    // Einfacher Bubble-Sort
    int anz = kontonummer.size();
    for (int x = 0; x < anz - 1; x++)
    {
        for (int i = 0; i < anz - 1 - x; i++)
        {
            // Vergleiche zuerst die Nachnamen
            if (nachname[i] > nachname[i + 1] ||
                (nachname[i] == nachname[i + 1] && vorname[i] > vorname[i + 1]))
            {
                kontonummer.move(i, i + 1);
                nachname.move(i, i + 1);
                vorname.move(i, i + 1);
                kontostand.move(i, i + 1);
            }
        }
    }
}

void FrmMain::on_btnAnlegen_clicked()
{
    // Ausgabe leeren
    ui->lwAnzeige->clear();
    bool ok = true;

    // Eingaben in lokale Variablen speichern und prüfen ob Kontonummer int ist
    int eingabeKontonummer = ui->leKontonummer->text().toInt(&ok);
    if (!ok) {
        ui->lwAnzeige->addItem("Ungültige Konto-Nr.!");
        return;
    }


    QString eingabeVorname = ui->leVorname->text();
    QString eingabeNachname = ui->leNachname->text();

    // Überprüfe auf Zahlen in Vor- und Nachname
    for (int i = 0; i < eingabeVorname.length(); ++i) {
        if (eingabeVorname[i].isDigit()) {
            ui->lwAnzeige->addItem("Ungültiger Vorname! Der Name darf keine Zahlen enthalten.");
            return;
        }
    }

    for (int i = 0; i < eingabeNachname.length(); ++i) {
        if (eingabeNachname[i].isDigit()) {
            ui->lwAnzeige->addItem("Ungültiger Nachname! Der Name darf keine Zahlen enthalten.");
            return;
        }
    }

    // Eingabe Kontostand auf Double chekcen und sicherstellen das Kontostand nicht negativ ist
    double eingabeKontostand = ui->leKontostand->text().toDouble(&ok);
    if (!ok || eingabeKontostand < 0) {
        ui->lwAnzeige->addItem("Ungültiger Kontostand! Muss eine positive Zahl sein.");
        return;
    }

    // Überprüfe, ob Eingaben nicht leer sind
    if (ui->leKontonummer->text().isEmpty() ||
        eingabeVorname.isEmpty() ||
        eingabeNachname.isEmpty() ||
        ui->leKontostand->text().isEmpty())
    {
        ui->lwAnzeige->addItem("Alle Felder müssen ausgefüllt werden!");
        return;
    }

    // Check ob Kontonummer schon existiert
    if(istDoppelt(kontonummer,eingabeKontonummer) == true) {
        ui->lwAnzeige->addItem("Die Konto-Nr. existiert bereits!");
        return;
    }

    // Benutzerkontodetails der Liste hinzufügen
    kontonummer.append(eingabeKontonummer);
    vorname.append(eingabeVorname);
    nachname.append(eingabeNachname);
    kontostand.append(eingabeKontostand);

    ui->lwAnzeige->addItem("Konto erfolgreich angelegt.");
}

bool FrmMain::istDoppelt(const QList<int>& liste, int wert)
{
    // Durchläuft die Liste und überprüft jedes Element
    for (int element : liste)
    {
        if (element == wert)
        {
            // Wenn das Element gleich dem gesuchten Wert ist, wird true zurückgegeben
            // (Der Wert ist in der Liste vorhanden)
            return true;
        }
    }
    // Wenn der Wert nicht gefunden wurde, wird false zurückgegeben
    return false;
}

bool FrmMain::ausgabeKonten()
{
    int anz = kontonummer.size(); // Ermittelt die Anzahl der Konten
    QString text;
    if (anz >= 1) {
        // Durchläuft die Liste der Konten und stellt sie dar
        for(int i = 0; i < anz; i++)
        {
            // Erstellt einen String, der die Kontoinformationen enthält
            text = "Konto-Nr.:" + QString::number(kontonummer[i]) + " Kontostand: " + QString::number(kontostand[i],'f',2);
            text += "€ Name: " + vorname[i] + " " + nachname[i];
            // Fügt den erstellten String zur Anzeige im List Widget hinzu
            ui->lwAnzeige->addItem(text);
        }
        return true; // Gibt zurück, dass Konten erfolgreich ausgegeben wurden
    }
    return false; // Gibt zurück, dass keine Konten ausgegeben wurden
}

void FrmMain::on_btnUeberweisen_clicked()
{
    ui->lwAnzeige->clear(); // Löscht die bisherige Anzeige im List Widget

    // Liest die Kontonummern von Absender und Empfänger sowie den Überweisungsbetrag aus den Eingabefeldern
    int absenderkonto = ui->leAbsenderKonto->text().toInt();
    int empfaengerkonto = ui->leEmpfaengerKonto->text().toInt();
    double ueberweisungsbetrag = ui->leUeberweisungsbetrag->text().toDouble();

    // Ermittelt die Indizes der Kontonummern von Absender und Empfänger
    int indexAbsender = getIndexFromKontonummer(absenderkonto);
    int indexEmpfaenger = getIndexFromKontonummer(empfaengerkonto);

    // Überprüft, ob die Kontonummern existieren und ob sie unterschiedlich sind
    if (indexAbsender == -1 || indexEmpfaenger == -1)
    {
        ui->lwAnzeige->addItem("Ein oder beide Konten existieren nicht!");
        return;
    }

    if(indexAbsender == indexEmpfaenger)
    {
        ui->lwAnzeige->addItem("Du darfst dir nicht selber Geld überweisen!");
        return;
    }

    // Überprüft, ob der Überweisungsbetrag gültig ist (muss größer als 0 sein)
    if (ueberweisungsbetrag <= 0){
        ui->lwAnzeige->addItem("Der Betrag muss größer als 0 sein!");
        return;
    }

    // Führt die Überweisung durch, wenn genügend Guthaben vorhanden ist
    if (kontostand.at(indexAbsender) >= ueberweisungsbetrag)
    {
        kontostand[indexAbsender] -= ueberweisungsbetrag;
        kontostand[indexEmpfaenger] += ueberweisungsbetrag;
        ui->lwAnzeige->addItem("Überweisung erfolgreich!");
    }
    else
    {
        ui->lwAnzeige->addItem("Nicht genügend Guthaben auf dem Absenderkonto!");
    }
}

void FrmMain::on_comboBox_activated(int index)
{
    ui->lwAnzeige->clear(); // Löscht die bisherige Anzeige im List Widget

    // Prüft, welcher Eintrag im ComboBox ausgewählt wurde
    if (index == 0) {
        sortierenNachKontonummer(); // Sortiert die Konten nach Kontonummer
        if (!ausgabeKonten()) {
        // Zeigt eine Nachricht an, wenn keine Konten zum Anzeigen vorhanden sind
        ui->lwAnzeige->addItem("Es müssen erst Konten angelegt werden...");
        }
    }
    if (index == 1) {
        sortierenNachName(); // Sortiert die Konten nach Name
        if (!ausgabeKonten()) {
        // Zeigt eine Nachricht an, wenn keine Konten zum Anzeigen vorhanden sind
        ui->lwAnzeige->addItem("Es müssen erst Konten angelegt werden...");
        }
    }
}

int FrmMain::getIndexFromKontonummer(int konto)
{
    // Ermittelt die Länge der Liste der Kontonummern
    int laengeKontonummerArray = kontonummer.size();

    // Durchläuft die Liste der Kontonummern
    for (int i = 0; i < laengeKontonummerArray; i++) {
        // Vergleicht jede Kontonummer mit der gesuchten Kontonummer
        if (konto == kontonummer[i])
        {
            // Gibt den Index der gefundenen Kontonummer zurück
            return i;
        }
    }
    // Gibt -1 zurück, wenn die Kontonummer nicht gefunden wurde
    return -1;
}

void FrmMain::on_btnAuszahlung_clicked()
{
    ui->lwAnzeige->clear(); // Löscht die bisherige Anzeige im List Widget

    // Liest die Kontonummer und den Auszahlungsbetrag aus den Eingabefeldern
    int auszahlkonto = ui->leKontonummerEinAusZahlen->text().toInt();
    int indexKontonummer = getIndexFromKontonummer(auszahlkonto);
    double betragAuszahlen = ui->leBetragEinAusZahlen->text().toDouble();

    // Überprüft, ob der Auszahlungsbetrag gültig ist (muss größer als 0 sein)
    if (betragAuszahlen <= 0){
        ui->lwAnzeige->addItem("Der Betrag muss größer als 0 sein!");
        return;
    }

    // Überprüft, ob die eingegebene Kontonummer existiert
    if(indexKontonummer == -1)
    {
        ui->lwAnzeige->addItem("Das angegebene Konto exestiert nicht!");
    } else {
        // Führt die Auszahlung durch: Subtrahiert den Betrag vom Kontostand
        // Überprüft, ob genügend Guthaben vorhanden ist
        if (kontostand.at(indexKontonummer) >= betragAuszahlen)
        {
            kontostand[indexKontonummer] -= betragAuszahlen;
            ui->lwAnzeige->addItem(QString::number(betragAuszahlen,'f', 2) + "€ wurden erfolgreich ausgezahlt!");
        }
        else {
            ui->lwAnzeige->addItem("Nicht genügend Geld auf dem Konto!");
        }
    }
}

void FrmMain::on_btnEinzahlung_clicked()
{
    ui->lwAnzeige->clear(); // Löscht die bisherige Anzeige im List Widget

    // Liest die Kontonummer und den Einzahlungsbetrag aus den Eingabefeldern
    int einzahlkonto = ui->leKontonummerEinAusZahlen->text().toInt();
    int indexKontonummer = getIndexFromKontonummer(einzahlkonto);
    double betragEinzahlen = ui->leBetragEinAusZahlen->text().toDouble();

    // Überprüft, ob der Einzahlungsbetrag gültig ist (muss größer als 0 sein)
    if (betragEinzahlen <= 0){
        ui->lwAnzeige->addItem("Der Betrag muss größer als 0 sein!");
        return;
    }

    // Überprüft, ob die eingegebene Kontonummer existiert
    if(indexKontonummer == -1)
    {
        ui->lwAnzeige->addItem("Das angegebene Konto exestiert nicht!");
    } else {
        // Führt die Einzahlung durch: Addiert den Betrag zum Kontostand
        kontostand[indexKontonummer] += betragEinzahlen;

        // Zeigt Erfolgsmeldung und den aktuellen Kontostand an
        ui->lwAnzeige->addItem(QString::number(betragEinzahlen, 'f', 2) + "€ wurden erfolgreich Eingezahlt!");
        ui->lwAnzeige->addItem("Der Aktuelle Kontostand beträgt: " + QString::number(kontostand.at(indexKontonummer)));
    }
}
