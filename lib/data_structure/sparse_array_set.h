/**
 * sparse_array_set.h
 * Purpose: Dynamic array representation for sparse sets.
 *          Lookups may need linear time.
 *
 * The original code was kindly provided by Darren Strash.
 *
 ******************************************************************************
 * Copyright (C) 2015-2017 Sebastian Lamm <lamm@ira.uka.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef _SPARSE_ARRAY_SET_H
#define _SPARSE_ARRAY_SET_H

#include <set>
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

class sparse_array_set {
    public:
        /**
         * Constructor.
         * Initializes the array with the given size.
         *
         * @param size Size of the array.
         */
        sparse_array_set(unsigned int size) : elements(size, -1), first(0), last(-1) { }

        /**
         * Default Constructor.
         */
        sparse_array_set() : elements(), first(0), last(-1) { }

        /**
         * Default Destructor.
         */
        ~sparse_array_set() { }

        /**
         * Resizes the array with a given size.
         *
         * @param size Size of the array.
         */
        void resize(unsigned int size) {
            elements.resize(size, -1);
        }

        /**
         * Initializes the array with a given size.
         *
         * @param size Size of the array.
         */
        void init(unsigned int size) {
            elements.resize(size, -1);
            first = 0;
            last = -1;
        }

        /**
         * Initializes the array with the size of a given adjacency array.
         * Inserts all neighbors for the given node.
         *
         * @param adj Adjacency array of the array.
         * @param node Node for which neighbors will be added.
         */
        void init_from_adj(std::vector<std::vector<int>> & adj, int node) {
            resize(adj.size());
            for (int neighbor : adj[node]) {
                insert(neighbor);
            }
        }

        /**
         * Check if the set contains a given node.
         * May needs to check all elements in the set.
         *
         * @param x Node to search for.
         * @return True, if the node exists in the array.
         *         False, otherwise.
         */
        bool contains(int const x) const {
            for (int value : *this) {
                if (value == x) return true;
            }
            return false;
        }

        /**
         * Insert a given node to the set.
         * If the node is already present, do nothing.
         *
         * @param x Node to insert.
         */
        void insert(int const x) {
            if (contains(x)) return;
            last++;
            elements[last] = x;
        }

        /**
         * Remove a given node from the set.
         *
         * @param x Node to remove.
         */
        void remove(int const x) {
            for (int index = first; index <= last; index++) {
                if (elements[index] == x) {
                    elements[index] = elements[last];
                    elements[last] = x;
                    last--;
                    return;
                }
            }
        }

        /**
         * Move a node from the current set to another one.
         *
         * @param x Node to move.
         * @param other Other array set.
         */
        void move_to(int x, sparse_array_set &other) {
            remove(x);
            other.insert(x);
        }

        /**
         * Returns the size of the set.
         *
         * @return Size of the set.
         */
        unsigned int size() const { return last - first + 1; }

        /**
         * Check if the set is empty.
         *
         * @return True, if the set is empty.
         *         False, otherwise.
         */
        bool empty() const { return last < first; }

        /**
         * Returns a iterator to the beginning of the set.
         *
         * @return Iterator to the beginning of the set.
         */
        std::vector<int>::iterator begin() { return elements.begin() + first; }

        /**
         * Returns a iterator to the end of the set.
         *
         * @return Iterator to the end of the set.
         */
        std::vector<int>::iterator end()   { return elements.begin() + last + 1; }

        /**
         * Returns a _const_ iterator to the beginning of the set.
         *
         * @return Iterator to the beginning of the set.
         */
        std::vector<int>::const_iterator begin() const { return elements.begin() + first; }

        /**
         * Returns a _const_ iterator to the end of the set.
         *
         * @return Iterator to the end of the set.
         */
        std::vector<int>::const_iterator end() const { return elements.begin() + last + 1; }

        /**
         * Returns the element at a given index.
         *
         * @param index Index of the element.
         * @return Element at the index.
         */
        int at(unsigned int index) {
            return elements[index];
        }

        /**
         * Returns the element at a given index.
         *
         * @param index Index of the element.
         * @return Element at the index.
         */
        int operator[](unsigned int index) { return at(index); }

        /**
         * Clear the set.
         * Simply resets indiciators for the beginning and end.
         */
        void clear() {
            first = 0;
            last = -1;
        }

    private:
        // Array containing the elements.
        std::vector<int> elements;
        // Index of the first element.
        int first;
        // Index of the last element.
        int last;
};

#endif 
