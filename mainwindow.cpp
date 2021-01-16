#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Img_Height = ui->lbl_gra->height();
    Img_Width = ui->lbl_gra->width();

        zycie=new int*[wiersze];

        for ( int i=0; i<wiersze; i++)
        {
            zycie[i]=new int[kolumny]{0};
        }
kratki_start=(wiersze*kolumny)/5;

    plansza = new QImage(20, 20, QImage::Format_ARGB32);
    MainWindow::on_btn_wyczysc_clicked();
}

MainWindow::~MainWindow()
{
    if(zycie != nullptr){
        for (int i=0;i<wiersze;i++) {
            delete [] zycie[i];
        }
        delete [] zycie;
    }
    zycie = nullptr;
    delete ui;
}

void MainWindow::on_btn_wyczysc_clicked()
{
    for (int i =0;i<wiersze;i++) {
        for (int j=0;j<kolumny;j++)
        {
        zycie[i][j]=0;
        }
    }
    plansza->fill(QColor(255,255,255));

    ui->lbl_gra->setPixmap(QPixmap::fromImage(plansza->scaled(Img_Width,Img_Height)));
}

void MainWindow::on_btn_randomStart_clicked()
{
    MainWindow::on_btn_wyczysc_clicked();

        std::random_device rd;
        int rand_wiersz;
        int rand_kolumna;

        QBrush red_p(QColor::fromRgb(255,0,0));
        QPainter pedzel(plansza);
        pedzel.setPen(QColor::fromRgb(255,0,0));

        for (int i = 0; i < kratki_start; i++)
        {
            rand_wiersz=(rd()%wiersze);
            rand_kolumna =(rd()%kolumny);
            zycie[rand_wiersz][rand_kolumna]=1;
        }

        for (int i=0;i<wiersze;i++) {
            for (int j=0;j<kolumny;j++) {
                if(zycie[i][j]==1)            pedzel.fillRect(j, i, 1, 1, red_p);
            }
        }

        pedzel.end();
        ui->lbl_gra->setPixmap(QPixmap::fromImage(plansza->scaled(Img_Width,Img_Height)));
}

void MainWindow::on_btn_ustawRozmiar_clicked()
{
    int nowyWie = ui->l_wierszy->value();
    int nowyKol = ui->l_kolumn->value();
    kratki_start=(nowyWie*nowyKol)/5;
    plansza->fill(QColor(255,255,255));
    if(zycie!=nullptr)
    {

    plansza = new QImage(nowyKol, nowyWie, QImage::Format_ARGB32);

        int **temp = new int*[nowyWie];
        for (int i = 0; i< nowyWie; i++) {
            temp[i]=new int[nowyKol];
        }
        for (int i=0;i<wiersze;i++) {
            delete [] zycie[i];
        }
        delete []  zycie;

        zycie = temp;

        temp=nullptr;
        wiersze = nowyWie;
        kolumny = nowyKol;
    }
    ui->lbl_gra->setPixmap(QPixmap::fromImage(plansza->scaled(Img_Width,Img_Height)));
}

void MainWindow::on_btn_kratki_start_clicked()
{
    kratki_start = ui->l_kratek->value();
}

void MainWindow::zapis(int wartosc, int i_wiersz, int i_kolumna)
{
    if(zycie != nullptr && i_wiersz <= wiersze && i_kolumna <=kolumny)
    {
        zycie[i_wiersz][i_kolumna]=wartosc;
    }
}

int MainWindow::odczyt(int i_wiersz, int i_kolumna)
{
    if(zycie != nullptr && i_wiersz <= wiersze && i_kolumna <=kolumny)
    {
        return zycie[i_wiersz][i_kolumna];
    }
return 0;
}

