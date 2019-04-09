#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "algorithm"



void tofile (string s)
{
  ofstream f("a.txt");

  f << s;
}

void tofile (int a)
{
    ofstream f("a.txt");

    f << a;
}

void tofile (char l, int a)
{
    string s = "";
    s += l;
    ofstream f(s);

    f << a;
}

void MainWindow::updateTime()
{
    time_for_move--;
    if (time_for_move == 0)
      endtime();
    QTime t;
    t.setHMS(0,time_for_move/60,time_for_move%60);
    ui->timer->setText(t.toString());
    ui->timer->setStyleSheet("QLabel { background-color : black; color : red; }");
}

void MainWindow::FillPoints(void)
{
  points.push_back(1);
  points.push_back(3);
  points.push_back(2);
  points.push_back(3);
  points.push_back(2);
  points.push_back(1);
  points.push_back(5);
  points.push_back(5);
  points.push_back(1);
  points.push_back(2);

  points.push_back(2);
  points.push_back(2);
  points.push_back(2);
  points.push_back(1);
  points.push_back(1);
  points.push_back(2);
  points.push_back(2);
  points.push_back(2);
  points.push_back(2);
  points.push_back(3);
  points.push_back(10);

  points.push_back(5);
  points.push_back(10);
  points.push_back(5);
  points.push_back(10);
  points.push_back(10);
  points.push_back(10);
  points.push_back(5);
  points.push_back(5);
  points.push_back(10);
  points.push_back(10);
  points.push_back(3);


}

bool MainWindow::PointInMoves (int x, int y)
{
  for (int i = 0; i < moves; i++)
    if (moves_log[i].xs == x && moves_log[i].ys == y)
      return true;
  return false;
}

