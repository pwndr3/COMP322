#ifndef _BLACKJACK_H
#define _BLACKJACK_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// Card ranks
enum Rank {
    ACE = 1, 
    TWO, 
    THREE, 
    FOUR, 
    FIVE, 
    SIX, 
    SEVEN, 
    EIGHT, 
    NINE, 
    TEN, 
    JACK, 
    QUEEN, 
    KING
};

// Card types
enum Type {
    CLUBS, 
    DIAMONDS, 
    HEARTS, 
    SPADES
};

class Card {
    public:
        // Constructor
        Card(Rank rank, Type type);

        // Public methods
        int getValue();
        void displayCard();    

    private:
        // Delete default constructor
        Card();

        // Private variables
        Rank m_rank;
        Type m_type;
};

class Hand {
    public:
        // Public methods
        void add(Card card);
        void clear();
        int getTotal();
        void displayHand();
    
    private:
        // Private variables
        std::vector<Card> m_cards;
};

class Deck {
    public:
        // Constructor
        Deck();

        // Public methods
        Card deal();

    private:
        // Private variables
        std::vector<Card> m_cards;

        // Private static variables
        static std::default_random_engine m_rng;

        // Private methods
        void populate();
        void shuffle();
};

class AbstractPlayer {
    public:
        // Public methods
        virtual bool isDrawing() = 0;
        virtual void showHand() = 0;
        bool isBusted();

        void add(Card card);
        void clear();
        int getTotal();

    protected:
        // Protected variables
        Hand m_hand;
};

class HumanPlayer: public AbstractPlayer {
    public:
        // Public methods
        bool isDrawing();
        void announce(AbstractPlayer* winner, bool busted);
        void showHand();
};

class ComputerPlayer: public AbstractPlayer {
    public:
        // Public methods
        bool isDrawing();
        void showHand();
};

class BlackJackGame {
    public:
        // Public methods
        void play();

    private:
        // Private variables
        Deck m_deck;
        HumanPlayer m_human;
        ComputerPlayer m_casino;
};

#endif // _BLACKJACK_H