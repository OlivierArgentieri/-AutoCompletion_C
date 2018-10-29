// auto_completion_arbre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Letter.h"
#include <vector>
#include <list>

#define TRUE 1
#define FALSE 0
void fill_linked_letter_with_file(std::string file_name, Letter **letter);

// search letter and add if not exist 
void add_letter_if_not_exist(Letter **letter, char c);
// move letter
void move_to_right(Letter** current_letter);
void move_to_under(Letter** current_letter);

// unroll the tree
void unwrap_tree(Letter * letters);

// print words by letter 
void find_word_by_letter(Letter * letters, char c);
int main()
{
	Letter* start;
	fill_linked_letter_with_file( "liste_francais.txt",&start);

	find_word_by_letter(start, 'a');
}

void fill_linked_letter_with_file(std::string file_name, Letter **letter)
{
	int c;
	FILE* file;
	(*letter) = (Letter *)malloc(sizeof(Letter)); // not exist
	(*letter)->m_next = nullptr;
	(*letter)->m_under= nullptr;
	(*letter)->m_top= nullptr;
	(*letter)->m_value = 'a';
	Letter *first_element = (*letter);

	fopen_s(&file, file_name.c_str(), "r");
	if (file)
	{
		while ((c = getc(file)) != EOF)
		{
			if (c != 10)
			{
				add_letter_if_not_exist(letter, c);
				move_to_under(letter);
			}

			else if (c == 10)
			{
				(*letter) = first_element; // return to start
			}
		}
		fclose(file);
	}
	(*letter) = first_element;
}

void add_letter_if_not_exist(Letter** letter, char c)
{
	
	// (*letter)!= nullptr && (*letter)->m_next != nullptr : protection
	// if (*letter)->m_value == '\0' : letter doesn't exist

	while ((*letter)!= nullptr && (*letter)->m_next != nullptr && (*letter)->m_next->m_value != '\0' && (*letter)->m_value < c && (*letter)->m_value != c)
	{
		move_to_right(letter);
	}

	if((*letter)->m_value == c) // letter exist : make nothing
		return;

	if ((*letter)->m_value < c && (*letter)->m_next != nullptr)// at end and not exist
	{
		(*letter)->m_next = (Letter *)malloc(sizeof(Letter));
		(*letter)->m_next->m_under = nullptr;
		(*letter)->m_next->m_next = nullptr;
		(*letter)->m_next->m_top = (*letter);

		(*letter) = (*letter)->m_next;
		(*letter)->m_value = c;// add letter
		return;
	}

	if((*letter)->m_value > c) // add on right 
	{
		char right_letter = (*letter)->m_value;

		Letter* new_letter = (Letter *)malloc(sizeof(Letter)); 
		new_letter->m_value = right_letter;
		new_letter->m_next = (*letter)->m_next;
		new_letter->m_under = (*letter)->m_under;
		new_letter->m_top = (*letter)->m_top;

		(*letter)->m_under = nullptr;

		(*letter)->m_value = c;// add letter
		(*letter)->m_next = new_letter;
		return;
	}

	if ((*letter)->m_value == '\0')
	{
		(*letter)->m_value = c;
		return;
	}

	if ((*letter)->m_next == nullptr || ((*letter)->m_next != nullptr && (*letter)->m_next->m_value == '\0')) // to right
	{	
		Letter* new_letter = (Letter *)malloc(sizeof(Letter));
		new_letter->m_value = c;
		new_letter->m_next = nullptr;
		new_letter->m_under = nullptr;
		new_letter->m_top = (*letter)->m_top;

		(*letter)->m_next = new_letter;
		move_to_right(&(*letter));
		return;
	}
	if ((*letter)->m_next->m_value == '\0')
		(*letter)->m_next->m_value = c;
}

char exist(Letter* letter, char c)
{
	while (letter != nullptr && letter->m_next != nullptr && letter->m_next->m_value != '\0' && letter->m_value != c)
	{
		move_to_right(&letter);
	}
	return letter->m_value == c;
}


void move_to_right(Letter** current_letter)
{
	if ((*current_letter) != nullptr && (*current_letter)->m_next != nullptr)
	{
		(*current_letter) = (*current_letter)->m_next;
	}
	else if((*current_letter) != nullptr)
	{
		(*current_letter)->m_next = (Letter *)malloc(sizeof(Letter)); // not exist
		(*current_letter) = (*current_letter)->m_next;
		(*current_letter)->m_value = '\0';

		(*current_letter)->m_next = nullptr;
		(*current_letter)->m_under = nullptr;
		(*current_letter)->m_top = nullptr;
	}
}

void move_to_under(Letter** current_letter)
{
	if ((*current_letter) != nullptr && (*current_letter)->m_under != nullptr) // exist letter
	{
		(*current_letter) = (*current_letter)->m_under;
	}
	else if ((*current_letter) != nullptr)
	{
		(*current_letter)->m_under = (Letter *)malloc(sizeof(Letter)); // not exist
		(*current_letter)->m_under->m_top = (*current_letter);
		(*current_letter) = (*current_letter)->m_under;
		(*current_letter)->m_value = '\0';
		(*current_letter)->m_next = nullptr;
		(*current_letter)->m_under = nullptr;
	}
}

// Start Search
void find_word_by_letter(Letter * letters, char c)
{
	while (letters != nullptr && letters->m_value != c)
	{
		letters = letters->m_next;
	}

	if(letters != nullptr)
	{
		unwrap_tree(letters->m_under);
	}

}

void unwrap_tree(Letter * letters) 
{
	std::list<Letter*> child_nodes = std::initializer_list<Letter*>();




	Letter * start = letters;
	for (Letter * before = letters; before != nullptr; before = before->m_next)
	{
		


		Letter * flag = before;
		
		do{
			printf("%c", (char)flag->m_value);

			if(flag->m_under->m_value == '\0') // end of word
			{
				// roll back 
				while (child_nodes.back()->m_next == nullptr)
				{
					child_nodes.remove(child_nodes.back());
				}
			}
			else
			{
				flag = flag->m_under;
				child_nodes.push_back(flag);
			}
		} while (child_nodes.size() > 0);
		printf("\n");
		//letters = letters->m_next;
	}
}