int MainWindow::PointsCounting (void)
{
  QString temp = "";
  vector <QString> list;
  vector <Word> wd;

  for (int i = 0; i < moves; i++)
  {

    int x = moves_log[i].xs;
    int y = moves_log[i].ys;

    int left = 0;
    while (x-left!=-1&&beforeMove[x-left][y]!=' ')
      left++;
    int right = 0;
    while (x+right!=15&&beforeMove[x+right][y]!=' ')
      right++;
    int up = 0;
    while (y-up!=-1&&beforeMove[x][y-up]!=' ')
      up++;
    int down = 0;
    while (y+down!=15&&beforeMove[x][y+down]!=' ')
      down++;
    up--;
    down--;
    left--;
    right--;


    temp.clear();
    for (int j = x-left; j <= x+right; j++)
      temp+=beforeMove[j][y];
    if (temp.size() > 1 && FindWord(temp.toStdString()) == false)
      return 0;
    int noword = 0;
    if (FindWord(temp.toStdString()) == true)
    {
        bool flg = true;
        for (int q = 0; q < list.size(); q++)
          if (list[q] == temp)
            flg = false;
        if (flg == true)
        {
          list.push_back(temp);
          Word word;
          word.xb = x-left;
          word.yb = y;
          word.dirx= 1;
          word.diry= 0;
          wd.push_back(word);
        }
      noword++;
    }
    temp.clear();
    for (int j = y-up; j <= y+down; j++)
      temp += beforeMove[x][j];
    if (temp.size() > 1 && FindWord(temp.toStdString()) == false)
      return 0;
    if (FindWord(temp.toStdString()) == true)
    {
      bool flg = true;
      for (int q = 0; q < list.size(); q++)
        if (list[q] == temp)
          flg = false;
      if (flg == true)
      {
        list.push_back(temp);
        Word word;
        word.yb = y-up;
        word.xb = x;
        word.dirx= 0;
        word.diry= 1;
        wd.push_back(word);
      }
      noword++;
    }
    if (noword == 0)
        return 0;


  }

  for (int i = 0; i < list.size(); i++)
    tofile(list[i].toStdString()[0]);


  bool flag = false;
  bool flag_centr = false;
  for (unsigned long long i = 0; i < list.size(); i++)
  {
    int point_word = 0;
    int imul = 1;
    flag = false;
    flag_centr = false;
    for (int j = 0; j < list[i].size(); j++)
    {

      point_word += points[list[i].at(j).unicode()-1072];
      if (PointInMoves(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)==false)
        flag = true;
      if (wd[i].xb+wd[i].dirx*j == 7 && wd[i].yb+wd[i].diry*j == 7)
        flag_centr = true;
      if (PointInMoves(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)==true && ui->square->item(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)->backgroundColor()!=Qt::white)
      {
        if (ui->square->item(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)->backgroundColor()==Qt::blue)
            imul*=2;
        if (ui->square->item(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)->backgroundColor()==Qt::green)
            point_word += points[list[i].at(j).unicode()-1072];
        if (ui->square->item(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)->backgroundColor()==Qt::yellow)
            point_word += 2*points[list[i].at(j).unicode()-1072];
        if (ui->square->item(wd[i].xb+wd[i].dirx*j,wd[i].yb+wd[i].diry*j)->backgroundColor()==Qt::red)
            imul*=3;
      }

    }
    if (flag == false)
      return 0;
    for (int i = 0; i < PlayersPoints.size(); i++)
      if (PlayersPoints[i] != 0)
        flag_centr = true;
    if (flag_centr == false)
      return 0;
    point_word*=imul;
    int index = (now_play-1+PLAYERS)%PLAYERS;
    tofile(index);
    PlayersPoints[index]+=point_word;
    ui->scores->item(0,index)->setText(QString::number(PlayersPoints[index]));
    log += "Зачтено ";
    log += list[i];
    log += " - ";
    log += QString::number(point_word);
    log += " очков\n";
  }
  ui->log->setText(log);
  tofile(PlayersPoints[now_play]);
  return 1;
}
bool MainWindow::FindWord(string word)
{
    return binary_search(words.begin(), words.end(), word);
}
void MainWindow::CancelTransaction(void)
{
  ui->log->setText(log);
  lock_flag = false;
  res_flag = false;

  if (ui->square->rowCount() > 15)
    ui->square->removeRow(15);
  if (ui->square->columnCount() > 15)
    ui->square->removeColumn(15);


  QString temp = "";
  temp += moves_log[(int)moves].letter;
  QTableWidgetItem *item = new QTableWidgetItem(temp);
  ui->letters->setItem(0,moves_log[(int)moves].xl,item);
  moves-=0.5;


  lock_flag = true;
  res_flag = true;

}
void MainWindow::readFile(string name)
{
  ifstream f(name);
  string s;
  while (!f.eof())
  {
      f >> s;
      words.push_back(s);
  }
}
void MainWindow::result (int x, int y)
{
     cancel = 0;

   if (res_flag == true)
   {
       if (x >= SIZE || y >= SIZE )
       {
         cancel += 2;
         if (cancel == 3)
           CancelTransaction();
         return;
       }
   moves_log[(int)moves].xs = x;
   moves_log[(int)moves].ys = y;
   if (beforeMove[x][y] == ' ')
   {
       beforeMove[x][y] = ui->square->item(x,y)->text()[0];
   }
   else
   {
     QString temp = "";
     temp += beforeMove[x][y];
     QTableWidgetItem *item = new QTableWidgetItem(temp);
     res_flag = false;
     ui->square->setItem(x,y,item);
     res_flag = true;
     cancel += 2;
     if (cancel == 3)
       CancelTransaction();
     return;
   }
   moves+=0.5;
   }
}

void MainWindow::lock (int y)
{
  if (cancel != 2)
    cancel = 0;
  if (lock_flag == true)
   {
   moves_log[(int)moves].xl = y;
   moves_log[(int)moves].letter = letbefore[now_play][y];

   cancel++;
   if (cancel == 3)
     CancelTransaction();

   moves+=0.5;
   }
}

