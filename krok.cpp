#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>

int MainWindow::l_zyjacych_obok(int i_wiersz, int i_kolumna)
{
    int licznik=0;
   if(i_wiersz!=0 && i_wiersz != wiersze-1 && i_kolumna!=0 && i_kolumna!= kolumny-1)
    {
        if(zycie[i_wiersz-1][i_kolumna-1]>=2)licznik++;
        if(zycie[i_wiersz-1][i_kolumna]  >=2)licznik++;
        if(zycie[i_wiersz-1][i_kolumna+1]>=2)licznik++;
        if(zycie[i_wiersz][i_kolumna-1]  >=2)licznik++;
        if(zycie[i_wiersz][i_kolumna+1]  >=2)licznik++;
        if(zycie[i_wiersz+1][i_kolumna-1]>=2)licznik++;
        if(zycie[i_wiersz+1][i_kolumna]  >=2)licznik++;
        if(zycie[i_wiersz+1][i_kolumna+1]>=2)licznik++;
    } 

    else if(i_wiersz==0)
    {
        if(i_kolumna ==0)
        {
            if(zycie[0][1]>=2)licznik++;
            if(zycie[1][0]>=2)licznik++;
            if(zycie[1][1]>=2)licznik++;
        }
        else if(i_kolumna == kolumny-1)
        {
            if(zycie[0][i_kolumna-1]>=2)licznik++;
            if(zycie[1][i_kolumna]>=2)licznik++;
            if(zycie[1][i_kolumna-1]>=2)licznik++;
        }
        else {

            for(int row=i_wiersz; row<=i_wiersz+1;row++)
            {
                for(int col = i_kolumna-1; col<=i_kolumna+1; col++)
                {
                    if(zycie[row][col] >= 2 && row!=i_wiersz && col!=i_kolumna)licznik++;
                }
            }
        }
    }
    else if(i_wiersz==wiersze-1)
    {
        if(i_kolumna == kolumny-1)
        {
            if(zycie[i_wiersz][i_kolumna-1]>=2)licznik++;
            if(zycie[i_wiersz-1][i_kolumna]>=2)licznik++;
            if(zycie[i_wiersz-1][i_kolumna-1]>=2)licznik++;
        }
        else if(i_kolumna == 0)
        {
            if(zycie[i_wiersz][i_kolumna+1]>=2)licznik++;
            if(zycie[i_wiersz-1][i_kolumna]>=2)licznik++;
            if(zycie[i_wiersz-1][i_kolumna+1]>=2)licznik++;
        }
        else {
            for(int row=i_wiersz-1; row<=i_wiersz;row++)
            {
                for(int col = i_kolumna-1; col<=i_kolumna+1; col++)
                {
                     if(zycie[row][col] >= 2 && row!=i_wiersz && col!=i_kolumna)licznik++;
                }
            }
        }
    }
    else if(i_kolumna==0 && i_wiersz!=0 && i_wiersz!=wiersze-1)
    {
        for(int row=i_wiersz-1; row<=i_wiersz+1;row++)
        {
            for(int col = i_kolumna; col<=i_kolumna+1; col++)
            {
                if(zycie[row][col]>= 2 && row!=i_wiersz && col!=i_kolumna)licznik++;
            }
        }
    }
    else if(i_kolumna==19 && i_wiersz!=0 && i_wiersz!=wiersze-1)
    {
        for(int row=i_wiersz-1; row<=i_wiersz+1;row++)
        {
            for(int col = i_kolumna-1; col<=i_kolumna; col++)
            {
                if(zycie[row][col]>= 2 && row!=i_wiersz && col!=i_kolumna)licznik++;
            }
        }
    }
    return licznik;
}

void MainWindow::dlugosc_zycia()
{

    for (int i=0;i<wiersze;i++) {
        for (int j=0;j<kolumny;j++) {
            if(zycie[i][j]>=1) zycie[i][j]++;
            else if(zycie[i][j]==(-1))zycie[i][j]=0;
        }
    }
}



void MainWindow::on_btn_nastepnyKrok_clicked()
{
    plansza->fill(QColor(255,255,255));

    QBrush red_p(QColor::fromRgb(255,0,0));
    QBrush yellow_p(QColor::fromRgb(255,255,0));
    QBrush green_p(QColor::fromRgb(0,255,0));
    QBrush aqua_p(QColor::fromRgb(0,255,255));
    QBrush blue_p(QColor::fromRgb(0,0,255));

       int l_krokow=ui->l_krokow->value();
  for (int k=0;k<l_krokow;k++) {

    QPainter pedzel(plansza);
     pedzel.setPen(QColor::fromRgb(255,0,0));
        int l_zyjacych=0;
        dlugosc_zycia();

     for (int row=0;row<wiersze;row++)
     {
         for (int col=0;col<kolumny;col++)
         {
             l_zyjacych=l_zyjacych_obok(row, col);
             if(zycie[row][col]==0)
             {

                if(l_zyjacych == 3)
                {
                    zycie[row][col]=1;

                pedzel.fillRect(col, row, 1, 1, red_p);
                }
             }
             else
             {
                 if(l_zyjacych != 3 && l_zyjacych !=2)zycie[row][col]=(-1);

                 else {
                     if(zycie[row][col]==2)
                     pedzel.fillRect((col), (row), 1, 1, yellow_p);
                     else if (zycie[row][col]==3)
                        pedzel.fillRect((col), (row), 1, 1, green_p);
                     else if (zycie[row][col]==4)
                         pedzel.fillRect((col), (row), 1, 1, aqua_p);
                     else if (zycie[row][col]>=5)
                     pedzel.fillRect((col), (row), 1, 1, blue_p);
                     }
                 }
             }
         }
      pedzel.end();
      ui->lbl_gra->setPixmap(QPixmap::fromImage(plansza->scaled(Img_Width,Img_Height)));
       // Sleep(CLOCKS_PER_SEC);
    }
}
