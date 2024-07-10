#include "Model.h"

void Model::Draw(Renderer renderer, const Vector2& postion, float angle, float scale)
{
	if (m_points.empty()) return;

	for (int i = 0; i < m_points.size() - 1; i++)
	{
		
		Vector2 p1 = m_points[i].Rotate(angle) * scale + postion;
		Vector2 p2 = m_points[i+ 1].Rotate(angle) * scale + postion;

		renderer.DrawLine(p1.x, p2.x, p1.y, p2.y);
	}
}
