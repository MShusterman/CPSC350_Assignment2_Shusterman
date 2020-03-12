#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string enterButton = "";

class gameBoard{

  private:
    int width = 0;
    int length = 0;
    char **board;
    int generation = 0;

  public:

    gameBoard(){
      width = 0;
      length = 0;
      board == NULL;
    }

    gameBoard(char **arr, int oldWidth, int oldLength){
      width = oldWidth;
      length = oldLength;
      generation = 1;
      board = arr;
    }

    ~gameBoard(){
      delete board;
    }

    void passInfo(char **arr, int oldWidth, int oldLength){
      width = oldWidth;
      length = oldLength;
      generation = 0;
      board = arr;
    }

    void printBoard(){
      generation++;
      cout << "Here is generation #: " << generation << endl;
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          cout << board[k][i];
        }
        cout << endl;
      }
      cout << endl;
    }

    void fileOutput(){
      generation++;
      ofstream file;
      file.open ("Shusterman_GameOfLife.txt");

      file << "Here is generation #: " << generation << endl;
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          file << board[k][i];
        }
        file << endl;
      }
      file << endl;

      file.close();
    }

    void fileOutputAppend(){
      generation++;

      std::ofstream outfile;
      outfile.open("Shusterman_GameOfLife.txt", std::ios_base::app);

      outfile << "Here is generation #: " << generation << endl;
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          outfile << board[k][i];
        }
        outfile << endl;
      }
      outfile << endl;

      outfile.close();
    }

    void cleanBoard(){
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          if (board[k][i] == 'X' || board[k][i] == '#'){
            board[k][i] = board[k][i];
          } else{
            board[k][i] = '-';
          }
        }
      }
    }

    char** getBoard(){
      return board;
    }

    int getGeneration(){
      return generation;
    }

    int getWidth(){
      return width;
    }

    int getLength(){
      return length;
    }

    void setBoard(char **arr){
      board = arr;
    }

    void updateBoard(char **arr){
      board = arr;
      generation++;
    }

    void setTo(gameBoard passBoard){
      board = passBoard.getBoard();
      generation = passBoard.getGeneration();
      width = passBoard.getWidth();
      length = passBoard.getLength();
    }

};

class mirrorGame{

  private:
    char **oldBoard;
    char **newBoard;
    int width = 0;
    int length = 0;
    bool boardChanges = false;

  public:
    mirrorGame(){
      //nothing
    }

