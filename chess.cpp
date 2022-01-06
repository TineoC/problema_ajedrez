#include <iostream>
#include <stdlib.h>

/*
    Fecha de Inicio: 4 - 11 - 2021

    Fecha de Entrega: 6 - 11 - 2021

    Grupo #02

    * Christopher Tineo
    * Camilo Maria
    * Lya Sanchez
    * Sahira Tejada
    * Taiyab Gillani
    * José Fernandez

    * Instrucciones

    Realizar un programa C++ que dado la ubicación de 2 torres enemigas y una Reina, se produzca una salida con todas las jugadas posibles de la reina donde puede y no ser eliminada.
*/

class GamePiece
{
	public:
		GamePiece(char PieceColor) : mPieceColor(PieceColor) {}
		~GamePiece() {}
			virtual char GetPiece() = 0;
			char GetColor() {
				return mPieceColor;
		}
		bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
			GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
			if ((qpDest == 0) || (mPieceColor != qpDest->GetColor())) {
				return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, GameBoard);
			}
			return false;
		}
	private:
		virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) = 0;
		char mPieceColor;
};

class RookPiece : public GamePiece
{
	public:
		RookPiece(char PieceColor) : GamePiece(PieceColor) {}
		~RookPiece() {}
	private:
		virtual char GetPiece() {
			return 'R';
		}
		bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
			if (iSrcRow == iDestRow) {
				// Make sure that all invervening squares are empty
				int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
				for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
					if (GameBoard[iSrcRow][iCheckCol] != 0) {
						return false;
					}
				}
				return true;
			} else if (iDestCol == iSrcCol) {
				// Make sure that all invervening squares are empty
				int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
				for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
					if (GameBoard[iCheckRow][iSrcCol] != 0) {
						return false;
					}
				}
				return true;
			}
			return false;
		}
};

class QueenPiece : public GamePiece
{
	public:
		QueenPiece(char PieceColor) : GamePiece(PieceColor) {}
		~QueenPiece() {}
	private:
		virtual char GetPiece() {
			return 'Q';
		}
		bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
			if (iSrcRow == iDestRow) {
				// Make sure that all invervening squares are empty
				int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
				for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
					if (GameBoard[iSrcRow][iCheckCol] != 0) {
						return false;
					}
				}
				return true;
			} else if (iDestCol == iSrcCol) {
				// Make sure that all invervening squares are empty
				int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
				for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
					if (GameBoard[iCheckRow][iSrcCol] != 0) {
						return false;
					}
				}
				return true;
			} else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
				// Make sure that all invervening squares are empty
				int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
				int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
				int iCheckRow;
				int iCheckCol;
				for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
					iCheckRow !=  iDestRow;
					iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
				{
					if (GameBoard[iCheckRow][iCheckCol] != 0) {
						return false;
					}
				}
				return true;
			}
			return false;
		}
};

class CBoard
{
	public:
		CBoard() {
			for (int iRow = 0; iRow < 8; ++iRow) {
				for (int iCol = 0; iCol < 8; ++iCol) {
					MainGameBoard[iRow][iCol] = 0;
				}
			}
			// Allocate and place black pieces
			MainGameBoard[7][0] = new RookPiece('B');
			MainGameBoard[7][4] = new QueenPiece('B');
			MainGameBoard[7][7] = new RookPiece('B');
			// Allocate and place white pieces
			MainGameBoard[0][0] = new RookPiece('W');
			MainGameBoard[0][4] = new QueenPiece('W');
			MainGameBoard[0][7] = new RookPiece('W');
		}
		~CBoard() {
			for (int iRow = 0; iRow < 8; ++iRow) {
				for (int iCol = 0; iCol < 8; ++iCol) {
					delete MainGameBoard[iRow][iCol];
					MainGameBoard[iRow][iCol] = 0;
				}
			}
		}

