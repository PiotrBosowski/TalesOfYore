#include "Moving.hpp"
#include "Position.hpp"
#include "World.hpp"
using namespace std;

Moving::Moving(Position * position_, World * world_)
	: position{ position_ }, world{ world_ }
{

}

bool Moving::isQueueEmpty()
{
	return stepsQueue.empty();
}

Cords Moving::front()
{
	return stepsQueue.front();
}

void Moving::eraseFirst()
{
	stepsQueue.erase(stepsQueue.begin());
}

void Moving::makeMove()
{
	Square * const sourceSquare = world->getSquare(position->get());
	Square * const targetSquare = world->getSquare(position->get() + stepsQueue.front());
	
	if (targetSquare != nullptr)
	{
		switch (targetSquare->getType())
		{
		case wall:
		{
			stepsQueue.clear();
			break;
		}
		default:
		{
			position->set(targetSquare->position);
			eraseFirst();
			break;
		}
		}
	}
	else
	{
		if (sourceSquare->getType() == entrance || sourceSquare->getType() == egress)
		{
			Position lowerPosition = position->get() + stepsQueue.front();
			Position higherPosition = position->get() + stepsQueue.front();
			Square * const lowerSquare = world->getSquare(--lowerPosition);
			Square * const higherSquare = world->getSquare(++higherPosition);
			if (lowerSquare)
			{
				if (lowerSquare->getType() != wall)
				{
					position->set(lowerPosition);
					eraseFirst();
				}
				else stepsQueue.clear();
			}
			else if (higherSquare)
			{
				if (higherSquare->getType() != wall)
				{
					position->set(higherPosition);
					eraseFirst();
				}
				else stepsQueue.clear();
			}
		}
		stepsQueue.clear();
	}
}
	
void Moving::queueMove(Cords cordsToMove) //relative cords
{
	stepsQueue.clear();
	if (cordsToMove.x == 0)
	{
		int Ysteps = cordsToMove.y;
		if (Ysteps > 0)
		{
			while (Ysteps > 0)
			{
				stepsQueue.push_back(Cords{ 0, 1 });
				Ysteps--;
			}
		}
		else
		{
			while (Ysteps < 0)
			{
				stepsQueue.push_back(Cords{ 0, -1 });
				Ysteps++;
			}
		}
	}
	else if (cordsToMove.y == 0)
	{
		int Xsteps = cordsToMove.x;
		if (Xsteps > 0)
		{
			while (Xsteps > 0)
			{
				stepsQueue.push_back(Cords{ 1, 0 });
				Xsteps--;
			}
		}
		else
		{
			while (Xsteps < 0)
			{
				stepsQueue.push_back(Cords{ -1, 0 });
				Xsteps++;
			}
		}
	}
	else //diagonals
	{
		int actual_x_rel = 0;
		int actual_y_rel = 0;
		double A = static_cast<double>(cordsToMove.y) / cordsToMove.x;
		double B = 0;
		int distance = abs(cordsToMove.x) + abs(cordsToMove.y);
		switch (getDirectionOfSuchVector(cordsToMove))
		{
		case NE:
		{
			while (distance > 0)
			{
				if (linearFunction(A, B, actual_x_rel + 1) < actual_y_rel)
				{
					--actual_y_rel;
					stepsQueue.push_back(Cords{ 0, -1 });
				}
				else
				{
					++actual_x_rel;
					stepsQueue.push_back(Cords{ 1, 0 });
				}
				distance--;
			}
		}
		case SE:
		{
			while (distance > 0)
			{
				if (linearFunction(A, B, actual_x_rel + 1) > actual_y_rel + 1)
				{
					++actual_y_rel;
					stepsQueue.push_back(Cords{ 0, 1 });
				}
				else
				{
					++actual_x_rel;
					stepsQueue.push_back(Cords{ 1, 0 });
				}
				distance--;
			}
		}
		case SW:
		{
			while (distance > 0)
			{
				if (linearFunction(A, B, actual_x_rel) > actual_y_rel + 1)
				{
					++actual_y_rel;
					stepsQueue.push_back(Cords{ 0, 1 });
				}
				else
				{
					--actual_x_rel;
					stepsQueue.push_back(Cords{ -1, 0 });
				}
				distance--;
			}
		}
		case NW:
		{
			while (distance > 0)
			{
				if (linearFunction(A, B, actual_x_rel) < actual_y_rel)
				{
					--actual_y_rel;
					stepsQueue.push_back(Cords{ 0, -1 });
				}
				else
				{
					--actual_x_rel;
					stepsQueue.push_back(Cords{ -1, 0 });
				}
				distance--;
			}
		}
		default: return;
		}
	}
}

double Moving::linearFunction(double A, double B, double x) const
{
	return A * (x - 0.5) + B + 0.5;
}

Moving::~Moving()
{

}
