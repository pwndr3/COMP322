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

void Hand::displayHand() {
    for(Card card: this->m_cards) {
        card.displayCard();
        cout << " ";
    }
}

// Deck
default_random_engine Deck::m_rng = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
Deck::Deck() {
    this->populate();
}

void Deck::shuffle() {
    std::shuffle(this->m_cards.begin(), this->m_cards.end(), Deck::m_rng);
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

int AbstractPlayer::getTotal() {
    return this->m_hand.getTotal();
}

// HumanPlayer
bool HumanPlayer::isDrawing() {
    cout << "Do you want to draw? (y/n):";

    char ans;
    cin >> ans;

    return (ans == 'y');
}

void HumanPlayer::announce(AbstractPlayer* winner, bool busted) {
    if (winner == NULL) {
        // Push
        cout << "Push: No one wins." << endl << endl;
    } else if(winner == this) {
        // Human is winner
        if(busted)
            cout << "Casino busts." << endl;
        cout << "Player wins." << endl << endl;
    } else {
        // Casino is winner
        if(busted)
            cout << "Player busts." << endl;
        cout << "Casino wins." << endl << endl;
    }
}

void HumanPlayer::showHand() {
    cout << "Player: ";
    this->m_hand.displayHand();
    cout << "[" << this->getTotal() << "]" << endl;
}

// ComputerPlayer
bool ComputerPlayer::isDrawing() {
    return (this->m_hand.getTotal() <= 16);
}

void ComputerPlayer::showHand() {
    cout << "Casino: ";
    this->m_hand.displayHand();
    cout << "[" << this->getTotal() << "]" << endl;
}

// BlackJackGame
void BlackJackGame::play() {
    // Initialize game
    this->m_deck = Deck();
    this->m_human.clear();
    this->m_casino.clear();
    
    // Casino's first draw
    this->m_casino.add(this->m_deck.deal());
    this->m_casino.showHand();
    
    // Player's first draw
    this->m_human.add(this->m_deck.deal());
    this->m_human.add(this->m_deck.deal());
    this->m_human.showHand();

    // Player's turn
    while(this->m_human.isDrawing()) {
        this->m_human.add(this->m_deck.deal());
        this->m_human.showHand();

        if(this->m_human.isBusted()) {
            this->m_human.announce(&this->m_casino, true);
            return;
        }
    }

    // Casino's turn
    while(this->m_casino.isDrawing()) {
        this->m_casino.add(this->m_deck.deal());
        this->m_casino.showHand();

        if(this->m_casino.isBusted()) {
            this->m_human.announce(&this->m_human, true);
            return;
        }
    }

    // If no one busted, announce winner
    if(this->m_human.getTotal() > this->m_casino.getTotal())
        this->m_human.announce(&this->m_human, false);
    else if(this->m_human.getTotal() < this->m_casino.getTotal())
        this->m_human.announce(&this->m_casino, false);
    else
        this->m_human.announce(NULL, false);
}