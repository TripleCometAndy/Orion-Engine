#include "uGrid.h"
//
uGrid::uGrid(int w, int h) {

	width = w;
	height = h;

	uniformGrid = new vector<hitbox>*[width];

	for (int i = 0; i < width; i++) {
		uniformGrid[i] = new vector<hitbox>[height];
	}

	clearGrid();

}

uGrid::~uGrid() {

	for (int i = 0; i < width; i++) {

		for (int j = 0; j < height; j++) {

			uniformGrid[i][j].swap(uniformGrid[i][j]);


		}
	}

	for (int i = 0; i < width; i++) {

		delete[] uniformGrid[i];

	}

	delete[] uniformGrid;



}


void uGrid::clearGrid() {

	for (int i = 0; i < width; i++) {

		for (int j = 0; j < height; j++) {

			uniformGrid[i][j].clear();

		}
	}

}

void uGrid::findAndDeleteHitbox(hitbox hitboxToDelete, int x, int y) {

	//cout << "X: " << x << endl;
	//cout << "Y: " << y << endl;


	int numElements = uniformGrid[x][y].size();

	if (numElements > 0) {


		hitbox * p = uniformGrid[x][y].data();



		//this grows way too high for some reason. maybe I'm not deleting the hitboxes for some reason?//


		//cout << "Num Elements: " << numElements << endl;

		for (int i = 0; i < numElements; i++) {


			if (hitboxToDelete.name.compare((*p).name) == 0) {

				uniformGrid[x][y].erase(uniformGrid[x][y].begin() + i);

				return;


			}

			p++;

		}
	}

	//hitbox wasn't here//


}

