#include "stack.h"
#include <QPen>
#include <QDebug>
#include <QString>
#include <QBrush>
#include "game.h"

extern Game *game;


Stack::Stack(Deck *pDeck, int pStartIndex, int pHowMuchCards, QString pNameOfStack, QGraphicsItem *parent):
    nameOfStack(pNameOfStack), QGraphicsRectItem(parent){

    for(int i=pStartIndex; i<pStartIndex+pHowMuchCards; i++){
        stackOfCards.append(pDeck->get_card(i));
    }
    for(int i=0; i<stackOfCards.size(); i++){
        stackOfCards[i]->set_whichStackC(nameOfStack);
        stackOfCards[i]->setParentItem(this);

        if(nameOfStack != QString("STOCK1")){
            if(i<stackOfCards.size()-1){
                stackOfCards[i]->set_frontOfCard(false);
                stackOfCards[i]->change_front();
            }
        }
        else{//STOCK1 Stapel immer alle zudecken!!
            if(i<stackOfCards.size()){
                stackOfCards[i]->set_frontOfCard(false);
                stackOfCards[i]->change_front();
            }
        }



    }


    setRect(0,0,70,95);
    setPen(QPen(Qt::DotLine));
    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);
    //brush.setColor(Qt::transparent);
    setBrush(brush);
    create_stack();

}

void Stack::create_stack(){

    if(nameOfStack == QString("TEMP1") || nameOfStack == QString("TEMP2") ||
       nameOfStack == QString("TEMP3") || nameOfStack == QString("TEMP4") ||
       nameOfStack == QString("TEMP5") || nameOfStack == QString("TEMP6") ||
       nameOfStack == QString("TEMP7")){
        for(int i=0; i<stackOfCards.size(); i++){
            stackOfCards[i]->setParentItem(this);
            stackOfCards[i]->setPos(0,30*i);
        }
    }
    else if(nameOfStack == QString("MAIN1") || nameOfStack == QString("MAIN2") ||
            nameOfStack == QString("MAIN3") || nameOfStack == QString("MAIN4")){
        for(int i=0; i<stackOfCards.size(); i++){
            stackOfCards[i]->setParentItem(this);
            stackOfCards[i]->setPos(0,0);
        }
    }
    else if(nameOfStack == QString("STOCK1")){
        for(int i=0; i<stackOfCards.size(); i++){
            stackOfCards[i]->setParentItem(this);
            stackOfCards[i]->setPos(5*i,0);
        }
    }
    else if(nameOfStack == QString("STOCK2")){
        for(int i=0; i<stackOfCards.size(); i++){
            stackOfCards[i]->setParentItem(this);
            stackOfCards[i]->setPos(0,0);
        }
    }
}

void Stack::add_cards(QList<Card *> cards){
    for(int i=0; i<cards.size(); i++){
        cards[i]->set_whichStackC(nameOfStack);
        stackOfCards.append(cards[i]);
        cards[i]->setParentItem(this);
        cards[i]->setPos(0,0);

    }
}

void Stack::remove_card(Card *card){
    stackOfCards.removeOne(card);
}

int Stack::return_size(){
    return stackOfCards.size();
}

int Stack::return_indexOf(Card *card, int pStart){
    return stackOfCards.indexOf(card,0);
}

QString Stack::return_nameOfStack(){
    return nameOfStack;
}

void Stack::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(game->MoveMode == true || game->stock1_hasNoCards()){
        game->placeStack(this);
    }


}







