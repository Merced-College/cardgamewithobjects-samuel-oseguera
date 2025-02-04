// Names: Samuel Oseguera, Jose Arellano, Michael Santos, Arnold Rocha
// Date: 1/30/25
// Making a card game

#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

// Class for the card
class Card { // Keeps a card object
public:
    Card(string suit = "", string rank = "", int value = 0)  // Constructor which initializes the card object
        : suit(suit), rank(rank), value(value) {}

    // Getters 
    string get_suit() { return suit; }    // Returns suit
    string get_rank() { return rank; }    // Returns rank
    int get_value() { return value; }     // Returns value

    // Setters
    void set_suit(string new_suit) { suit = new_suit; }
    void set_rank(string new_rank) { rank = new_rank; }
    void set_value(int new_value) { value = new_value; }

    // Prints the card details
    void print_card() {
        cout << rank << " of " << suit << " (Value: " << value << ")" << endl;
    }

private:
    string suit;  // Stores the card suit
    string rank;  // Stores the card rank
    int value;    // Stores the card value
};

// Constants
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};  // Holds 4 possible suits
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", 
                        "9", "10", "Jack", "Queen", "King", "Ace"}; // Holds all ranks
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};  // Assigns numerical value to each rank

Card deck[52];  // Full deck of cards
int currentCardIndex = 0; // Card index set to 0; keeps track of which card is next in the deck
bool play = true;   // Control game loop
int wins = 0;       // Tracks the wins
int ties = 0;       // Tracks the ties
int loses = 0;      // Tracks the losses
string response = ""; // Stores user input

// Initializing deck function
void initializeDeck() {
    int deckIndex = 0;                                        
    for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
        for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
            deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
        }
    }
}

// Shuffle deck function
void shuffleDeck() {
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        Card temp = deck[i];
        deck[i] = deck[index];
        deck[index] = temp;
    }
}

// Deal the card (ensures it is dealt in order)
Card dealCard() { 
    return deck[currentCardIndex++]; 
}

// Deal the cards to the player
int dealInitialPlayerCards() {  
    Card card1 = dealCard();
    Card card2 = dealCard();
    cout << "Your cards: ";
    card1.print_card();       
    card2.print_card();       
    return card1.get_value() + card2.get_value();
}

// Player's turn
int playerTurn(int playerTotal) {
    while (true) {  
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        
        if (action == "hit") {
            Card newCard = dealCard();
            playerTotal += newCard.get_value();
            cout << "You drew a ";
            newCard.print_card();
            if (playerTotal > 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

// Deal the dealer's cards
int dealInitialDealerCards() {
    Card card1 = dealCard();
    Card card2 = dealCard();
    cout << "Dealer's cards: ";
    card1.print_card();
    card2.print_card();
    return card1.get_value() + card2.get_value(); 
}

// Dealer's turn
int dealerTurn(int dealerTotal) { 
    while (dealerTotal < 17) {    
        Card newCard = dealCard();
        dealerTotal += newCard.get_value();
        cout << "Dealer drew a ";
        newCard.print_card();
    }
    return dealerTotal;   
}

// Determine the winner
void determineWinner(int playerTotal, int dealerTotal) {  
    cout << "Your total: " << playerTotal << endl;
    cout << "Dealer's total: " << dealerTotal << endl;

    if (playerTotal > 21) {                       
        cout << "You busted! Dealer wins." << endl;  
        loses++; 
    } else if (dealerTotal > 21) {    
        cout << "Dealer busted! You win." << endl;
        wins++; 
    } else if (playerTotal > dealerTotal) { 
        cout << "You win!" << endl;
        wins++;
    } else if (playerTotal < dealerTotal) { 
        cout << "Dealer wins!" << endl;
        loses++;
    } else {
        cout << "It's a tie!" << endl;
        ties++; 
    }
}

// Main function (addition from previous project)
int main() {
    while (play == true) { 
        initializeDeck(); 
        shuffleDeck();

        int playerTotal = dealInitialPlayerCards();
        int dealerTotal = dealInitialDealerCards();
        playerTotal = playerTurn(playerTotal);

        if (playerTotal > 21) {
            cout << "You busted! Dealer wins." << endl;
            loses++;
        } else {
            dealerTotal = dealerTurn(dealerTotal);
            determineWinner(playerTotal, dealerTotal);
        }

        cout << "Play again? \n";
        getline(cin, response); 
        
        if (response == "No" || response == "no") {  
            play = false;
        } else if (response == "Yes" || response == "yes") {
            play = true;
        } else {
            cout << "Invalid input";
        }

        cout << "Wins: " << wins << " \n" 
             << "Loses: " << loses << " \n" 
             << "Ties: " << ties << "\n"; 
    }
    return 0;
}
