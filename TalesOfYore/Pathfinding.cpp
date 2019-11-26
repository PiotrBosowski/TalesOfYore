#include "Pathfinding.hpp"
#include "World.hpp"
#include "Hero.hpp"

Pathfinding::Pathfinding(Hero * const hero_, World * const world_) : hero { hero_ }, world{world_}
{

}

void Pathfinding::findBestPath(const Cords & relativeCords)
{
	Room * roomRef = world->getWorldMap()[relativeCords.level];
	Cords absTargetCords = hero->position.get() + relativeCords;
	if (!roomRef->checkSquareBelonging(absTargetCords))
	{
		//find shortest way to rooms egress
	}
	else
	{
		if (roomRef->checkLine(hero->position.get(), absTargetCords))
		{
			hero->move.queueMove(relativeCords);//wysylamy tylko docelowy adres, funkcja sama ma do niego dojsc (bo zawsze bedzie dochodzic po linii prostej)
		}
		
	//	else
	//	{
	//		hero->move.queueMove(pathsetting.findBestPath(hero->position.get(), absTargetCords)); //find best path powinno zwracac wektor kolejnych cordow, miedzy ktorymi klasa "moving" bedzie poruszac sie w linii prostej
		//nodesGraphRef
		//roomMapRef

		//3. else add 2 dynamic nodes to our node structure and calculate how they changed graph
		//4. find best path from first to second using dijijksatra algorythm
		//5. as a return got vector of straight moves to do
		//6. queue all theese moves
	//	}
	}
}




Pathfinding::~Pathfinding()
{

}
