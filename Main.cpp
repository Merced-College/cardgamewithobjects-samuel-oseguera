#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

class Card { // Keeps a card object
public:
  Card(string suit = "", string rank = "", int value = 0)
      : suit(suit), rank(rank), value(value) {}

  string get_suit() { return suit; }
  string get_rank() { return rank; }
  int get_value() { return value; }

  void set_suit(string new_suit) { suit = new_suit; }
  void set_rank(string new_rank) { rank = new_rank; }
  void set_value(int new_value) { value = new_value; }

  void print_card() {
    cout << rank << " of " << suit << " (Value: " << value << ")" << endl;
  }

private:
  string suit;
  string rank;
  int value;
};

const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Card deck[52];
int currentCardIndex = 0;
bool play = true;
int wins = 0;
int ties = 0;
int loses = 0;
string response = "";

void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i];
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() { 
  return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {  
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();
  return card1.get_value() + card2.get_value();
}

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

int dealInitialDealerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Dealer's cards: ";
  card1.print_card();
  card2.print_card();
  return card1.get_value() + card2.get_value();
}

int dealerTurn(int dealerTotal) {
  while (dealerTotal < 17) {
    Card newCard = dealCard();
    dealerTotal += newCard.get_value();
    cout << "Dealer drew a ";
    newCard.print_card();
  }
  return dealerTotal;
}

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
    
    if (response == "No" ){
      play = false;
    }
    else if (response == "Yes" ){
      play = true;
    }
    else if (response == "yes" ){
      play = true;
    }
    else if (response == "no" ){
      play = false;
    }
    else {
      cout << "Invalid input";
    }
    cout << "Wins: " << wins << " \n" << "Loses: " << loses << " \n" << "Ties: " << ties << "\n";
  }
  return 0;
}
