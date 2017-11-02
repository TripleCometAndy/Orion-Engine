#include <vector>
#include <string>
#include <iostream>
#include <functional>
#ifndef _THREADPOOL
#define _THREADPOOL
#include "../../threadpool/threadPool/threadPool.h"
#endif


#ifndef _HITBOX
#define _HITBOX
#include "../../hitbox/hitbox/hitbox.h"
#endif

using namespace std;

using namespace ctpl;

class uGrid {

private:

	int width;
	int height;

	vector<hitbox> ** uniformGrid;

public:

	uGrid(int w, int h);
	~uGrid();
	void clearGrid();
	void findAndDeleteHitbox(hitbox hitboxToDelete, int x, int y);

	void deleteHitbox_xPyN(hitbox hitboxToDelete, int xIgnore, int yIgnore);
	void deleteHitbox_xNyN(hitbox hitboxToDelete, int xIgnore, int yIgnore);
	void deleteHitbox_xPyP(hitbox hitboxToDelete, int xIgnore, int yIgnore);
	void deleteHitbox_xNyP(hitbox hitboxToDelete, int xIgnore, int yIgnore);
	void deleteHitbox_xPyZ(hitbox hitboxToDelete, int xIgnore);
	void deleteHitbox_xNyZ(hitbox hitboxToDelete, int xIgnore);
	void deleteHitbox_xZyN(hitbox hitboxToDelete, int yIgnore);
	void deleteHitbox_xZyP(hitbox hitboxToDelete, int yIgnore);

	void addReference_xPyN(hitbox hitboxAdd, int xIgnore, int yIgnore);
	void addReference_xNyN(hitbox hitboxAdd, int xIgnore, int yIgnore);
	void addReference_xPyP(hitbox hitboxAdd, int xIgnore, int yIgnore);
	void addReference_xNyP(hitbox hitboxAdd, int xIgnore, int yIgnore);
	void addReference_xPyZ(hitbox hitboxAdd, int xIgnore);
	void addReference_xNyZ(hitbox hitboxAdd, int xIgnore);
	void addReference_xZyN(hitbox hitboxAdd, int yIgnore);
	void addReference_xZyP(hitbox hitboxAdd, int yIgnore);
//
	void addReferenceNoIgnore(hitbox hitboxAdd);

	void update(vector<hitbox> hitboxes);
	bool findName(hitbox & source, int ID, thread_pool * pool);
	bool findNameSingleThread(hitbox & source, int ID);
	void printGridInfo();
	void destruct();
	void getName(hitbox source, string name, vector<hitbox> * retrieve);
	int numName(hitbox source, string name);
	string getGridInfo();



};

bool duplicateParentName(vector<hitbox> * retrieve, string parentName);