void uGrid::deleteHitbox_xPyN(hitbox hitboxToDelete, int xIgnore, int yIgnore) {

	//cout << "Iguana" << endl;
//  cout << "X Ignore = " << xIgnore << endl;
	//cout << "Y Ignore = " << yIgnore << endl;


	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore && j < yIgnore) {

				//ignore//
				//  cout << "Ignored: x = " << i << ", y = " << j << endl;


			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xNyN(hitbox hitboxToDelete, int xIgnore, int yIgnore) {

	//cout << "Juice" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore && j < yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xPyP(hitbox hitboxToDelete, int xIgnore, int yIgnore) {

	//cout << "Kale" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;
	//cout << "X : " << x << endl;
	//cout << "Y: " << y << endl;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore && j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xNyP(hitbox hitboxToDelete, int xIgnore, int yIgnore) {

	//cout << "Lizard" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;


	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore && j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xPyZ(hitbox hitboxToDelete, int xIgnore) {

	//cout << "Mango" << endl;
	//cout << "xIgnore: " << xIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;


	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xNyZ(hitbox hitboxToDelete, int xIgnore) {

	//cout << "Nutmeg" << endl;
	//cout << "xIgnore: " << xIgnore << endl;


	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xZyN(hitbox hitboxToDelete, int yIgnore) {

	//cout << "Octopus" << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (j < yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::deleteHitbox_xZyP(hitbox hitboxToDelete, int yIgnore) {

	//cout << "Porcupine" << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxToDelete.pastLeft;
	int y = hitboxToDelete.pastTop;
	int width = hitboxToDelete.pastRight - x;
	int height = hitboxToDelete.pastBottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Deleting: x = " << i << ", y = " << j << endl;
				findAndDeleteHitbox(hitboxToDelete, i, j);
			}

		}

	}

}

void uGrid::addReference_xPyN(hitbox hitboxAdd, int xIgnore, int yIgnore) {

	//cout << "Quartz" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore && j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xNyN(hitbox hitboxAdd, int xIgnore, int yIgnore) {

	//cout << "Rolo" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore && j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xPyP(hitbox hitboxAdd, int xIgnore, int yIgnore) {

	//cout << "Timbre" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore && j < yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xNyP(hitbox hitboxAdd, int xIgnore, int yIgnore) {

	//cout << "Umbrella" << endl;
	//cout << "xIgnore: " << xIgnore << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore && j < yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xPyZ(hitbox hitboxAdd, int xIgnore) {

	//cout << "Deer" << endl;
	//cout << "xIgnore: " << xIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i < xIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xNyZ(hitbox hitboxAdd, int xIgnore) {

	//cout << "Snek" << endl;
	//cout << "xIgnore: " << xIgnore << endl;


	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (i >= xIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xZyN(hitbox hitboxAdd, int yIgnore) {

	//cout << "Seinfeld" << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (j >= yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}

void uGrid::addReference_xZyP(hitbox hitboxAdd, int yIgnore) {

	//cout << "Ace" << endl;
	//cout << "yIgnore: " << yIgnore << endl;

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			if (j < yIgnore) {

				//ignore//
				//cout << "Ignored: x = " << i << ", y = " << j << endl;

			}
			else {
				//cout << "Adding: x = " << i << ", y = " << j << endl;
				uniformGrid[i][j].push_back(hitboxAdd);
			}
		}

	}


}



void uGrid::addReferenceNoIgnore(hitbox hitboxAdd) {

	int x = hitboxAdd.left;
	int y = hitboxAdd.top;
	int width = hitboxAdd.right - x;
	int height = hitboxAdd.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;
	//cout << "---------------------------------------" << endl;
	//cout << "Hitbox: " << hitboxAdd.name << endl;

	for (int i = x; i < xPlusWidth; i++) {

		for (int j = y; j < yPlusHeight; j++) {

			//cout << "x: " << i << endl;
			//cout << "y: " << j << endl;
			uniformGrid[i][j].push_back(hitboxAdd);

		}

	}

	//cout << "---------------------------------------" << endl;
}



void uGrid::update(vector<hitbox> hitboxes) {

	//cycle through hitboxes, deleting them from the grid and adding their updated position//
	int numHitboxes = hitboxes.size();
	hitbox * p = hitboxes.data();

	int x5 = 0;
	int y5 = 0;
	int x6 = 0;
	int y6 = 0;
	bool xMPositive;
	bool xMNegative;
	bool xMZero;
	bool yMPositive;
	bool yMNegative;
	bool yMZero;


	for (int i = 0; i < numHitboxes; i++) {

		x5 = max((*p).pastLeft, (*p).left);
		y5 = max((*p).pastTop, (*p).top);
		x6 = min((*p).pastRight, (*p).right);
		y6 = min((*p).pastBottom, (*p).bottom);


		if ((*p).pastRight > (*p).right) {

			xMNegative = true;
			xMPositive = false;
			xMZero = false;

		}
		else if ((*p).pastRight < (*p).right) {

			xMPositive = true;
			xMNegative = false;
			xMZero = false;

		}
		else {

			xMZero = true;
			xMNegative = false;
			xMPositive = false;

		}

		if ((*p).pastTop > (*p).top) {

			yMNegative = true;
			yMPositive = false;
			yMZero = false;

		}
		else if ((*p).pastTop < (*p).top) {

			yMPositive = true;
			yMNegative = false;
			yMZero = false;


		}
		else {

			yMZero = true;
			yMPositive = false;
			yMNegative = false;

		}



		if (xMZero && yMZero) {


			//hitbox didnt move//
			//  cout << "Hitbox didnt move" << endl;



		}
		else {

			if (xMPositive && yMNegative) {

				deleteHitbox_xPyN(*p, x5, y6);
				addReference_xPyN(*p, x6, y5);
				//cout << "Apple" << endl;

			}
			else if (xMNegative && yMNegative) {

				deleteHitbox_xNyN(*p, x6, y6);
				addReference_xNyN(*p, x5, y5);
				//cout << "Banana" << endl;

			}
			else if (xMPositive && yMPositive) {

				deleteHitbox_xPyP(*p, x5, y5);
				addReference_xPyP(*p, x6, y6);
				//cout << "Carror" << endl;

			}
			else if (xMNegative && yMPositive) {

				deleteHitbox_xNyP(*p, x6, y5);
				addReference_xNyP(*p, x5, y6);
				//cout << "Dinner" << endl;

			}
			else if (xMPositive && yMZero) {

				deleteHitbox_xPyZ(*p, x5);
				addReference_xPyZ(*p, x6);
				//cout << "Eggplant" << endl;

			}
			else if (xMNegative && yMZero) {

				deleteHitbox_xNyZ(*p, x6);
				addReference_xNyZ(*p, x5);
				//cout << "Fireworks" << endl;

			}
			else if (xMZero && yMNegative) {

				deleteHitbox_xZyN(*p, y6);
				addReference_xZyN(*p, y5);
				//cout << "Grapeape" << endl;

			}
			else if (xMZero && yMPositive) {

				deleteHitbox_xZyP(*p, y5);
				addReference_xZyP(*p, y6);
				//cout << "Hamburger" << endl;

			}



		}

		p++;

	}

}

bool findNameThreadOne(int id, int x, int y, vector<hitbox> ** &uniformGrid, int width, int height, int xPlusWidth, int yPlusHeight, int ID) {
	//cout << "IN THREAD ONE" << endl;
	hitbox * p;

	for (int i = y; i < yPlusHeight; i += 4) {

		for (int j = x; j < xPlusWidth; j += 4) {

			int vSize = uniformGrid[j][i].size();

			p = uniformGrid[j][i].data();

			for (int k = 0; k < vSize; k++) {

				if (p->ID == ID) {

					return true;


				}

				p++;

			}


		}


	}

	return false;

}

bool findNameThreadTwo(int id, int x, int y, vector<hitbox> ** &uniformGrid, int width, int height, int xPlusWidth, int yPlusHeight, int ID) {
	//cout << "IN THREAD TWO" << endl;
	hitbox * p;

	for (int i = y; i < yPlusHeight; i += 4) {

		for (int j = x; j < xPlusWidth; j += 4) {

			int vSize = uniformGrid[j][i].size();

			p = uniformGrid[j][i].data();

			for (int k = 0; k < vSize; k++) {

				if (p->ID == ID) {

					return true;


				}

				p++;

			}


		}


	}

	return false;

}

bool findNameThreadThree(int id, int x, int y, vector<hitbox> ** &uniformGrid, int width, int height, int xPlusWidth, int yPlusHeight, int ID) {
	//cout << "IN THREAD THREE" << endl;
	hitbox * p;

	for (int i = y; i < yPlusHeight; i += 4) {

		for (int j = x; j < xPlusWidth; j += 4) {

			int vSize = uniformGrid[j][i].size();

			p = uniformGrid[j][i].data();

			for (int k = 0; k < vSize; k++) {

				if (p->ID == ID) {

					return true;


				}

				p++;

			}


		}


	}

	return false;

}

bool findNameThreadFour(int id, int x, int y, vector<hitbox> ** &uniformGrid, int width, int height, int xPlusWidth, int yPlusHeight, int ID) {

	hitbox * p;
	//cout << "IN THREAD FOUR" << endl;

	for (int i = y; i < yPlusHeight; i += 4) {

		for (int j = x; j < xPlusWidth; j += 4) {

			int vSize = uniformGrid[j][i].size();

			p = uniformGrid[j][i].data();

			for (int k = 0; k < vSize; k++) {

				if (p->ID == ID) {

					return true;


				}

				p++;

			}


		}


	}

	return false;

}

bool uGrid::findName(hitbox & source, int ID, thread_pool * pool) {

	int x = source.left;
	int y = source.top;
	int width = source.right - x;
	int height = source.bottom - y;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;



	std::future<bool> qw1 = pool->push(findNameThreadOne, x, y, uniformGrid, width, height, xPlusWidth, yPlusHeight, ID);
	std::future<bool> qw2 = pool->push(findNameThreadTwo, x + 1, y + 1, uniformGrid, width, height, xPlusWidth, yPlusHeight, ID);
	std::future<bool> qw3 = pool->push(findNameThreadThree, x + 2, y + 2, uniformGrid, width, height, xPlusWidth, yPlusHeight, ID);
	std::future<bool> qw4 = pool->push(findNameThreadFour, x + 3, y + 3, uniformGrid, width, height, xPlusWidth, yPlusHeight, ID);

	if (qw1.get() || qw2.get() || qw3.get() || qw4.get()) {

		return true;

	}
	else {

		return false;
	}





}

bool uGrid::findNameSingleThread(hitbox & source, int ID) {


	cout << "Bottom" << endl;
	int x = source.left;
	int y = source.top;
	int width = source.right - x;
	int height = source.bottom - y;
	hitbox * p;
	int xPlusWidth = x + width;
	int yPlusHeight = y + height;

	for (int i = y; i < yPlusHeight; i++) {

		for (int j = x; j < xPlusWidth; j++) {

			int vSize = uniformGrid[j][i].size();
			p = uniformGrid[j][i].data();

			for (int k = 0; k < vSize; k++) {

				if (p->ID == ID) {

					return true;


				}

				p++;

			}


		}


	}

	return false;


}



void uGrid::destruct() {

	for (int i = 0; i < width; i++) {

		for (int j = 0; j < height; j++) {

			uniformGrid[i][j].swap(uniformGrid[i][j]);


		}
	}

	for (int i = 0; i < width; i++) {

		delete[] uniformGrid[i];

	}

	delete[] uniformGrid;


}

void uGrid::printGridInfo() {

	hitbox * p;

	cout << "Uniform Grid Data" << endl;
	cout << "=================" << endl;


	for (int i = 0; i < 45; i++) {

		for (int j = 0; j < 45; j++) {

			cout << "///////////////" << endl;
			cout << "x = " << i << " y = " << j << endl;
			cout << "Number of Hitboxes: " << uniformGrid[i][j].size() << endl;
			cout << "---------------" << endl;

			p = uniformGrid[i][j].data();

			for (size_t k = 0; k < uniformGrid[i][j].size(); k++) {

				cout << p->name << endl;
				p++;



			}

		}

	}


}

void uGrid::getName(hitbox source, string name, vector<hitbox> * retrieve) {

	//retrieve->clear();
	//delete retrieve;

	//retrieve = new vector<hitbox>;

	int x = source.left;
	int y = source.top;
	int width = source.right - x;
	int height = source.bottom - y;
	hitbox * p;
	int vSize = 0;


	for (int i = x; i < (x + width); i++) {

		for (int j = y; j < (y + height); j++) {

			vSize = uniformGrid[i][j].size();
			p = uniformGrid[i][j].data();

			for (int k = 0; k < vSize; k++) {

				if (!(p->name.compare(name))) {

					//if not duplicate, add to vector//
					if (!duplicateParentName(retrieve, p->parentName)) {

						//cout << "Pushed: " << p->parentName << endl;
						retrieve->push_back(*p);



					}

				}

				p++;

			}


		}


	}

}

int uGrid::numName(hitbox source, string name) {

	//retrieve->clear();
	//delete retrieve;

	int count = 0;

	vector<hitbox> * retrieve = new vector<hitbox>;

	int x = source.left;
	int y = source.top;
	int width = source.right - x;
	int height = source.bottom - y;
	hitbox * p;
	int vSize = 0;


	for (int i = x; i < (x + width); i++) {

		for (int j = y; j < (y + height); j++) {

			vSize = uniformGrid[i][j].size();
			p = uniformGrid[i][j].data();

			for (int k = 0; k < vSize; k++) {

				if (!(p->name.compare(name))) {

					//if not duplicate, add to vector//
					if (!duplicateParentName(retrieve, p->parentName)) {

						//cout << "Pushed: " << p->parentName << endl;
						retrieve->push_back(*p);
						count++;


					}

				}

				p++;

			}


		}


	}

	return count;
}

bool duplicateParentName(vector<hitbox> * retrieve, string parentName) {

	int size = retrieve->size();
	int count = 0;
	hitbox * p = retrieve->data();

	for (int i = 0; i < size; i++) {

		if (!(p->parentName.compare(parentName))) {

			return true;


		}

		p++;
	}

	return false;
}


string uGrid::getGridInfo() {

	string info;
	hitbox * p;

	info += "Uniform Grid Data";
	info += "=================";


	for (int i = 0; i < 100; i++) {

		for (int j = 0; j < 100; j++) {

			info += "===============";
			info += "_x = ";
			info += to_string(i);
			info += "_ y = ";
			info += to_string(j);
			info += "_Number of Hitboxes: ";
			info += to_string(uniformGrid[i][j].size());
			info += "_---------------_";

			p = uniformGrid[i][j].data();

			for (size_t k = 0; k < uniformGrid[i][j].size(); k++) {

				info += p->name;
				info += "_";
				p++;



			}

		}

	}

	return info;
}

