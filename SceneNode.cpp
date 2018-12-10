#include "SceneNode.h"



SceneNode::SceneNode() 
{
}

void SceneNode::update()
{
	// Do nothing by default
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();
	drawCurrent(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}
