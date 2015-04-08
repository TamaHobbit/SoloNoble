/* Contract:
TCallBackHandler must implement:
bool ownPiece(std::pair<int,int> mouseTile);
void select(std::pair<int,int> mouseTile);
void deselect();
bool validMove(std::pair<int,int> from, std::pair<int,int> to);
void makeMove(std::pair<int,int> from, std::pair<int,int> to);
*/

template<class TCallBackHandler>
class TwoClickOrDrag { // that is the question
public:

	TwoClickOrDrag(TCallBackHandler & ch) : _callbackHandler(ch) {
	}

	bool HasSelection(){
		return pieceSelected;
	}

	void MouseDown(std::pair<int,int> mouseTile){
		if( _callbackHandler.ownPiece(mouseTile) ){
			if( pieceSelected ){
				_callbackHandler.deselect();
				if( selection != mouseTile ){
					_callbackHandler.select(mouseTile);
					selection = mouseTile;
				}
			} else {
				_callbackHandler.select(mouseTile);
				selection = mouseTile;
			}
		} else if( pieceSelected ){
			TryMove(selection, mouseTile);
			pieceSelected = false;
			_callbackHandler.deselect();
		}

	}	

	void MouseUp(std::pair<int,int> mouseTile){
		if( pieceSelected ){
			if( selection == mouseTile ){
				return;
			}
			if( TryMove(selection, mouseTile) ){
				_callbackHandler.deselect();
			}
		} else {
			TryMove(selection, mouseTile);
		}
	}

private:
	TCallBackHandler & _callbackHandler;
	bool pieceSelected { false };
	std::pair<int,int> selection;

	bool TryMove(std::pair<int,int> from, std::pair<int,int> to){
		if( _callbackHandler.validMove(from, to) ){
			_callbackHandler.makeMove(from, to);
			return true;
		}
		return false;
	}

};