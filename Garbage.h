#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

class Card {
public:
    string number;
    string suit;
    [[nodiscard]] string getCard() const {
        return number + " of " + suit;
    }
};

class Suit {
private:
    vector<Card> cards;
    int draws = 0;
public:
    explicit Suit(const string& suit) {
        for(int i = 0; i < 13; i++) {
            cards.push_back(createCard(i, suit));
        }
    }
    static Card createCard(int i, string suit = "") {
        Card temp;
        temp.suit = std::move(suit);
        switch(i) {
            case 0: {
                temp.number = "Ace";
                break;
            }
            case 1: {
                temp.number = "Two";
                break;
            }
            case 2: {
                temp.number = "Three";
                break;
            }
            case 3: {
                temp.number = "Four";
                break;
            }
            case 4: {
                temp.number = "Five";
                break;
            }
            case 5: {
                temp.number = "Six";
                break;
            }
            case 6: {
                temp.number = "Seven";
                break;
            }
            case 7: {
                temp.number = "Eight";
                break;
            }
            case 8: {
                temp.number = "Nine";
                break;
            }
            case 9: {
                temp.number = "Ten";
                break;
            }
            case 10: {
                temp.number = "Jack";
                break;
            }
            case 11: {
                temp.number = "Queen";
                break;
            }
            case 12: {
                temp.number = "King";
                break;
            }
            default: {
                temp.number = "";
                break;
            }
        }
        return temp;
    }
    void shuffle() {
        ::shuffle(&cards[0], &cards[13], std::mt19937(std::random_device()()));
    }
    void printSuit() {
        for(int i = 0; i < 13 ; i++) {
            if(!(cards[i].number.empty() && cards[i].suit.empty())) {
                cout << cards[i].number << " of " << cards[i].suit << endl;
            }
        }
    }
    Card drawCard(int num) {
        Card cardWanted = cards[num];


        int cardPos = 0;
        for(int i = 0; i < (13 - draws); i++) {
            if(cards.at(i).getCard() == cardWanted.getCard()) {
                cardPos = i;
            }
        }

        draws++;

        cards.erase(cards.begin() + cardPos);

        return cardWanted;
    }
};

namespace Suits {
    Suit Spades("Spades");
    Suit Hearts("Hearts");
    Suit Diamonds("Diamonds");
    Suit Clubs("Clubs");
}
using namespace Suits;

class Deck {
private:
    Suit cards[4] = {Spades, Hearts, Diamonds, Clubs};
public:
    void shuffle() {
        cards[0].shuffle();
        cards[1].shuffle();
        cards[2].shuffle();
        cards[3].shuffle();
    }
    void printDeck() {
        cards[0].printSuit();
        cards[1].printSuit();
        cards[2].printSuit();
        cards[3].printSuit();
    }
    Card draw() {
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<>dis(0, 12);
        uniform_int_distribution<>dat(0, 3);
        int random_number = dis(gen);
        int random_suit = dat(gen);

        while(cards[random_suit].drawCard(random_number).number.empty() && cards[random_suit].drawCard(random_number).suit.empty()) {
            random_number = dis(gen);
            random_suit = dat(gen);
        }

        Card temp = cards[random_suit].drawCard(random_number);

        return temp;
    }
};

class Field {
private:
    Card cards[10];
public:
    explicit Field(Deck deck) {
        for(auto & card : cards) {
            card = deck.draw();
        }
    }
    void printField() {
        cout << "Cards on the Field: \n";
        for(auto & card : cards) {
            cout << card.number << " of " << card.suit << endl;
        }
    }
};