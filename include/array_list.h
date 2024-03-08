#pragma once
#include <cassert>
#include <string>
#include <iostream>
#include <exception>

// If you set this to 0, ArrayList messages should not show.  I put this here because after this lab,
// we don't really want those debug messages cluttering things up.
#define SHOW_DEBUG_MSGS 0

#define INITIAL_SIZE 5

namespace ssuds
{
	/// An ArrayList is similar to (but more simple than) std::vector.  Behind the scenes
	/// is contains a dynamically created array of T objects.  This array is resized periodically
	/// when we run out of capacity (currently by a fixed amount, although that could be changed
	/// to doubling, tripling, if desired -- that would increase the amortized efficiency, but
	/// would (drastically) increase the memory footprint).
	template<class T> 
	class ArrayList
	{
	protected:
		/// The dynamically allocated array
		T* mData;
		unsigned int mCapacity;
		unsigned int mSize;

	public:
		/// Default constructor -- allocates msCapacityIncrease
		ArrayList() : mSize(0), mData(NULL)
		{
			mCapacity = INITIAL_SIZE;
			mData = new T[INITIAL_SIZE];
		}


		/// Constructor in which they give us the initial capacity
		ArrayList(size_t initial_capacity) : mSize(0), mData(NULL)
		{
			mCapacity = (unsigned int)initial_capacity;
			mData = new T[initial_capacity];
		}

		ArrayList(const ArrayList& other)
		{
			// make a DEEP copy of other's data
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mData = new T[mCapacity];
			for (unsigned int i = 0; i < mSize; i++)
				mData[i] = other.mData[i];
		}

		ArrayList(ArrayList&& other)
		{
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mData = other.mData;
			other.mData = NULL;
		}

		ArrayList(const std::initializer_list<T>& ilist)
		{
			mCapacity = ilist.size();
			mSize = 0;
			mData = new T[mCapacity];
			for (T s : ilist)
				push_back(s);
		}

		/// The destructor
		~ArrayList()
		{
			if (mData)
				delete[] mData;
		}


		/// This allows us to do a[0] and similar for ArrayLists.
		T& operator [] (unsigned int index) const
		{
			if (index < mSize)
				return mData[index];
			else
				throw std::out_of_range("Invalid index");
		}

		void operator=(const ArrayList& other)
		{
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mData = new T[mCapacity];
			for (unsigned int i = 0; i < mSize; i++)
				mData[i] = other.mData[i];
		}

		/// Gets the number of available slots in the array.  Note: This is not the same as the
		/// number of *used* slots (that's the size).  Once this capacity is reached, we'll do the
		/// costly "grow" operation
		unsigned int capacity() const
		{
			return mCapacity;
		}

	protected:
		// This method should be called before adding an element.  Determines
		// if we're currently at capacity.  If we are, resize the array
		// to be of a bigger size (and return true).  Do nothing and return
		// false otherwise.
		bool check_for_capacity()
		{
			if (mSize == mCapacity)
			{
#if _DEBUG && SHOW_DEBUG_MSGS
				std::cout << "[[GROW]]" << std::endl;
#endif
				T* temp_data = new T[mCapacity * 2];
				for (unsigned int i = 0; i < mSize; i++)
					temp_data[i] = mData[i];
				delete[] mData;
				mData = temp_data;
				mCapacity = mCapacity * 2;
				return true;
			}
			return false;
		}

	public:
		/// Resets the array to its initial (empty) state. 
		void clear()
		{
			if (mData)
			{
				delete[] mData;
				mData = NULL;
			}
			mData = new T[INITIAL_SIZE];
			mCapacity = INITIAL_SIZE;
			mSize = 0;
		}

		/// Finds the first occurrence of the given index, starting at the given index.  -1 is returned
		/// if that item can't be found
		int find(const T& val, int start_index = 0) const
		{
			for (int i = start_index; i < (int)mSize; i++)
			{
				if (val == mData[i])
					return i;
			}
			return -1;
		}


