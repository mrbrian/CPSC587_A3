#include "Spring.h"
#include <vector>

class Model
{
public:
	std::vector<Mass*> springs;
	std::vector<Mass*> masses;

	virtual void init();
	virtual void render();
	virtual void update(float dt);
};

class Model1 : public Model
{
	void init() override;
};

class Model2 : public Model
{
	void init() override;
};
