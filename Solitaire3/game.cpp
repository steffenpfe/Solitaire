#include "game.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include "button.h"
#include <QString>
#include <QPointF>
#include <QBrush>
#include <QImage>

#include <QDebug>


Game::Game(QWidget *parent){
    //set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    //background
    setBackgroundBrush(QBrush(QImage(":/images/bg.jpg")));

    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768); //for no autosize
    setScene(scene);


    //initialize
    MoveMode = false;



}


void Game::displayMainMenu(){
    //create the title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Solitaire"));
    QFont titleFond("comic sans",50);
    titleText->setFont(titleFond);
    //this->width   --width of the scene
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //create the play button
    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    //create the quit button
    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}


void Game::pickUpCard(Card *card){
    pickedCard = card;
    whichStackCard = which_stack_isCard(card);

    //Wenn Karte von STOCK1, dann auf STOCK2 und aufdecken
    if(whichStackCard->return_nameOfStack() == QString("STOCK1")){
        //add stock2, remove from stock1
        cardsToPlace.append(card);
        stock2->add_cards(cardsToPlace);
        stock1->remove_card(card);
        //aufdecken
        card->set_frontOfCard(true);
        card->change_front();
        resetPlace();
        return;
    }

    //change front of top card when no frontOfCard!
    if(card->get_frontOfCard() == false){
        if(whichStackCard->return_indexOf(card,0) == whichStackCard->return_size()-1){
            card->set_frontOfCard(true);
            card->change_front();
            resetPlace();
        }
        return; //nun kommen nur noch aufgedeckte Karten weiter
    }


    //Alle aufgedeckten Karten ab gewählter Karte aufnehmen
    if(whichStackCard->stackOfCards.indexOf(card,0) >=0){
        for(int i=whichStackCard->stackOfCards.indexOf(card,0);
            i<whichStackCard->stackOfCards.size(); i++){
            cardsToPlace.append(whichStackCard->stackOfCards[i]);
        }
    }

    //RemoveCards from old Stack
    for(int i=0; i<cardsToPlace.size(); i++){
        //whichStackCard->stackOfCards.removeOne(cardsToPlace[i]);
        whichStackCard->remove_card(cardsToPlace[i]);
    }

    MoveMode = true;
}


void Game::placeCard(Card *cardToReplace){
    whichStackCardRe = which_stack_isCard(cardToReplace);
    int size = whichStackCardRe->stackOfCards.size();

    if(whichStackCardRe->stackOfCards[size-1]->get_frontOfCard() == false){
        return;
    }

    //Es dürfen keine Karten auf STOCK1
    if(whichStackCardRe->return_nameOfStack() == QString("STOCK1")){
        return;
    }else if(whichStackCardRe->return_nameOfStack() == QString("STOCK2") &&
             pickedCard->get_whichStack() != QString("STOCK2")){
        return;
    }

    //bedingungen für die TEMP STACKS
    if(whichStackCardRe->return_nameOfStack() == QString("TEMP1") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP2") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP3") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP4") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP5") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP6") ||
             whichStackCardRe->return_nameOfStack() == QString("TEMP7")){
        //Farbe muss unterschiedlich sein
        if(whichStackCardRe->stackOfCards[size-1]->get_color() == cardsToPlace[0]->get_color()){
            return;
        }
        //Rang muss kleiner sein
        if(whichStackCardRe->stackOfCards[size-1]->get_rank()-1 != cardsToPlace[0]->get_rank()){
            return;
        }
    }

    //Bedingungen für den MAIN STACK
    if(whichStackCardRe->return_nameOfStack() == QString("MAIN1") ||
       whichStackCardRe->return_nameOfStack() == QString("MAIN2") ||
       whichStackCardRe->return_nameOfStack() == QString("MAIN3") ||
       whichStackCardRe->return_nameOfStack() == QString("MAIN4")){
        //Symbol muss gleich sein
        if(cardsToPlace.size() > 1){
            return;
        }
        if(whichStackCardRe->stackOfCards[size-1]->get_symbol() != cardsToPlace[0]->get_symbol()){
            return;
        }
        //Rang muss größer werden
        if(whichStackCardRe->stackOfCards[size-1]->get_rank()+1 != cardsToPlace[0]->get_rank()){
            return;
        }
    }




    whichStackCardRe->add_cards(cardsToPlace);
    resetPlace();

    if(main1->return_size()==13 && main2->return_size()==13 && main3->return_size()==13 && main4->return_size()==13){
        gameOverWindow();
    }
}