		void Print() {
			using namespace std;
			const int kiSquareWidth = 4;
			const int kiSquareHeight = 3;
			for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
				int iSquareRow = iRow/kiSquareHeight;
				// Print side border with numbering
				if (iRow % 3 == 1) {
					cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
				} else {
					cout << "---";
				}
				// Print the chess board
				for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
					int iSquareCol = iCol/kiSquareWidth;
					if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && MainGameBoard[7-iSquareRow][iSquareCol] != 0) {
						if ((iCol % 4) == 1) {
							cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetColor();
						} else {
							cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetPiece();
						}
					} else {
						if ((iSquareRow + iSquareCol) % 2 == 1) {
							cout << '*';
						} else {
							cout << ' ';
						}
					}
				}
				cout << endl;
			}
			// Print the bottom border with numbers
			for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
				if (iRow % 3 == 1) {
					cout << "---";
					for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
						int iSquareCol = iCol/kiSquareWidth;
						if ((iCol % 4) == 1) {
							cout << (iSquareCol + 1);
						} else {
							cout << '-';
						}
					}
					cout << endl;
				} else {
					for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
						cout << '-';
					}
					cout << endl;
				}
			}
		}

		bool IsInCheck(char PieceColor) {
			// Find the king
			int iKingRow;
			int iKingCol;
			for (int iRow = 0; iRow < 8; ++iRow) {
				for (int iCol = 0; iCol < 8; ++iCol) {
					if (MainGameBoard[iRow][iCol] != 0) {
						if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
							if (MainGameBoard[iRow][iCol]->GetPiece() == 'K') {
								iKingRow = iRow;
								iKingCol = iCol;
							}
						}
					}
				}
			}
			// Run through the opponent's pieces and see if any can take the king
			for (int iRow = 0; iRow < 8; ++iRow) {
				for (int iCol = 0; iCol < 8; ++iCol) {
					if (MainGameBoard[iRow][iCol] != 0) {
						if (MainGameBoard[iRow][iCol]->GetColor() != PieceColor) {
							if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, MainGameBoard)) {
								return true;
							}
						}
					}
				}
			}

			return false;
		}

		bool CanMove(char PieceColor) {
			// Run through all pieces
			for (int iRow = 0; iRow < 8; ++iRow) {
				for (int iCol = 0; iCol < 8; ++iCol) {
					if (MainGameBoard[iRow][iCol] != 0) {
						// If it is a piece of the current player, see if it has a legal move
						if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
							for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
								for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
									if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, MainGameBoard)) {
										// Make move and check whether king is in check
										GamePiece* qpTemp                   = MainGameBoard[iMoveRow][iMoveCol];
										MainGameBoard[iMoveRow][iMoveCol]   = MainGameBoard[iRow][iCol];
										MainGameBoard[iRow][iCol]           = 0;
										bool bCanMove = !IsInCheck(PieceColor);
										// Undo the move
										MainGameBoard[iRow][iCol]           = MainGameBoard[iMoveRow][iMoveCol];
										MainGameBoard[iMoveRow][iMoveCol]   = qpTemp;
										if (bCanMove) {
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
			return false;
		}

		GamePiece* MainGameBoard[8][8];
};

class ChessBoard
{
public:
    ChessBoard() : mcPlayerTurn('W') {}
    ~ChessBoard() {}

    void Start() {
        do {
            GetNextMove(mqGameBoard.MainGameBoard);
            AlternateTurn();
        } while (!IsGameOver());
        mqGameBoard.Print();
    }

    void GetNextMove(GamePiece* GameBoard[8][8]) {
        using namespace std;
        bool bValidMove     = false;
        do {
            system("cls");

			cout << "Bienvenido al proyecto de Ajedrez de IDS344" << endl;

			cout << "\nNomenclatura: " << endl;

            cout<<"-  * = Cuadro blanco"<<endl;
            cout<<"-  Espacio en blanco = Cuadro negro"<<endl;
            cout<<"-  TN = Torre negra"<<endl;
            cout<<"-  RB = Reina blanca"<<endl;

            cout<<"\nPara moverse :"<<endl;
			cout<<"  1ro. Escribe la fila y columna de la ficha que deseas mover."<<endl;
			cout<<"  2do. Escribe la fila y columna de hacia donde la deseas mover."<<endl;

			char opcion;

			cout << "\nListo? (y/n): ";
			cin >> opcion;

			if(opcion == 'y') {
				system("cls");
				mqGameBoard.Print();
				}
			else return;
            

            // Get input and convert to coordinates
            cout << "Escribe la posicion de la primera torre: ";
            int iStartMove;
            cin >> iStartMove;
            int iStartRow = (iStartMove / 10) - 1;
            int iStartCol = (iStartMove % 10) - 1;

            cout << "To: ";
            int iEndMove;
            cin >> iEndMove;
            int iEndRow = (iEndMove / 10) - 1;
            int iEndCol = (iEndMove % 10) - 1;

            // Check that the indices are in range
            // and that the source and destination are different
            if ((iStartRow >= 0 && iStartRow <= 7) &&
                (iStartCol >= 0 && iStartCol <= 7) &&
                (iEndRow >= 0 && iEndRow <= 7) &&
                (iEndCol >= 0 && iEndCol <= 7)) {
                // Additional checks in here
                GamePiece* qpCurrPiece = GameBoard[iStartRow][iStartCol];
                // Check that the piece is the correct color
                if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, GameBoard)) {
                        // Make the move
                        GamePiece* qpTemp                   = GameBoard[iEndRow][iEndCol];
                        GameBoard[iEndRow][iEndCol]     = GameBoard[iStartRow][iStartCol];
                        GameBoard[iStartRow][iStartCol] = 0;
                        // Make sure that the current player is not in check
                        if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
                            delete qpTemp;
                            bValidMove = true;
                        } else { // Undo the last move
                            GameBoard[iStartRow][iStartCol] = GameBoard[iEndRow][iEndCol];
                            GameBoard[iEndRow][iEndCol]     = qpTemp;
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "Invalid Move!" << endl;
            }
        } while (!bValidMove);
    }

    void AlternateTurn() {
        mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
    }

    bool IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove(false);
        bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
        if (!bCanMove) {
            if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
            } else {
                std::cout << "Stalemate!" << std::endl;
            }
        }
        return !bCanMove;
    }
private:
    CBoard mqGameBoard;
    char mcPlayerTurn;
};

int main() {
    ChessBoard qGame;
    qGame.Start();
    return 0;
}
