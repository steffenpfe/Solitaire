#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QPixmap>
#include <QString>
#include <QGraphicsItem>


class Card: public QGraphicsPixmapItem{
public:
    //constructors
    Card(int pRank, int pSymbol, int pColor, QGraphicsItem *parent=NULL);

    //getters
    int get_rank();
    int get_symbol();
    int get_color();
    bool get_isPlaced();
    QString get_whichStack();
    QString get_filename();
    bool get_frontOfCard();

    //setters
    void change_front(); //by default you just see the back of the card
    void set_isPlaced(bool p);
    void set_whichStackC(QString pWhichStack);
    void set_frontOfCard(bool b);


    //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);



private:
    //private functions
    void set_filename();

    //private attributes
    int rankOfCard; //0-12
    int symbolOfCard; //0Hearts, 1Diamonds (red), 2Spades ,3Clubs (black)
    int colorOfCard; // 0'R' = red, 1'B' = black

    QString filename;
    bool frontOfCard;
    QString filenameBackOfCard;
    bool isPlaced;
    QString whichStack;




};

#endif // CARD_H
