#include "Spring.h"
#include <vector>

class Model
{
public:
	std::vector<Mass*> objects;

	virtual void init();
	virtual void render();
	virtual void update(float dt);
};

class Model1 : public Model
{
	void init() override;
};
