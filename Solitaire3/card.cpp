#include "card.h"
#include "game.h"
#include <QDebug>

extern Game *game;

Card::Card(int pRank, int pSymbol, int pColor,  QGraphicsItem *parent):
    rankOfCard(pRank), symbolOfCard(pSymbol), colorOfCard(pColor), QGraphicsPixmapItem(parent){

    frontOfCard = true;
    isPlaced = false;
    filenameBackOfCard.append(QString(":/images/Autre/fondCaseBut.bmp"));
    set_filename();
    change_front();
}

int Card::get_rank(){
return rankOfCard;
}

int Card::get_symbol(){
return symbolOfCard;
}

int Card::get_color(){
    return colorOfCard;
}

bool Card::get_isPlaced(){
    return isPlaced;
}

QString Card::get_whichStack(){
    return whichStack;
}

QString Card::get_filename(){
    return filename;
}

bool Card::get_frontOfCard(){
    return frontOfCard;
}


void Card::change_front(){
    if(frontOfCard == false){
        setPixmap(QPixmap(filenameBackOfCard));
    }
    else{
        setPixmap(QPixmap(filename));
    }
}

void Card::set_isPlaced(bool p){
    isPlaced = p;
}

void Card::set_whichStackC(QString pWhichStack){
    whichStack = pWhichStack;
}

void Card::set_frontOfCard(bool b){
    frontOfCard = b;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(game->MoveMode == false){
        game->pickUpCard(this);
    }
    else{
       game->placeCard(this);
    }

}


void Card::set_filename(){
    int startInRes=0;
    if(symbolOfCard == 0){
        startInRes = 0;
    }else if(symbolOfCard == 1){
        startInRes = 13;
    }else if(symbolOfCard == 2){
        startInRes = 26;
    }else if(symbolOfCard == 3){
        startInRes = 39;
    }

    filename.append(QString(":/images/Cartes/"));
    filename.append(QString::number(startInRes + rankOfCard));
    filename.append(QString(".bmp"));
}
