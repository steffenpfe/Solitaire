#include "deck.h"
//for rand() in riffle_cards()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>


Deck::Deck(){
    //initialize the deck with 52 cards
    int rankNum=0;
    int symbolNum=0;
    int colorNum=0;
    for(int i=0; i<52; i++){
        Card *newCard = new Card(rankNum,symbolNum,colorNum);
        rankNum++;
        //rank
        if(i==12 || i==25 || i==38 || i==51)
            rankNum=0;
        //Hearts, Diamonds, Spades ,Clubs
        if(i==12 || i==25 || i==38 || i==51)
            symbolNum++;
        //Hearts, Diamonds (red) <->  Spades ,Clubs (black)
        if(i==25)
            colorNum = 1;

        deckOfCards.append(newCard);
    }
}


void Deck::riffle_cards(){
    int firstIndex, secondIndex;
    Card *tmpcard;

    srand(time(NULL));
    for(int i=0; i<1000; i++) { //riffle the cards very long
        firstIndex = rand() % 52;
        secondIndex = rand() % 52;

        tmpcard = deckOfCards[firstIndex];
        deckOfCards[firstIndex] = deckOfCards[secondIndex];
        deckOfCards[secondIndex] = tmpcard;

    }
}


Card *Deck::get_card(int pIndex){
    return deckOfCards[pIndex];
}


