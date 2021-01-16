#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QPoint>
#include <QFileDialog>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int **zycie = nullptr;
    int wiersze =20;
    int kolumny =20;
    int Img_Height;
    int Img_Width ;
    int kratki_start;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QImage* plansza;


public slots:
    void on_btn_randomStart_clicked();

    void on_btn_nastepnyKrok_clicked();

    void on_btn_wyczysc_clicked();

    int l_zyjacych_obok(int, int);

    void dlugosc_zycia();

    int get_wiersz(){return wiersze; }
    int get_kolumna(){return kolumny; }

    void zapis(int wartosc,int i_wiersz, int i_kolumna);
    int odczyt( int i_wiersz, int i_kolumna);

private slots:
    void on_btn_ustawRozmiar_clicked();

    void on_btn_kratki_start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