		/// Inserts the given element at the given index, shifting everything to the right.  Note: You can't
		/// append using this method (use push_back for that)
		void insert(const T& item, int index)
		{
			if (index < 0 || index >(int)mSize)
				throw std::out_of_range("Invalid index");
			if (index == mSize)
				push_back(item);
			else if (index == 0)
				push_front(item);
			else
			{
				check_for_capacity();
				for (int i = mSize; i > index; i--)
					mData[i] = mData[i - 1];
				mData[index] = item;
				mSize++;
			}
		}



		/// Appends the given element to the end of the array, resizing if necessary
		void push_back(const T& item)
		{
			check_for_capacity();
			mData[mSize++] = item;
		}


		/// Prepends the given element to the beginning of the array, resizing if necessary -- this is much more expensive than push_back!
		void push_front(const T& item)
		{
			check_for_capacity();
			for (int i = mSize; i > 0; i--)
				mData[i] = mData[i - 1];
			mData[0] = item;
			mSize++;
		}



		/// Removes the element at the given index.  It resizes the array if we go msCapacityIncrease below capacity
		T remove(int index)
		{
			// Make sure we have a good index
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");

			// Get the element at that position
			T removed = mData[index];

			// Remove that offending index by shifting everything down.  Note: the last element in the
			// array is still there!  But...we can't access it, so no worries.  For some values (ints for example), 
			// we could set that last value to 0.  But since this is a templated class, we don't know what to set it
			// to for *all* possible values.  
			for (int i = index; i < (int)mSize - 1; i++)
				mData[i] = mData[i + 1];
			mSize--;

			// I made the choice to resize if we go below capacity.  It would've been OK to just keep capacity where it was at.
			if (mSize <= mCapacity / 2)
			{
				T* temp_data = new T[mCapacity / 2];
				for (unsigned int i = 0; i < mSize; i++)
					temp_data[i] = mData[i];
				delete[] mData;
				mData = temp_data;
				mCapacity /= 2;
			}

			return removed;
		}


		/// Gets the number of *used* slots in the array.
		unsigned int size() const
		{
			return mSize;
		}

		/// The stream operator for ArrayLists
		friend std::ostream& operator<<(std::ostream& os, const ArrayList<T>& a)
		{
			os << "[";
			bool first = true;
			for (int i = 0; i < (int)a.size(); i++)
			{
				if (!first)
					os << ", ";
				else
					first = false;
				os << a[i];
			}
			os << "]";
			return os;
		}

		class ArrayListIterator
		{
		protected:
			ArrayList& mOwner;		// Could be an ArrayList pointer too
			int mCurPos;
			int inc;
		public:
			ArrayListIterator(ArrayList& the_list, int index=0, bool ascending = true) : mOwner(the_list)
			{
				mCurPos = index;
				if (ascending)
					inc = 1;
				else
					inc = -1;
			}
			
			bool operator==(const ArrayListIterator& other)
			{
				return mCurPos == other.mCurPos && &mOwner == &other.mOwner;
			}

			bool operator!=(const ArrayListIterator& other)
			{
				// Return true if we have a different position than other OR
				// if our address (this) is different than the ADDRESS of other (&other)
				return mCurPos != other.mCurPos || &mOwner != &other.mOwner;
			}

			// Overload the * operator
			T& operator*()
			{
				// Return the current value from mOwner at position mCurPos
				return mOwner[mCurPos];
			}

			// Overload the ++it (pre-increment)
			void operator++()
			{
				// Advance to the next spot in our owner list
				mCurPos += inc;
			}

			// [optional] overload the it++ (post-increment) method
			void operator++(int dummy)
			{
				// You do EXACTLY the same thing as the other ++ operator
				// dummy is just there so the compiler can call this instead of the other
				// operator++
				mCurPos += inc;
			}
		};

		ArrayListIterator begin()
		{
			return ArrayListIterator(*this);
		}

		ArrayListIterator end()
		{
			// Create an iterator that is the state of any iterator when they're
			// DONE iterating (set its mCurPos to the size of our list)
			return ArrayListIterator(*this, mSize);
		}

		ArrayListIterator rbegin()
		{
			return ArrayListIterator(*this, mSize-1, false);
		}

		ArrayListIterator rend()
		{
			return ArrayListIterator(*this, -1, false);
		}
	};
}