    mirrorGame(gameBoard& passBoard){
      width = passBoard.getWidth();
      length = passBoard.getLength();

      oldBoard = passBoard.getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    ~mirrorGame(){
      delete oldBoard;
      delete newBoard;
    }

    void passBoard(gameBoard *passBoard){
      //myBoard->setTo(passBoard);

      width = passBoard->getWidth();
      length = passBoard->getLength();

      oldBoard = passBoard->getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    bool getChanges(){
      return boardChanges;
    }

    char** playGame(){
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          if (oldBoard[k][i] == '#'){
            newBoard[k][i] = '#';
            //cout << "#";
          }
          else {
            int neighborCount = 0;

            //Top Row? (Bottom Row?)
            if (oldBoard[k-1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i+1] == 'X'){
              neighborCount++;
            }

            //Middle Row
            if (oldBoard[k][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k][i] == 'X'){
              //do nothing
            }
            if (oldBoard[k][i+1] == 'X'){
              neighborCount++;
            }

            //Bottom Row (Top Row?)
            if (oldBoard[k+1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i+1] == 'X'){
              neighborCount++;
            }

            //Mirror Mode Stuff (top)
            if (oldBoard[k-1][i-1] == '#'){
              if(oldBoard[k][i-1] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k-1][i] == '#'){
              if(oldBoard[k][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k-1][i+1] == '#'){
              if(oldBoard[k][i+1] == 'X'){
                neighborCount++;
              }
            }
            //(left wall)
            if (oldBoard[k-1][i-1] == '#'){
              if(oldBoard[k-1][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k][i-1] == '#'){
              if(oldBoard[k][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k+1][i-1] == '#'){
              if(oldBoard[k+1][i] == 'X'){
                neighborCount++;
              }
            }
            //bottom
            if (oldBoard[k+1][i-1] == '#'){
              if(oldBoard[k][i-1] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k+1][i] == '#'){
              if(oldBoard[k][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k+1][i+1] == '#'){
              if(oldBoard[k][i+1] == 'X'){
                neighborCount++;
              }
            }
            //(Right Wall)
            if (oldBoard[k-1][i+1] == '#'){
              if(oldBoard[k-1][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k][i+1] == '#'){
              if(oldBoard[k][i] == 'X'){
                neighborCount++;
              }
            }
            if (oldBoard[k+1][i+1] == '#'){
              if(oldBoard[k+1][i] == 'X'){
                neighborCount++;
              }
            }

            //Corner check
            if (oldBoard[k-1][i] == '#' && oldBoard[k][i-1] == '#'){
              neighborCount++;
            }
            if (oldBoard[k+1][i] == '#' && oldBoard[k][i-1] == '#'){
              neighborCount++;
            }
            if (oldBoard[k][i+1] == '#' && oldBoard[k+1][i] == '#'){
              neighborCount++;
            }
            if (oldBoard[k-1][i] == '#' && oldBoard[k][i+1] == '#'){
              neighborCount++;
            }

            //Assign New Board Values
            if (neighborCount == 1 || neighborCount == 0){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else if (neighborCount == 2 && oldBoard[k][i] == 'X'){
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 3) {
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 4){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else {
              newBoard[k][i] = '-';
              //cout << 0;
            }

              if (newBoard[k][i] == 'X' && oldBoard[k][i] != 'X'){
                boardChanges = true;
              }
              else if (oldBoard[k][i] == 'X' && newBoard[k][i] != 'X'){
                boardChanges = true;
              }
          }
        }
        //cout << endl;
      }
      return newBoard;
    }

};

class doughnutGame{

  private:
    //gameBoard *myBoard = new gameBoard();
    char **oldBoard;
    char **newBoard;
    int width = 0;
    int length = 0;
    bool boardChanges = false;

  public:
    doughnutGame(){
      //nothing
    }

    doughnutGame(gameBoard& passBoard){
      //myBoard->setTo(passBoard);

      width = passBoard.getWidth();
      length = passBoard.getLength();

      oldBoard = passBoard.getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    ~doughnutGame(){
      delete oldBoard;
      delete newBoard;
    }

    void passBoard(gameBoard *passBoard){
      //myBoard->setTo(passBoard);

      width = passBoard->getWidth();
      length = passBoard->getLength();

      oldBoard = passBoard->getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    bool getChanges(){
      return boardChanges;
    }

    char** playGame(){
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          if (oldBoard[k][i] == '#'){
            newBoard[k][i] = '#';
            //cout << "#";
          }
          else{
            int neighborCount = 0;

            //Top Row
            if (oldBoard[k-1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i+1] == 'X'){
              neighborCount++;
            }

            //Middle Row
            if (oldBoard[k][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k][i] == 'X'){
              //do nothing
            }
            if (oldBoard[k][i+1] == 'X'){
              neighborCount++;
            }

            //Bottom Row
            if (oldBoard[k+1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i+1] == 'X'){
              neighborCount++;
            }

            //  doughnut rules //

            //top left (corner)
            if (oldBoard[k-1][i-1] == '#'){
              if (oldBoard[k-1][length-2] == 'X'){
                neighborCount++;
              } else if (oldBoard[width-2][length-2] == 'X'){
                neighborCount++;
              }
            }
            //top Center
            if (oldBoard[k-1][i] == '#'){
              if (oldBoard[width-2][i] == 'X'){
                neighborCount++;
              }
            }
            //top right (corner)
            if (oldBoard[k-1][i+1] == '#'){
              if (oldBoard[k-1][1] == 'X'){
                neighborCount++;
              } else if (oldBoard[width-2][1] == 'X'){
                neighborCount++;
              }
            }

            //Middle Left
            if (oldBoard[k][i-1] == '#'){
              if (oldBoard[k][length-2] == 'X'){
                neighborCount++;
              }
            }
            //Middle Right
            if (oldBoard[k][i+1] == '#'){
              if (oldBoard[k][1] == 'X'){
                neighborCount++;
              }
            }

            //Bottom Left (corner)
            if (oldBoard[k+1][i-1] == '#'){
              if (oldBoard[k+1][length-2] == 'X'){
                neighborCount++;
              } else if (oldBoard[1][length-2] == 'X'){
                neighborCount++;
              }
            }
            //bottom center
            if (oldBoard[k+1][i] == '#'){
              neighborCount++;
            }
            //bottom right (corner)
            if (oldBoard[k+1][i+1] == '#'){
              if (oldBoard[k+1][1] == 'X'){
                neighborCount++;
              } else if (oldBoard[1][1] == 'X'){
                neighborCount++;
              }
            }

            if (neighborCount == 1 || neighborCount == 0){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else if (neighborCount == 2 && oldBoard[k][i] == 'X'){
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 3) {
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 4){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else {
              newBoard[k][i] = '-';
              //cout << 0;
            }

            if (newBoard[k][i] == 'X' && oldBoard[k][i] != 'X'){
              boardChanges = true;
            }
            else if (oldBoard[k][i] == 'X' && newBoard[k][i] != 'X'){
              boardChanges = true;
            }

          }
        }
        //cout << endl;
      }
      return newBoard;
    }

};

class classicGame{

  private:
    //gameBoard *myBoard = new gameBoard();
    char **oldBoard;
    char **newBoard;
    int width = 0;
    int length = 0;
    bool boardChanges = false;

  public:
    classicGame(){
      //nothing
    }

    classicGame(gameBoard& passBoard){
      //myBoard->setTo(passBoard);

      width = passBoard.getWidth();
      length = passBoard.getLength();

      oldBoard = passBoard.getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    ~classicGame(){
      delete oldBoard;
      delete newBoard;
    }

    void passBoard(gameBoard *passBoard){
      //myBoard->setTo(passBoard);

      width = passBoard->getWidth();
      length = passBoard->getLength();

      oldBoard = passBoard->getBoard();

      newBoard = new char*[width];
      for (int i = 0; i < (width); i++) {
        newBoard[i] = new char[length];
      }
    }

    bool getChanges(){
      return boardChanges;
    }

    char** playGame(){
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          if (oldBoard[k][i] == '#'){
            newBoard[k][i] = '#';
            //cout << "#";
          }
          else{
            int neighborCount = 0;

            //Top Row? (Bottom Row?)
            if (oldBoard[k-1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k-1][i+1] == 'X'){
              neighborCount++;
            }

            //Middle Row
            if (oldBoard[k][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k][i] == 'X'){
              //do nothing
            }
            if (oldBoard[k][i+1] == 'X'){
              neighborCount++;
            }

            //Bottom Row (Top Row?)
            if (oldBoard[k+1][i-1] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i] == 'X'){
              neighborCount++;
            }
            if (oldBoard[k+1][i+1] == 'X'){
              neighborCount++;
            }

            if (neighborCount == 1 || neighborCount == 0){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else if (neighborCount == 2 && oldBoard[k][i] == 'X'){
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 3) {
              newBoard[k][i] = 'X';
              //cout << neighborCount;
            } else if (neighborCount == 4){
              newBoard[k][i] = '-';
              //cout << neighborCount;
            } else {
              newBoard[k][i] = '-';
              //cout << 0;
            }

            if (newBoard[k][i] == 'X' && oldBoard[k][i] != 'X'){
              boardChanges = true;
            }
            else if (oldBoard[k][i] == 'X' && newBoard[k][i] != 'X'){
              boardChanges = true;
            }

          }
        }
        //cout << endl;
      }
      return newBoard;
    }

};

class randomBoard{

  private:
    int width = 0;
    int length = 0;
    double density = 0.0;
    char **myPassBoard;

  public:

    randomBoard(){
      generate_Board_Dimensions();
      generateBoard();
    }

    ~randomBoard(){
      delete myPassBoard;
    }

    void generate_Board_Dimensions(){
      string dimensionAnswer = "";
      cout << "How wide would you like the world?: ";
      getline(cin, dimensionAnswer);
      width = stoi(dimensionAnswer);

      cout << "How tall would you like the world?: ";
      getline(cin, dimensionAnswer);
      length = stoi(dimensionAnswer);

      cout << "How dense would you like the world to be?(0.0 - 1.0]: ";
      getline(cin, dimensionAnswer);
      density = stod(dimensionAnswer);
    }

    void generateBoard(){

      char newBoard[width][length];

      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          double densityTest = ((double) rand() / (RAND_MAX));
          if (densityTest <= density){
            newBoard[k][i] = 'X';
          } else{
            newBoard[k][i] = '-';
          }
        }
      }

      cout << '\n';
      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          cout << newBoard[k][i];
        }
        cout << endl;
      }

      cout << "\n===============================================================\n" << endl;

      int newBorderW = width + 2;
      int newBorderL = length + 2;

      char** newBoardTest = new char*[newBorderW];
      for (int i = 0; i < newBorderW; i++) {
        newBoardTest[i] = new char[newBorderL];
      }

      for (int i = 0; i < newBorderL; i++){
        for (int k = 0; k < newBorderW; k++){
          if (i == 0 || i == (newBorderL - 1)){
            newBoardTest[k][i] = '#';
          }
          else if (k == 0 || k == (newBorderW - 1)){
            newBoardTest[k][i] = '#';
          } else{
            newBoardTest[k][i] = newBoard[k-1][i-1];
          }
        }
      }

      myPassBoard = newBoardTest;
    }

    char** getBoard(){
      return myPassBoard;
    }

    int getWidth(){
      return (width + 2);
    }

    int getLength(){
      return (length + 2);
    }

};

class customBoard{

  private:
    string fileName = "";
    int width = 0;
    int length = 0;
    char **myPassBoard;

  public:

    customBoard(){
      generate_Board_Dimensions();
      generateBoard();
    }

    ~customBoard(){
      delete myPassBoard;
    }

    void generate_Board_Dimensions(){
      cout << "What is the name of the custom file?" << endl;
      cout << "File Name: ";
      getline(cin, fileName);
      cout << '\n';

      ifstream customBoardFile(fileName);
      string boardLine;
      int dimensionIterate = 0;
      while(getline(customBoardFile,boardLine) && dimensionIterate != 2){
        dimensionIterate++;
        if (dimensionIterate == 1){
          length = stoi(boardLine);
        }
        else if (dimensionIterate == 2){
          width = stoi(boardLine);
        }
      }
      customBoardFile.close();

      cout << "The Width of the board is: " << width << endl;
      cout << "The Length of the board is " << length << endl;
      cout << '\n';
    }

    void generateBoard(){

      char newBoard[width][length];

      ifstream customBoardFile(fileName);
      string boardLine;
      int lineIterate = 1;

      int i = -1;

      while(getline(customBoardFile,boardLine)){
        if (lineIterate > 2){

          i++; // this moves down one on the length

          // This converts a string to a char array
          int length = boardLine.length();
          char char_array[length + 1];
          strcpy(char_array, boardLine.c_str());

          //put char array into board
          for (int k = 0; k < width; k++){
            newBoard[k][i] = char_array[k];
          }
        }else{
          lineIterate++;
        }
      }


      for (int i = 0; i < length; i++){
        for (int k = 0; k < width; k++){
          cout << newBoard[k][i];
        }
        cout << endl;
      }

      cout << "\n===============================================================\n" << endl;

      int newBorderW = width + 2;
      int newBorderL = length + 2;

      char** newBoardTest = new char*[newBorderW];
      for (int i = 0; i < newBorderW; i++) {
        newBoardTest[i] = new char[newBorderL];
      }

      for (int i = 0; i < newBorderL; i++){
        for (int k = 0; k < newBorderW; k++){
          if (i == 0 || i == (newBorderL - 1)){
            newBoardTest[k][i] = '#';
          }
          else if (k == 0 || k == (newBorderW - 1)){
            newBoardTest[k][i] = '#';
          } else{
            newBoardTest[k][i] = newBoard[k-1][i-1];
          }
        }
      }
      myPassBoard = newBoardTest;
    }

    char** getBoard(){
      return myPassBoard;
    }

    int getWidth(){
      return width + 2;
    }

    int getLength(){
      return length + 2;
    }

};

bool stepPause(bool changes){
  for (int i = 0; i < 100000000; i++){
    //pause
  }

  if (changes == false){
    cout << "Generation has stabilized!" << endl;
    return true;
  } else {
    return false;
  }
}

bool stepEnter(bool changes){
  string enterContinue = "";
  cout << "Press Enter To Continue";
  getline(cin, enterContinue);
  cout << "\n";

  if (changes == false){
    cout << "Generation has stabilized!" << endl;
    return true;
  } else {
    return false;
  }

}

bool stepFile(bool changes){
  if (changes == false){
    cout << "A generation has stabilized and has been outputed to a file!" << endl;
    return true;
  } else {
    return false;
  }
}

int main(int argc, char *argv[] ){

  //string enterButton = "";

  cout << "\n===============================================================\n";
  cout << "          Welcome to Michael's Magical Game of Life!";
  cout << "\n===============================================================\n";
  cout << "\n";

  cout << "Would you like to start with a random board or a custom one?" << endl;
  bool boardTypeBool = false;
  string boardType = "";

  while (boardTypeBool == false){
    cout << "(Random/Custom): ";
    getline(cin, boardType);
    if (boardType == "Random" || boardType == "random"){
      cout << "Generating random board..." << endl;
      boardTypeBool = true;
      boardType = "Random";
    }
    else if (boardType == "Custom" || boardType == "custom"){
      cout << "Prepping for custom board..." << endl;
      boardTypeBool = true;
      boardType = "Custom";
    } else{
      cout << "Please enter Random or Custom!" << endl;
    }
  }

  cout << "\n";
  cout << "What border condition would you prefer?" << endl;
  bool boardBoundaryBool = false;
  string boardBoundaryType = "";

  while (boardBoundaryBool == false){
    cout << "(Classic/Doughnut/Mirror): ";
    getline(cin, boardBoundaryType);
    if (boardBoundaryType == "Classic" || boardBoundaryType == "classic"){
      cout << "Classic Board Selected!" << endl;
      boardBoundaryBool = true;
      boardBoundaryType = "Classic";
    }
    else if (boardBoundaryType == "Doughnut" || boardBoundaryType == "doughnut"){
      cout << "Classic Board Selected!" << endl;
      boardBoundaryBool = true;
      boardBoundaryType = "Doughnut";
    }
    else if (boardBoundaryType == "Mirror" || boardBoundaryType == "mirror"){
      cout << "Mirror Board Selected!" << endl;
      boardBoundaryBool = true;
      boardBoundaryType = "Mirror";
    }else{
      cout << "Please enter Classic, Doughnut, or Mirror!" << endl;
    }
  }

  cout << "\n";
  cout << "How would you like to view the generations?" << endl;
  bool boardGenerationBool = false;
  string boardGenerationType = "";

  while (boardGenerationBool == false){
    cout << "(Pause/Enter/File): ";
    getline(cin, boardGenerationType);
    if (boardGenerationType == "Pause" || boardGenerationType == "pause"){
      cout << "Pause mode Selected!" << endl;
      boardGenerationBool = true;
      boardGenerationType = "Pause";
    }
    else if (boardGenerationType == "Enter" || boardGenerationType == "enter"){
      cout << "Enter mode Selected!" << endl;
      boardGenerationBool = true;
      boardGenerationType = "Enter";
    }
    else if (boardGenerationType == "File" || boardGenerationType == "file"){
      cout << "File mode Selected!" << endl;
      boardGenerationBool = true;
      boardGenerationType = "File";
    }else{
      cout << "Please enter Pause, Enter, or File!" << endl;
    }
  }

  cout << "\n===============================================================\n";
  cout << "\n";

  int width = 0;
  int length = 0;
  gameBoard *myBoard = new gameBoard();

  if (boardType == "Custom" || boardType == "custom"){
    customBoard *genBoard = new customBoard();
    width = genBoard->getWidth();
    length = genBoard->getLength();

    char** newBoardPass = new char*[width];
    for (int i = 0; i < (width); i++) {
      newBoardPass[i] = new char[length];
    }

    newBoardPass = genBoard->getBoard();
    myBoard->passInfo(newBoardPass, width, length);
    myBoard->cleanBoard();
  }
  else if (boardType == "Random" || boardType == "random"){
    randomBoard *genBoard = new randomBoard();
    width = genBoard->getWidth();
    length = genBoard->getLength();

    char** newBoardPass = new char*[width];
    for (int i = 0; i < (width); i++) {
      newBoardPass[i] = new char[length];
    }

    newBoardPass = genBoard->getBoard();
    myBoard->passInfo(newBoardPass, width, length);
  }

  bool gameOver = false;
  if (boardGenerationType == "Pause" || boardGenerationType == "pause" || boardGenerationType == "Enter" || boardGenerationType == "enter"){
  myBoard->printBoard();
  } else {
  myBoard->fileOutput();
  }

  if (boardGenerationType == "Pause" || boardGenerationType == "pause"){
    gameOver = stepPause(true);
  }
  else if (boardGenerationType == "Enter" || boardGenerationType == "enter"){
      gameOver = stepEnter(true);
  }
  else if (boardGenerationType == "File" || boardGenerationType == "file"){
    gameOver = stepFile(true); //next fix
  }


  if (boardBoundaryType == "Classic" || boardBoundaryType == "classic"){
    while (gameOver == false){
      classicGame *myClassic = new classicGame();
      myClassic->passBoard(myBoard);
      myBoard->setBoard(myClassic->playGame());
      myBoard->cleanBoard();
      if (boardGenerationType == "Pause" || boardGenerationType == "pause" || boardGenerationType == "Enter" || boardGenerationType == "enter"){
      myBoard->printBoard();
      }
      bool changes = myClassic->getChanges();

      if (boardGenerationType == "Pause" || boardGenerationType == "pause"){
        gameOver = stepPause(changes);
      }
      else if (boardGenerationType == "Enter" || boardGenerationType == "enter"){
          gameOver = stepEnter(changes);
      }
      else if (boardGenerationType == "File" || boardGenerationType == "file"){
        myBoard->fileOutputAppend();
        gameOver = stepFile(changes);
      }

    }
  }

  if (boardBoundaryType == "Mirror" || boardBoundaryType == "mirror"){
    while (gameOver == false){
      mirrorGame *myMirror = new mirrorGame();
      myMirror->passBoard(myBoard);
      myBoard->setBoard(myMirror->playGame());
      myBoard->cleanBoard();
      if (boardGenerationType == "Pause" || boardGenerationType == "pause" || boardGenerationType == "Enter" || boardGenerationType == "enter"){
      myBoard->printBoard();
      }
      bool changes = myMirror->getChanges();

      if (boardGenerationType == "Pause" || boardGenerationType == "pause"){
        gameOver = stepPause(changes);
      }
      else if (boardGenerationType == "Enter" || boardGenerationType == "enter"){
          gameOver = stepEnter(changes);
      }
      else if (boardGenerationType == "File" || boardGenerationType == "file"){
        myBoard->fileOutputAppend();
        gameOver = stepFile(changes);
      }

    }
  }

  if (boardBoundaryType == "Doughnut" || boardBoundaryType == "doughnut"){
    while (gameOver == false){
      doughnutGame *myDoughnut = new doughnutGame();
      myDoughnut->passBoard(myBoard);
      myBoard->setBoard(myDoughnut->playGame());
      myBoard->cleanBoard();
      if (boardGenerationType == "Pause" || boardGenerationType == "pause" || boardGenerationType == "Enter" || boardGenerationType == "enter"){
      myBoard->printBoard();
      }
      bool changes = myDoughnut->getChanges();

      if (boardGenerationType == "Pause" || boardGenerationType == "pause"){
        gameOver = stepPause(changes);
      }
      else if (boardGenerationType == "Enter" || boardGenerationType == "enter"){
          gameOver = stepEnter(changes);
      }
      else if (boardGenerationType == "File" || boardGenerationType == "file"){
        myBoard->fileOutputAppend();
        gameOver = stepFile(changes);
      }

    }
  }

  return 0;
}
