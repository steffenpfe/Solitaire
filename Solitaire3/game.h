#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <QPointF>
#include <QList>

#include "card.h"
#include "deck.h"
#include "stack.h"


class Game: public QGraphicsView{
    Q_OBJECT
public:
    //constructors
    Game(QWidget *parent=NULL);

    //public methods
    void displayMainMenu();
    void pickUpCard(Card *card);

    void placeCard(Card *cardToReplace);
    void placeStack(Stack *stack);
    //call if place successful or not
    void resetPlace();

    Stack* which_stack_isCard(Card *card);
    void redraw_allStacks();

    bool stock1_hasNoCards();
    void gameOverWindow();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);


    //events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    //public attributes
    QGraphicsScene *scene;
    bool MoveMode;
    QList<Card*> cardsToPlace;

public slots:
    void start();
    void restartGame();

private:
    //private methods


    //private attributes
    Stack *stock1;
    Stack *stock2;
    Stack *main1;
    Stack *main2;
    Stack *main3;
    Stack *main4;
    Stack *temp1;
    Stack *temp2;
    Stack *temp3;
    Stack *temp4;
    Stack *temp5;
    Stack *temp6;
    Stack *temp7;

    Stack *whichStackCard;
    Stack *whichStackCardRe;
    Card *pickedCard;





};

#endif // GAME_H
