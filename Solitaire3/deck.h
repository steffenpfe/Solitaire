#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <QList>


//collection of all 52 cards
class Deck{
public:
    //constructors
    Deck();

    //public functions
    void riffle_cards();
    Card* get_card(int pIndex);

private:
    //private attributes
    QList<Card*> deckOfCards;
};

#endif // DECK_H
