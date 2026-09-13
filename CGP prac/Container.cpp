#include "Container.h"

void Container::addchild(Button b) {

	int btnleft = b.getrect().left + rect.left;
	int btntop = b.getrect().top + rect.top;
	int btnright = b.getrect().right + btnleft;
	int btnbottom = b.getrect().bottom + btntop;

	b.setbtnrect(RECT{ btnleft,btntop,btnright,btnbottom });
	b.setposition(btnleft,btntop);

	int txtleft = b.gettxtrect().left + btnleft;
	int txttop = b.gettxtrect().top + btntop;
	int	txtright = btnright - b.gettxtrect().right;
	int	txtbottom = btnbottom - b.gettxtrect().bottom;

	b.setbtntextrect(RECT{ txtleft,txttop,txtright,txtbottom });

	children.push_back(b);
}