void Game::placeStack(Stack *stack){

    if(stack->return_nameOfStack() ==QString("MAIN1") ||
       stack->return_nameOfStack() ==QString("MAIN2") ||
       stack->return_nameOfStack() ==QString("MAIN3") ||
       stack->return_nameOfStack() ==QString("MAIN4")){
        //erste Karte muss Ass sein
        if(cardsToPlace[0]->get_rank() == 0){
           stack->add_cards(cardsToPlace);
           resetPlace();
       }
    }else if(stack->return_nameOfStack() ==QString("TEMP1") ||
             stack->return_nameOfStack() ==QString("TEMP2") ||
             stack->return_nameOfStack() ==QString("TEMP3") ||
             stack->return_nameOfStack() ==QString("TEMP4") ||
             stack->return_nameOfStack() ==QString("TEMP5") ||
             stack->return_nameOfStack() ==QString("TEMP6") ||
             stack->return_nameOfStack() ==QString("TEMP7")){
        //erste Karte muss König sein
        if(cardsToPlace[0]->get_rank() == 12){
            stack->add_cards(cardsToPlace);
            resetPlace();
        }
    }else if(stack->return_nameOfStack() == QString("STOCK2")){
        //erste Karte muss vom selben Stapel oder von STOCK1 kommen(max 1 Karte)
        if(cardsToPlace.size() == 1 && (cardsToPlace[0]->get_whichStack() == QString("STOCK1") ||
           cardsToPlace[0]->get_whichStack() == QString("STOCK2"))){
            stack->add_cards(cardsToPlace);
            resetPlace();
        }
    }else if(stack->return_nameOfStack() == QString("STOCK1")){
        //wenn stock1, dann alle Karten von stock2 auf stock1-> stack=stock1
        cardsToPlace.clear();
        //reihenfolge umdrehen
        for(int i=0; i<stock2->stackOfCards.size(); i++){
            cardsToPlace.append(stock2->stackOfCards[stock2->stackOfCards.size()-1-i]);
        }

        stack->add_cards(cardsToPlace);
        stock2->stackOfCards.clear();

        //Alle Karten wieder zudecken
        for(int i=0; i<stack->stackOfCards.size(); i++){
            stack->stackOfCards[i]->set_frontOfCard(false);
            stack->stackOfCards[i]->change_front();
        }
        resetPlace();
        return;
    }
}


void Game::resetPlace(){
    cardsToPlace.clear();
    redraw_allStacks();
    MoveMode = false;
}


Stack *Game::which_stack_isCard(Card *card){
    if(card->get_whichStack() == QString("STOCK1")){
        return stock1;
    }else if(card->get_whichStack() == QString("STOCK2")){
        return stock2;
    }else if(card->get_whichStack() == QString("MAIN1")){
        return main1;
    }else if(card->get_whichStack() == QString("MAIN2")){
        return main2;
    }else if(card->get_whichStack() == QString("MAIN3")){
        return main3;
    }else if(card->get_whichStack() == QString("MAIN4")){
        return main4;
    }else if(card->get_whichStack() == QString("TEMP1")){
        return temp1;
    }else if(card->get_whichStack() == QString("TEMP2")){
        return temp2;
    }else if(card->get_whichStack() == QString("TEMP3")){
        return temp3;
    }else if(card->get_whichStack() == QString("TEMP4")){
        return temp4;
    }else if(card->get_whichStack() == QString("TEMP5")){
        return temp5;
    }else if(card->get_whichStack() == QString("TEMP6")){
        return temp6;
    }else if(card->get_whichStack() == QString("TEMP7")){
        return temp7;
    }
}


