#ifndef STACK_H
#define STACK_H

#include <QList>
#include "deck.h"
#include "card.h"
#include <QString>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Stack:public QGraphicsRectItem{

public:
    //constructors
    //kindOfStack: STOCK, MAIN, TEMP
    Stack(Deck *pDeck, int pStartIndex, int pHowMuchCards, QString pNameOfStack, QGraphicsItem *parent=NULL);

    //public methods
    void create_stack();
    void add_cards(QList<Card*> cards);
    void remove_card(Card *card);
    int return_size();
    int return_indexOf(Card *card, int pStart);
    QString return_nameOfStack();

    //public attributes
    QList<Card*> stackOfCards;

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    //private methods



    //private attributes

    QString nameOfStack;



};

#endif // STACK_H
