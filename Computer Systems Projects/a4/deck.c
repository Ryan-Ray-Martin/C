#include <stdio.h>
#include <stdlib.h>

#include "a4.h"
//#define NUM_CARDS_IN_DECK 24

#define PRINT_DEBUG 1


// Put your deck functions in here
Deck * createDeck(){

    Deck* deck = malloc(sizeof(Deck));

    deck->topCard = -1;
    return deck;
}


void destroyDeck(Deck *deck){

    free(deck);
}

Deck * populateDeck(){

    Deck *deck = createDeck();

    for(int suit = HEARTS; suit <= DIAMONDS; suit++) {
        for (int name = NINE; name <= ACE; name++) {
            pushCardToDeck(createCard(suit, name), deck);

        }
    }
    return deck;
}

Deck * pushCardToDeck(Card *newCard, Deck *deck){

    if(deck->topCard == NUM_CARDS_IN_DECK -1){
        return deck;
    }
    deck->topCard++;
    deck->cards[deck->topCard]= newCard;
    return deck;
}

Card * peekAtTopCard(Deck *deck){

    return deck->cards[deck->topCard];
}

Card * popCardFromDeck(Deck *deck){

    return deck->cards[deck->topCard--];
}
int isDeckEmpty(Deck *deck){

    if (deck->topCard == -1){
        return 1;
    }
    return 0;
}



    
    
  
  
  
  



  