void MainWindow::MixCards()
{
    vector <Card> copy;
    srand(time(NULL));
    for (unsigned long long i = 0; i < cards.size(); i++)
      copy.push_back(cards[i]);
    cards.clear();
    unsigned long long size = copy.size();
    for (unsigned long long i = 0; i < size; i++)
    {
      unsigned long long a = rand() % copy.size();
      cards.push_back(copy[a]);
      copy.erase(copy.begin()+a);
    }
}

void MainWindow::FillingCards()
{
  Card l;

  l.cost = 1;
  l.letter = L'а';
  for (int i = 0; i < 10; i++)
    cards.push_back(l);

  l.cost = 3;
  l.letter = L'б';
  for (int i = 0; i < 3; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'в';
  for (int i = 0; i < 5; i++)
    cards.push_back(l);

  l.cost = 3;
  l.letter = L'г';
  for (int i = 0; i < 3; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'д';
  for (int i = 0; i < 5; i++)
    cards.push_back(l);

  l.cost = 1;
  l.letter = L'е';
  for (int i = 0; i < 9; i++)
    cards.push_back(l);

  l.cost = 5;
  l.letter = L'ж';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);

  l.cost = 5;
  l.letter = L'з';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);

  l.cost = 1;
  l.letter = L'и';
  for (int i = 0; i < 8; i++)
    cards.push_back(l);

  l.cost = 4;
  l.letter = L'й';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);


  l.cost = 2;
  l.letter = L'к';
  for (int i = 0; i < 6; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'л';
  for (int i = 0; i < 4; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'м';
  for (int i = 0; i < 5; i++)
    cards.push_back(l);

  l.cost = 1;
  l.letter = L'н';
  for (int i = 0; i < 8; i++)
    cards.push_back(l);

  l.cost = 1;
  l.letter = L'о';
  for (int i = 0; i < 10; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'п';
  for (int i = 0; i < 6; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'р';
  for (int i = 0; i < 6; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'с';
  for (int i = 0; i < 6; i++)
    cards.push_back(l);

  l.cost = 2;
  l.letter = L'т';
  for (int i = 0; i < 5; i++)
    cards.push_back(l);

  l.cost = 3;
  l.letter = L'у';
  for (int i = 0; i < 3; i++)
    cards.push_back(l);

  l.cost = 10;
  l.letter = L'ф';
  for (int i = 0; i < 1; i++)
    cards.push_back(l);

  l.cost = 5;
  l.letter = L'х';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);

  l.cost = 10;
  l.letter = L'ц';
  cards.push_back(l);

  l.cost = 5;
  l.letter = L'ч';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);


  l.cost = 10;
  l.letter = L'ш';
  cards.push_back(l);

  l.cost = 10;
  l.letter = L'щ';
  cards.push_back(l);

  l.cost = 10;
  l.letter = L'ъ';
  cards.push_back(l);

  l.cost = 5;
  l.letter = L'ы';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);

  l.cost = 5;
  l.letter = L'ь';
  for (int i = 0; i < 2; i++)
    cards.push_back(l);

  l.cost = 10;
  l.letter = L'э';
  cards.push_back(l);

  l.cost = 10;
  l.letter = L'ю';
  cards.push_back(l);

  l.cost = 3;
  l.letter = L'я';
  for (int i = 0; i < 3; i++)
    cards.push_back(l);

}

void MainWindow::endchange()
{
    ui->square->show();
    ui->cancelMove->show();
    ui->log->show();
    ui->change->show();
    ui->endMove->show();
    ui->label->hide();
    ui->rubbish->hide();
    ui->end_hide->hide();
    moves = 0;
    newmove();


}
void MainWindow::changecards()
{
    ui->square->hide();
    ui->cancelMove->hide();
    ui->log->hide();
    ui->change->hide();
    ui->endMove->hide();
    ui->label->show();
    ui->rubbish->show();
    ui->end_hide->show();
    rub_flag = true;
    cancelmove();
}
void MainWindow::Colour()
{
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
    {
      if ((i==0 && (j==0 || j==7 || j==14)) || (i==7 && (j==0 || j==14)) || (i==14 && (j==0 || j==7 || j==14)) )
        ui->square->item(i,j)->setBackgroundColor(Qt::red);
      if ((i==1 && (j==5 || j==9)) || (i==13 && (j==5 || j==9)) || (i==5 && (j==1 || j==13)) || (i==9 && (j==1 || j==13)) )
        ui->square->item(i,j)->setBackgroundColor(Qt::yellow);
      if ((i == j || i == 14-j) && ((i >= 1 && i<=4)||(i>=10 && i <= 13)) )
        ui->square->item(i,j)->setBackgroundColor(Qt::blue);
      if ((i == 0 && j == 3) || (i == 3 && j == 0) || (i == 0 && j == 11) || (i == 11 && j == 0) || (i == 14 && j == 3)
              || (i == 3 && j == 14) || (i == 14 && j == 11) || (i == 11 && j == 14) || (i == 3 && j == 7) || (i == 7 && j == 3)
              || (i == 6 && j == 2) || (i == 8 && j == 2) || (i == 2 && j == 6) || (i == 2 && j == 8) || (i == 11 && j == 7)
              || (i == 7 && j == 11) || (i == 12 && j == 6) || (i == 12 && j == 8) || (i == 6 && j == 12) || (i == 8 && j == 12)
              || (i == 6 && j == 8) || (i == 8 && j == 6) || (i == 6 && j == 6) || (i == 8 && j == 8))
        ui->square->item(i,j)->setBackgroundColor(Qt::green);
    }
}
void MainWindow::setPresets()
{
    log = "NewGame started!\n";
    ui->rubbish->hide();
    ui->end_hide->hide();
    ui->label->hide();
    ui->rubbish->setColumnWidth(0,50);
    ui->rubbish->setRowHeight(0,50);

    ui->scores->setRowCount(1);
    ui->scores->setColumnCount(PLAYERS);
    ui->scores->setFixedSize(PLAYERS*40+2,22);
    for (int i = 0; i < ui->scores->rowCount(); i++)
      ui->scores->setRowHeight(i,20);
    for (int i = 0; i < ui->scores->columnCount(); i++)
      ui->scores->setColumnWidth(i,20);


    for (int i = 0; i < ui->scores->columnCount(); i++)
      for (int j = 0; j < ui->scores->rowCount(); j++)
    {
        QString s = "0";
        QTableWidgetItem *item = new QTableWidgetItem(s);
        item->setFlags(item->flags() & Qt::ItemIsDropEnabled & ~Qt::ItemIsSelectable);
        ui->scores->setItem(j,i,item);
    }


    for (int i = 0; i < SIZE; i++)
    {
      ui->square->setColumnWidth(i,HOR);
      ui->square->setRowHeight(i,VERT);
    }


    ui->letters->setRowHeight(0,HOR);
    for (int i = 0; i < LETTERS_NUM; i++)
    {
      ui->letters->setColumnWidth(i,VERT);
    }

    srand(time(NULL));

    MixCards();
    FillPoints();
    PlayersPoints.clear();
    for (int i = 0; i < PLAYERS; i++)
      PlayersPoints.push_back(0);
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        beforeMove[i][j] = ' ';

    moves=0;
    count_c = 0;
    now_play = 0;
    res_flag = false;
    for (int i = 0; i < PLAYERS; i++)
      for (int j = 0; j < LETTERS_NUM; j++)
      {
        letbefore[i][j] = cards[count_c].letter;
        count_c++;
      }

    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
    {
          ui->square->item(i,j)->setText("");
    }
    int cnt;
    while (1)
    {
      cnt = rand()%50000;
     if (words[cnt].size() == 2*LCENT)
      {
        tofile(words[cnt]);
        break;
      }
    }
    QString wrd;
    wrd = QString::fromStdString(words[cnt]);
    for (int i = 0; i < wrd.size(); i++)
    {
      ui->square->item(7,4+i)->setText(wrd.at(i));
      beforeMove[7][4+i] = wrd.at(i);
    }



    lock_flag = true;
    res_flag = true;


    newmove();
}
void MainWindow::cancelmove()
{
  lock_flag = false;
  res_flag = false;

  for (int i = 0; i < (int)moves; i++)
  {
      QTableWidgetItem *clear = new QTableWidgetItem("");
      QString temp = "";
      temp += moves_log[i].letter;
      QTableWidgetItem *item = new QTableWidgetItem(temp);
      ui->letters->setItem(0,moves_log[i].xl,item);
      ui->square->setItem(moves_log[i].xs,moves_log[i].ys, clear);
      beforeMove[moves_log[i].xs][moves_log[i].ys] = ' ';
      letbefore[now_play][moves_log[i].xl] = moves_log[i].letter;
      Colour();
  }
  lock_flag = true;
  res_flag = true;
  moves = 0;
}

void MainWindow::clean()
{
  if (rub_flag == true)
  {
      rub_flag = false;
      QTableWidgetItem *item = new QTableWidgetItem("");
      ui->rubbish->setItem(0,0,item);
      rub_flag = true;
  }
}

void MainWindow::newmove()
{
 if (moves > 0)
 if (PointsCounting() == 0)
 {
   cancelmove();
   return;
 }
 lock_flag = false;
 for (int i = 0; i < LETTERS_NUM; i++)

    if (ui->letters->item(0,i)->text() == "")
    {
      letbefore[now_play][i] = cards.at(count_c).letter;
      count_c++;
    }
 now_play++;
 log += "Ходит игрок ";
 log += QString::number(now_play);
 log += '\n';
 ui->log->setText(log);
 if (now_play == PLAYERS)
   now_play = 0;
 for (int i = 0; i < LETTERS_NUM; i++)
     {
         QTableWidgetItem *zero = new QTableWidgetItem(letbefore[now_play][i]);
         zero->setFlags(zero->flags() & ~Qt::ItemIsEditable);


         ui->letters->setItem(0,i,zero);
     }

  lock_flag = true;
  moves = 0;
  time_for_move = LIMIT;


}

void MainWindow::endtime (void)
{
 //
  cancelmove();
  newmove();
}

void MainWindow::newgame (void)
{
  PLAYERS = ui->numPlayers->currentText().toInt();
  tofile(PLAYERS);
  setPresets();
}

void MainWindow::timer (void)
{
    time_for_move = LIMIT;
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setlocale(LC_ALL, "ru_RU.utf8");
    ui->setupUi(this);

    PLAYERS = 2;
    readFile("/home/ivan/Documents/Erudit_game/Erudit/voc.txt");
    FillingCards();

    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
    {

      QString s = "";
      QTableWidgetItem *item = new QTableWidgetItem(s);
      item->setFlags(item->flags() & Qt::ItemIsDropEnabled & ~Qt::ItemIsSelectable);
      ui->square->setItem(i,j,item);

    }
    setPresets();
    Colour();
    timer();


    connect(ui->letters,SIGNAL(cellChanged(int,int)), this,SLOT(lock(int, int)));
    connect(ui->square,SIGNAL(cellChanged(int,int)),this,SLOT(result(int,int)));
    connect(ui->endMove,SIGNAL(clicked()),this,SLOT(newmove()));   
    connect(ui->cancelMove,SIGNAL(clicked()), this,SLOT(cancelmove()));
    connect(ui->change,SIGNAL(clicked()),this,SLOT(changecards()));
    connect(ui->end_hide,SIGNAL(clicked()), this,SLOT(endchange()));
    connect(ui->rubbish,SIGNAL(cellChanged(int,int)),this,SLOT(clean()));
    connect(ui->newGame,SIGNAL(clicked()),this,SLOT(newgame()));
}

MainWindow::~MainWindow()
{

    delete ui;
}
