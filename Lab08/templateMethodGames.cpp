// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

// template for any game where players take
// turns to make moves
// and there is a winner
class Game
{
public:
   Game() : playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

   // template method
   void playGame(const int playersCount = 0)
   {
      playersCount_ = playersCount;
      movesCount_ = 0;

      initializeGame();

      for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_)
      {
         makeMove(i);
         if (i == playersCount_ - 1)
            ++movesCount_;
      }
      printWinner();
   }

   virtual ~Game() {}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
                                                               // returns true if winner is decided
   static const int noWinner = -1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

class Dice : public Game
{
public:
   void roll(int player[])
   {
      // store each roll, and add them up
      int sum = 0;
      for (int i = 0; i < 5; ++i)
      {
         player[i] = rand() % 6 + 1;
         sum += player[i];
      }
      player[5] = sum; // store that roll's sum
      if (sum > player[6])
         player[6] = sum; // check if it is the greatest or not
   }

   void initializeGame() override
   {
      playersCount_ = numberOfPlayers_;
      for (int i = 0; i < 7; ++i)
      {
         playerRolls_[i] = 0;
         compRolls_[i] = 0;
      }
   }

   bool endOfGame() override{
      return movesCount_ >= maxMoves_ || (compPass_ == true && playerPass_ == true);
   }

   void makeMove(int player) override
   { // player is whose turn it is
      if (movesCount_ < maxMoves_ || (compPass_ == false && playerPass_ == false))
      {
         if (player == 0)
         { // computer's turn
            if(compPass_ == false)
            {
               int choice = rand() % 2;
               if (choice == 0)
               {
                  roll(compRolls_);
               }
               else
               {
                  for(int i = 0; i < 6; ++i) 
                     compRolls_[i] = 0;
                  compPass_ = true;
               }
            }
            // print array and the highest score so far
            cout << "The Computer rolled: ";
            if(compPass_) cout << "They passed ";
            else
            {
               for (int i = 0; i < 5; ++i)
               {
                  cout << compRolls_[i] << ' ';
               }
               cout << "= " << compRolls_[5];
            }
            cout << ", computer's highest score = " << compRolls_[6];
         }

         if (player == 1)
         { // player turn
            // Ask for input
            char userInput;
            cout << "\nYou rolled: ";
            // print array and the highest score so far
            if (playerPass_ == false)
            {
               roll(playerRolls_);
               for (int i = 0; i < 5; ++i)
               {
                  cout << playerRolls_[i] << ' ';
               }
               cout << "= " << playerRolls_[5] << ", players's highest score = " << playerRolls_[6];
            }
            else
            {
               cout << "passed, your highest score = " << playerRolls_[6];
            }
            
            if(movesCount_ < 3 || !playerPass_){
               cout << "\nDo you want to roll? [Y/N] ";
               std::cin >> userInput;
               if (userInput == 'n' || userInput == 'N')
               {
                  playerPass_ = true;
               }
            }
            else
            {
               cout << endl;
            }
         }
      }
   }

   void printWinner() override
   {
      if (playerRolls_[6] > compRolls_[6])
      {
         cout << "You win!" << endl;
      }
      else
      {
         cout << "\nComptuer wins :(" << endl;
      }
   }

private:
   static const int numberOfPlayers_ = 2;
   static const int maxMoves_ = 3;
   // Two arrays to store player's and computer's rolls (0-4) and final sum for each round (5) and the highest score(6)
   int playerRolls_[7];
   int compRolls_[7];

   bool playerPass_ = false;
   bool compPass_ = false;
};

// Monopoly - a concrete game implementing primitive
// operations for the template method
class Monopoly : public Game
{
public:
   // implementing concrete methods
   void initializeGame()
   {
      playersCount_ = rand() % numPlayers_ + 1; // initialize players
   }

   void makeMove(int player)
   {
      if (movesCount_ > minMoves_)
      {
         const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
         if (chance < movesCount_)
            playerWon_ = player;
      }
   }

   void printWinner()
   {
      cout << "Monopoly, player " << playerWon_ << " won in "
           << movesCount_ << " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20;  // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game
{
public:
   void initializeGame()
   {
      playersCount_ = numPlayers_; // initalize players
      for (int i = 0; i < numPlayers_; ++i)
         experience_[i] = rand() % maxExperience_ + 1;
   }

   void makeMove(int player)
   {
      if (movesCount_ > minMoves_)
      {
         const int chance = (rand() % maxMoves_) / experience_[player];
         if (chance < movesCount_)
            playerWon_ = player;
      }
   }

   void printWinner()
   {
      cout << "Chess, player " << playerWon_
           << " with experience " << experience_[playerWon_]
           << " won in " << movesCount_ << " moves over"
           << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2;      // nobody wins before minMoves_
   static const int maxMoves_ = 100;    // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                                        // the higher, the greater probability of winning
   int experience_[numPlayers_];
};

int main()
{
   srand(time(nullptr));

   Game *gp = nullptr;
   /*
   // play chess 10 times
   for (int i = 0; i < 10; ++i)
   {
      gp = new Chess;
      gp->playGame();
      delete gp;
   }

   // play monopoly 8 times
   for (int i = 0; i < 8; ++i)
   {
      gp = new Monopoly;
      gp->playGame();
      delete gp;
   }
   */

   gp = new Dice;
   gp->playGame();
   delete gp;
}
