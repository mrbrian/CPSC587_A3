#include "Spring.h"
#include <vector>

class Model
{
public:
	std::vector<Spring*> springs;
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

class Model3 : public Model
{
	void init() override;
	void update(float dt) override;
};

class Model4 : public Model
{
	void init() override;
};

class Model5 : public Model
{
	void init() override;
	void update(float dt) override;
};
