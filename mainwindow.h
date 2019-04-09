#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <vector>
#include <fstream>
#include <QThread>
#include <QTimer>
#include <QTime>


//#define PLAYERS 2
#define SIZE 15
#define LETTERS_NUM 7
#define HOR 20
#define VERT 20
#define LCENT 7
#define LIMIT 120


using namespace std;

namespace Ui {
class MainWindow;
}

struct Card
{
    int cost;
    QChar letter;
};

struct Drag
{
    int xs, ys;
    int xl;
    QChar letter;
};

struct Word
{
    int xb, yb, dirx, diry;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

    int PLAYERS;
    QChar beforeMove[SIZE][SIZE]; // хранит элементы игрового поля
    QChar letbefore[4][LETTERS_NUM]; // хранит фишки игроков
    double moves;
    Drag moves_log[LETTERS_NUM];// хранит данные о перемещениях
    bool lock_flag;
    vector <string> words; // словарь
    bool res_flag;
    bool rub_flag;
    int count_c;
    short cancel;
    vector <Card> cards; // набор фишек
    vector <int> points;
    int now_play;
    vector <int> PlayersPoints; // очки игроков
    int time_for_move;
    QString log = ""; //вывод информации


     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void FillingCards (void);  //фишки
    void MixCards (void);   //
    void CancelTransaction(void);
    void setPresets(void);
    void Colour (void);
    void readFile(string name);
    bool FindWord(string word);
    int PointsCounting(void);
    void FillPoints (void);
    bool PointInMoves (int x, int y);
    void timer (void);


public slots :
    void result (int x, int y);
    void lock  (int y);
    void newmove();
    void cancelmove();
    void changecards();
    void endchange();
    void clean();
    void endtime();
    void newgame (void);

private slots:
    void updateTime();

private:
    Ui::MainWindow *ui;
   QTimer *tmr;
};

#endif // MAINWINDOW_H
