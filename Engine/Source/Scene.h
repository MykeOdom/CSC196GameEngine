#pragma once
#include <list>

class Renderer;
class Actor;

class Scene
{
public:
	Scene() = default;

	template<typename T>
	T* GetActor();

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);
protected:
	std::list<Actor*> m_actors;
};

template<typename T>
T* Scene::GetActor()
{
	for (Actor* actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor);
		if (result) return result;
	}
	return nullptr;
};