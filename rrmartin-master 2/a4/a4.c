#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "a4.h"

#define PRINT_DEBUG 1

// Implement the Hand and other functions in here

Card* createCard(Suit Suit, Name Name){

    Card* card = (Card*) malloc(sizeof(Card));

    card->name = Name;
    card->suit = Suit;

    return card;
}

void destroyCard(Card* card){

    free(card);
}

Hand* createHand() {

    Hand* hand = (Hand*)malloc(sizeof(Hand));

    hand->num_cards_in_hand = 0;

    return hand;
}

void addCardToHand(Card *card, Hand *hand) {

    CardNode* cardNode = (CardNode*)malloc(sizeof(CardNode));

    cardNode->thisCard = card;

    cardNode->nextCard = hand->firstCard;
    cardNode->prevCard = NULL;

    if(hand->firstCard != NULL)
        hand->firstCard->prevCard = cardNode;

    hand->firstCard = cardNode;

    hand->num_cards_in_hand++;

}

void destroyCardNode(CardNode *cardNode){
    while(cardNode !=NULL)
        cardNode--;
    free(cardNode);

}

Card * removeCardFromHand(Card *card, Hand *hand){
  
    CardNode* temp = hand -> firstCard;
    while (temp != NULL && temp -> thisCard != card) {
        temp = temp -> nextCard;
    }
    if (hand -> firstCard == temp) {
        hand -> firstCard = temp -> nextCard;
    }
    if(temp->nextCard != NULL) {
        temp->nextCard->prevCard = temp->prevCard;
    }
    if(temp->prevCard != NULL) {
        temp->prevCard->nextCard = temp->nextCard;
    }

    hand->num_cards_in_hand--;
    free(temp);
    return card;
}
   

int isHandEmpty(struct hand *Hand){

    CardNode* cardNode = (CardNode*)malloc(sizeof(CardNode));
    if(Hand->firstCard == NULL && cardNode->prevCard ==NULL)
        return 1;
    else
        return 0;
}

void destroyHand(struct hand* Hand){
    free(Hand->firstCard);
    free(Hand);
}

void swap (Deck *deck, int i, int j){

    Card* temp = deck->cards[i];
    deck->cards[i] = deck->cards[j];
    deck->cards[j] = temp;
}

void shuffle(Deck *aDeck){

    srand((unsigned int) time(NULL));

    for(int i = NUM_CARDS_IN_DECK-1; i > 0; i--){
        int j = rand() % (i+1);

        swap(aDeck, i, j);
    }

}

void deal(Deck *aDeck, Hand *p1hand, Hand *p2hand){
    shuffle(aDeck);
    CardNode *ptr = p1hand->firstCard;
    int i = 4;

    while(ptr != NULL) {
        ptr = ptr->nextCard;
        i--;
    }

    ptr = p2hand->firstCard;
    i = 4;

    while(ptr != NULL) {
        ptr = ptr->nextCard;
        i--;
    }
}

int isLegalMove(Hand *hand, Card *leadCard, Card *playedCard) {

    CardNode* temp = hand->firstCard;
    while(temp != NULL){
        if(temp->thisCard->suit == leadCard->suit){
            if(leadCard->suit == playedCard->suit){
                return 1;
            }else{
                return 0;
            }
        }
        temp = temp->nextCard;
    }
    return 1;
}

int whoWon(Card *leadCard, Card *followedCard, Suit trump) {

    if (leadCard->suit == followedCard->suit) {
        if (leadCard->value > followedCard->value) {
            return 1;
        } else {
            return 0;
        }

    } else{

        if (followedCard->suit != trump) {
            if (leadCard->suit != followedCard->suit) {
                return 1;
            }
            return 0;
        }
    }
    return 0;

}

void returnHandToDeck(Hand *hand, Deck *deck) {

      while(hand->num_cards_in_hand > 0){
      pushCardToDeck((Card *) hand->num_cards_in_hand, deck);
      hand--;
    }
}

