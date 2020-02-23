#include "blackjack.h"

using namespace std;

// Card
Card::Card(Rank rank, Type type) : m_rank(rank), m_type(type) {}

int Card::getValue() {
    return (this->m_rank > 10) ? 10 : this->m_rank;
}

void Card::displayCard() {
    // Display rank
    if (m_rank < 11)
        cout << m_rank;
    else {
        switch(m_rank) {
            case JACK:
                cout << 'J';
                break;
            case QUEEN:
                cout << 'Q';
                break;
            case KING:
                cout << 'K';
                break;
            default:
                cout << '?';
        }
    }

    // Display type
    switch(m_type) {
        case CLUBS:
            cout << 'C';
            break; 
        case DIAMONDS:
            cout << 'D';
            break;
        case HEARTS:
            cout << 'H';
            break;
        case SPADES:
            cout << 'S';
            break;
        default:
            cout << '?';
    }
}

// Hand
void Hand::add(Card card) {
    this->m_cards.push_back(card);
}

void Hand::clear() {
    this->m_cards.clear();
}

int Hand::getTotal() {
    // Compute total if Ace is 1 or 11
    int total_ace_1 = 0;
    int total_ace_11 = 0;

    for(Card card : this->m_cards) {
        int val = card.getValue();

        // Change Ace value to 11
        if(val == 1) {
            total_ace_1++;
            total_ace_11 += 11;
        } else {
            total_ace_1 += val;
            total_ace_11 += val;
        }
    }

    // Keep highest, given that not busted
    if(total_ace_11 <= 21)
        return total_ace_11;
    
    return total_ace_1;
}

// Deck
Deck::Deck() {
    this->populate();
}

void Deck::shuffle() {
    random_shuffle(this->m_cards.begin(), this->m_cards.end());
}

Card Deck::deal() {
    // Get last card
    Card card = this->m_cards.back();

    // Remove from vector
    this->m_cards.pop_back();
    
    // Return dealt card
    return card;
}

void Deck::populate() {
    // Clear cards, if any
    this->m_cards.clear();

    // Populate deck
    for(int i = Type::CLUBS; i <= Type::SPADES; i++) {
        Type type = static_cast<Type>(i);

        for(int j = Rank::ACE; j <= Rank::KING; j++) {
            Rank rank = static_cast<Rank>(j);

            this->m_cards.push_back(Card(rank, type));
        }
    }

    // Shuffle deck
    this->shuffle();
}

// AbstractPlayer
bool AbstractPlayer::isBusted() {
    return (this->m_hand.getTotal() > 21);
}

void AbstractPlayer::add(Card card) {
    this->m_hand.add(card);
}

void AbstractPlayer::clear() {
    this->m_hand.clear();
}

// HumanPlayer
bool HumanPlayer::isDrawing() {
    cout << "Do you want to draw? (y/n):";

    char ans;
    cin >> ans;

    return (ans == 'y');
}

void HumanPlayer::announce() {

}

// ComputerPlayer
bool ComputerPlayer::isDrawing() {
    return (this->m_hand.getTotal <= 16);
}

// BlackJackGame
void BlackJackGame::play() {
    // Initialize game
}