void Game::redraw_allStacks(){

    stock1->create_stack();
    stock2->create_stack();
    main1->create_stack();
    main2->create_stack();
    main3->create_stack();
    main4->create_stack();
    temp1->create_stack();
    temp2->create_stack();
    temp3->create_stack();
    temp4->create_stack();
    temp5->create_stack();
    temp6->create_stack();
    temp7->create_stack();
}

bool Game::stock1_hasNoCards(){
    if(stock1->stackOfCards.size() == 0){
        return true;
    }
    else{
        return false;
    }
}

void Game::gameOverWindow(){
    //disable all scene items
    for(size_t i=0, n=scene->items().size(); i<n; i++){
        scene->items()[i]->setEnabled(false);
    }

    //pop up semi transparent window
    drawPanel(0,0,1024,768,Qt::black,0.65);

    //draw panel
    drawPanel(312,184,400,400,Qt::lightGray,0.75);

    //create playAgain button
    Button *playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,300);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    //create quit button
    Button *quit = new Button(QString("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    //create text announcing winner
    QGraphicsTextItem *overText = new QGraphicsTextItem(QString("You won!"));
    overText->setPos(460,225);
    scene->addItem(overText);

}


void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    //draw a panel at a specified location with the specified properties
    QGraphicsRectItem *panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}



void Game::mouseMoveEvent(QMouseEvent *event){
    if(cardsToPlace.size() > 0){
        for(int i=0; i<cardsToPlace.size(); i++){
            cardsToPlace[i]->setParentItem(NULL);
            cardsToPlace[i]->setPos(event->x()+5,event->y()+30*i+5);
        }
    }
QGraphicsView::mouseMoveEvent(event);
}


void Game::mousePressEvent(QMouseEvent *event){
    //return card to old stack for right button
    if(event->button() == Qt::RightButton && MoveMode == true){
        whichStackCardRe = which_stack_isCard(pickedCard);
        whichStackCardRe->add_cards(cardsToPlace);
        resetPlace();
    }
    QGraphicsView::mousePressEvent(event);

}


void Game::start(){

    //clear the screen
    scene->clear();

    Deck *deck = new Deck();
    deck->riffle_cards();

    stock1 = new Stack(deck,0,24,QString("STOCK1"));
    stock2 = new Stack(deck,0,0,QString("STOCK2"));
    main1 = new Stack(deck,0,0,QString("MAIN1"));
    main2 = new Stack(deck,0,0,QString("MAIN2"));
    main3 = new Stack(deck,0,0,QString("MAIN3"));
    main4 = new Stack(deck,0,0,QString("MAIN4"));
    temp1 = new Stack(deck,24,1,QString("TEMP1"));
    temp2 = new Stack(deck,25,2,QString("TEMP2"));
    temp3 = new Stack(deck,27,3,QString("TEMP3"));
    temp4 = new Stack(deck,30,4,QString("TEMP4"));
    temp5 = new Stack(deck,34,5,QString("TEMP5"));
    temp6 = new Stack(deck,39,6,QString("TEMP6"));
    temp7 = new Stack(deck,45,7,QString("TEMP7"));

    scene->addItem(stock1);
    scene->addItem(stock2);
    scene->addItem(main1);
    scene->addItem(main2);
    scene->addItem(main3);
    scene->addItem(main4);
    scene->addItem(temp1);
    scene->addItem(temp2);
    scene->addItem(temp3);
    scene->addItem(temp4);
    scene->addItem(temp5);
    scene->addItem(temp6);
    scene->addItem(temp7);

    stock1->setPos(50,50);
    stock2->setPos(300,50);
    main1->setPos(590,50);
    main2->setPos(690,50);
    main3->setPos(790,50);
    main4->setPos(890,50);
    temp1->setPos(110,200);
    temp2->setPos(220,200);
    temp3->setPos(330,200);
    temp4->setPos(440,200);
    temp5->setPos(550,200);
    temp6->setPos(660,200);
    temp7->setPos(770,200);

}

void Game::restartGame(){
    start();
}
