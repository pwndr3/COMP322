#include "blackjack.h"

using namespace std;

/**
 * Card
 */

// Constructor
Card::Card(Rank rank, Type type) : m_rank(rank), m_type(type) {}

// Return numeric value of card
int Card::getValue() {
    return (this->m_rank > 10) ? 10 : this->m_rank;
}

// Display card as RT, R = rank, T = type
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
                // Shouldn't happen
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
            // Shouldn't happen
            cout << '?';
    }
}

/**
 * Hand
 */

// Add card to hand
// Param: card: card to add
void Hand::add(Card card) {
    this->m_cards.push_back(card);
}

// Remove all cards from hand
void Hand::clear() {
    this->m_cards.clear();
}

// Get total numeric value of the hand.
// Ace is taken to be 11 if hand value
// is not over 21, otherwise it is 1.
int Hand::getTotal() {
    int total_ace_1 = 0;
    int total_ace_11 = 0;

    // Add value of each card
    for(Card card : this->m_cards) {
        int val = card.getValue();

        // Compute total if Ace is 1 or 11
        if(val == 1) {
            // If Ace
            total_ace_1++;
            total_ace_11 += 11;
        } else {
            // If any other card
            total_ace_1 += val;
            total_ace_11 += val;
        }
    }

    // Keep highest, given that not busted
    if(total_ace_11 <= 21)
        return total_ace_11;
    
    return total_ace_1;
}

// Display hand, space-separated cards
void Hand::displayHand() {
    for(Card card: this->m_cards) {
        card.displayCard();
        cout << " ";
    }
}

/**
 * Deck
 */

// Random number generator initialization
default_random_engine Deck::m_rng = default_random_engine(chrono::system_clock::now().time_since_epoch().count());

// Constructor
Deck::Deck() {
    this->populate(); // Populate card with new shuffled cards
}

// Shuffle deck
void Deck::shuffle() {
    std::shuffle(this->m_cards.begin(), this->m_cards.end(), Deck::m_rng);
}

// Deal one card at random from the remaining cards in the deck
Card Deck::deal() {
    // Get last card
    Card card = this->m_cards.back();

    // Remove from vector
    this->m_cards.pop_back();
    
    // Return dealt card
    return card;
}

// Populate deck. Clear current cards, add all 52 cards, then shuffle
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

/**
 * AbstractPlayer
 */

// Return true if player is busted (hand value over 21)
bool AbstractPlayer::isBusted() {
    return (this->m_hand.getTotal() > 21);
}

// Add card to player's hand
// Param: card: card to add
void AbstractPlayer::add(Card card) {
    this->m_hand.add(card);
}

// Clear player's hand
void AbstractPlayer::clear() {
    this->m_hand.clear();
}

// Get player's hand value
int AbstractPlayer::getTotal() {
    return this->m_hand.getTotal();
}

/**
 * HumanPlayer
 */

// Ask user if he/she wants to true, return answer
bool HumanPlayer::isDrawing() {
    cout << "Do you want to draw? (y/n):";

    char ans;
    cin >> ans;

    return (ans == 'y'); // True if ans == 'y', false otherwise
}

// Announce the winner of the game.
// Param: winner: a pointer to the winner, null if none.
// Param: busted: true if winner won because their opponent is busted
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

// Show human player's hand
void HumanPlayer::showHand() {
    cout << "Player: ";
    this->m_hand.displayHand();
    cout << "[" << this->getTotal() << "]" << endl;
}

/**
 * ComputerPlayer
 */

// Computer draws if its total is less than or equal to 16
bool ComputerPlayer::isDrawing() {
    return (this->m_hand.getTotal() <= 16);
}

// Show computer player's hand
void ComputerPlayer::showHand() {
    cout << "Casino: ";
    this->m_hand.displayHand();
    cout << "[" << this->getTotal() << "]" << endl;
}

/**
 * BlackJackGame
 */

// Play a round
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
            // If human player busts, announce winner then quit
            this->m_human.announce(&this->m_casino, true);
            return;
        }
    }

    // Casino's turn
    while(this->m_casino.isDrawing()) {
        this->m_casino.add(this->m_deck.deal());
        this->m_casino.showHand();

        if(this->m_casino.isBusted()) {
            // If casino busts, announce winner then quit
            this->m_human.announce(&this->m_human, true);
            return;
        }
    }

    // If no one busted, announce winner
    if(this->m_human.getTotal() > this->m_casino.getTotal()) 
        this->m_human.announce(&this->m_human, false); // Human wins
    else if(this->m_human.getTotal() < this->m_casino.getTotal()) 
        this->m_human.announce(&this->m_casino, false); // Casino wins
    else
        this->m_human.announce(NULL, false); // Push
}