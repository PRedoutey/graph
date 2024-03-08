#pragma once
#include <map>
#include <iostream>
#include <exception>

namespace ssuds
{
	template<class N, class E>
	class Graph
	{
	protected:
		std::map<N, std::map<N, E>> mData;

	public:
		// No constructor or destructor needed!

		void add_node(const N& new_node)
		{
			if (has_node(new_node) == 0)
				mData[new_node];
		}

		void add_edge(const N& start, const N& end, const E& edge)
		{
			if (mData.find(start) == mData.end() || mData.find(end) == mData.end())
				throw std::out_of_range("Invalid key");
			mData[start][end] = edge;
		}

		int get_num_nodes() { return mData.size(); }

		N get_node(int index)
		{
			typename std::map<N,std::map<N,E>>::iterator iter = mData.begin();
			for (int i = 0; i < index; i++)
				iter++;
			return iter->first;
		}

		int has_node(const N& node)
		{
			if (mData.find(node) == mData.end())
				return 0;
			return 1;
		}

		int are_connected(const N& start, const N& end)
		{
			if (has_node(start) == 0)
				return 0;
			if (mData[start].find(end) == mData[start].end())
				return 0;
			return 1;
		}

		E& get_edge(const N& start, const N& end)
		{
			if (are_connected(start, end) == 0)
				throw std::out_of_range("Invalid key");
			return mData[start][end];
		}

		void remove_edge(const N& start, const N& end)
		{
			if (are_connected(start, end) == 0)
				throw std::out_of_range("Invalid key");
			mData[start].erase(mData[start].find(end));
		}

		void remove_node(const N& node)
		{
			if (has_node(node) == 0)
				throw std::out_of_range("Invalid key");
			mData.erase(mData.find(node));
			for (int i = 0; i < get_num_nodes(); i++)
			{
				N n = get_node(i);
				if (are_connected(n, node))
					remove_edge(n, node);
			}
		}

		int get_num_neighbors(const N& node)
		{
			if (has_node(node) == 0)
				throw std::out_of_range("Invalid key");
			return mData[node].size();
		}

		N get_neighbor(const N& node, int index)
		{
			if (has_node(node) == 0)
				throw std::out_of_range("Invalid key");
			if (get_num_neighbors(node) <= index)
				throw std::out_of_range("Invalid index");
			typename std::map<N, E>::iterator iter = mData[node].begin();
			for (int i = 0; i < index; i++)
				iter++;
			return iter->first;
		}

		E& get_neighbor_edge(const N& node, int index)
		{
			if (has_node(node) == 0)
				throw std::out_of_range("Invalid key");
			if (index < 0 || index >= get_num_neighbors(node))
				throw std::out_of_range("Invalid index");
			return mData[node][get_neighbor(node,index)];
		}

		friend std::ostream& operator<<(std::ostream& os, Graph<N,E>& g)
		{
			for (int i = 0; i < g.get_num_nodes(); i++)
			{
				N n = g.get_node(i);
				os << n << "\t|";
				for (int i = 0; i < g.get_num_neighbors(n); i++)
					os << " {" << g.get_neighbor(n, i) << ":" << g.get_neighbor_edge(n, i) << "}";
				os << std::endl;
			}
			return os;
		}
	};
}