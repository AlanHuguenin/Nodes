#include "random.h"
#include "network.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

void Network::resize(const size_t& size)
{
	RandomNumbers randomN;
	for (unsigned int i(0); i < size; ++i)
	{
		values.push_back(0);
	}
	randomN.normal(values, 0, 1);
}

bool Network::add_link(const size_t& nodeA, const size_t& nodeB)
{
	if ((size() < nodeA + 1)or(size() < nodeB + 1)or(nodeA == nodeB)) //if one of the two nodes doesn't exist or if they're the same
		return false;
	for(auto it : links)
	{
		if(it.first == nodeA)
			if(it.second == nodeB)
				return false;
				
		if(it.first == nodeB)
			if(it.second == nodeA)
				return false;
	}
	links.insert(make_pair(nodeA, nodeB));
	links.insert(make_pair(nodeB, nodeA));
	return true;
}

size_t Network::random_connect(const double& mean)
{
	links.clear();
	RandomNumbers randomN;
	size_t numTot(0);
	vector<size_t> otherNodes;
	for(unsigned int i(0); i < size(); ++i)
		otherNodes.push_back(i);
	for(unsigned int i(0); i < size(); ++i)
	{
		unsigned int deg(randomN.poisson(mean));
		size_t numb(0);
		while (numb < deg)
		{
			randomN.shuffle(otherNodes); //shuffles the nodes and picks the first one
			if (add_link(i, otherNodes[0]))
			{
				++numb;
				++numTot;
			}
		}
	}
	return numTot;    //number of links in total
}

size_t Network::set_values(const vector<double>& newValues)
{
	values.clear();
	values = newValues;
	return values.size();
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t& node) const
{
	size_t deg(0);
	for(auto it : links)
	{
		if(it.first == node)
			++deg;
	}
	return deg;
}

double Network::value(const size_t& node) const
{
	if (node <= size())
		return values[node];
	else return 0;
}


vector<double> Network::sorted_values() const
{
	vector<double> sorted(values);
	sort(sorted.begin(), sorted.end(), greater<double>());
	return sorted;
}

vector<size_t> Network::neighbors(const size_t& node) const
{
	vector<size_t> neigh;
	for(auto it : links)
	{
		if(it.first == node)
			neigh.push_back(it.second);
	}
	return neigh;
}
